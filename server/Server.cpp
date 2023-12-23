#include "Server.hpp"



// room's funcs -------------------------------------------------------------------------

void Room::enter(std::shared_ptr<Participant> participant, const std::string& nickname) {
  participants.insert(participant);
  nicknames[participant] = nickname;

  std::for_each(recentMessages.begin(), recentMessages.end(),
                boost::bind(&Participant::onMessage,
                            participant,
                            _1));
}

void Room::leave(std::shared_ptr<Participant> participant) {
  participants.erase(participant);
  nicknames.erase(participant);
}

void Room::broadcast(std::array<char, MAX_IP_PACK_SIZE>& message, std::shared_ptr<Participant> participant) {
  std::string timestamp = getTimestamp();
  std::string nickname = getNickname(participant);
  std::array<char, MAX_IP_PACK_SIZE> formattedMessage;

  strcpy(formattedMessage.data(), timestamp.c_str());
  strcat(formattedMessage.data(), nickname.c_str());
  strcat(formattedMessage.data(), message.data());

  recentMessages.push_back(formattedMessage);
  while (recentMessages.size() > maxRecentMessages) {
    recentMessages.pop_front();
  }

  std::for_each(participants.begin(),
                participants.end(),
                boost::bind(&Participant::onMessage,
                            _1,
                            std::ref(formattedMessage)));
}

std::string Room::getNickname(std::shared_ptr<Participant> participant) {
  return nicknames[participant];
}



// session's funcs -------------------------------------------------------------------------

Session::Session(boost::asio::io_service& io_service, boost::asio::io_service::strand& strand, Room& room)
        :
        socket(io_service),
        strand(strand),
        room(room) {}

void Session::nicknameHandler(const boost::system::error_code& err) {
  if (strlen(nickname.data()) <= MAX_NICKNAME - 2) {
    strcat(nickname.data(), ": ");
  }
  else {
    nickname[MAX_NICKNAME - 2] = ':';
    nickname[MAX_NICKNAME - 1] = ' ';
  }

  room.enter(shared_from_this(), std::string(nickname.data()));

  boost::asio::async_read(socket,
                          boost::asio::buffer(readMessage, readMessage.size()),
                          strand.wrap(boost::bind(&Session::readHandler,
                                                  shared_from_this(),
                                                  _1)));
}

void Session::readHandler(const boost::system::error_code& err) {
  if (!err) {
    room.broadcast(readMessage, shared_from_this());

    boost::asio::async_read(socket,
                            boost::asio::buffer(readMessage, readMessage.size()),
                            strand.wrap(boost::bind(&Session::readHandler,
                                                    shared_from_this(),
                                                    _1)));
  }
  else {
    room.leave(shared_from_this());
  }
}

void Session::writeHandler(const boost::system::error_code& err) {
  if (!err) {
    writeMessages.pop_front();

    if (!writeMessages.empty()) {
      boost::asio::async_read(socket,
                              boost::asio::buffer(readMessage, readMessage.size()),
                              strand.wrap(boost::bind(&Session::readHandler,
                                                      shared_from_this(),
                                                      _1)));
    }
  }
  else {
    room.leave(shared_from_this());
  }
}

tcp::socket& Session::getSocket() {
  return socket;
}

void Session::start() {
  boost::asio::async_read(socket,
                          boost::asio::buffer(nickname, nickname.size()),
                          strand.wrap(boost::bind(&Session::nicknameHandler,
                                                  shared_from_this(),
                                                  _1)));
}

void Session::onMessage(std::array<char, MAX_IP_PACK_SIZE>& message) {
  bool writeInProgress = !writeMessages.empty();
  writeMessages.push_back(message);
  if (!writeInProgress) {
    boost::asio::async_write(socket,
                            boost::asio::buffer(writeMessages.front(),
                                                writeMessages.front().size()),
                                                strand.wrap(boost::bind(&Session::writeHandler,
                                                                        shared_from_this(),
                                                                        _1)));
  }
}



// server's funcs -------------------------------------------------------------------------

Server::Server(boost::asio::io_service& io_service, boost::asio::io_service::strand& strand, const tcp::endpoint& endpoint)
        :
        io_service(io_service),
        strand(strand),
        acceptor(io_service, endpoint) {
          run();
        }

void Server::run() {
  std::shared_ptr<Session> newSession(new Session(io_service, strand, room));
  acceptor.async_accept(newSession->getSocket(),
                        strand.wrap(boost::bind(&Server::onAccept,
                                                this,
                                                newSession,
                                                _1)));
}

void Server::onAccept(std::shared_ptr<Session> newSession, const boost::system::error_code& err) {
  if (!err) newSession->start();
  run();
}
