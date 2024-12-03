#include "lib/Client.h"

Client::Client(const std::array<char, MAX_NICKNAME>& nickname_,
               boost::asio::io_service& io_service,
               tcp::resolver::iterator endpoint_iterator)
    : io_service(io_service), socket(io_service) {
  strcpy(nickname.data(), nickname_.data());
  memset(readMessage.data(), '\0', MAX_IP_PACK_SIZE);
  boost::asio::async_connect(socket, endpoint_iterator,
                             boost::bind(&Client::onConnect, this, _1));
}

void Client::onConnect(const boost::system::error_code& err) {
  if (!err) {
    boost::asio::async_write(socket,
                             boost::asio::buffer(nickname, nickname.size()),
                             boost::bind(&Client::readHandler, this, _1));
  }
}

void Client::readHandler(const boost::system::error_code& err) {
  std::cout << readMessage.data() << std::endl;
  if (!err) {
    boost::asio::async_read(
        socket, boost::asio::buffer(readMessage, readMessage.size()),
        boost::bind(&Client::readHandler, this, _1));
  } else {
    closeImpl();
  }
}

void Client::writeHandler(const boost::system::error_code& err) {
  if (!err) {
    writeMessages.pop_front();
    if (!writeMessages.empty()) {
      boost::asio::async_write(
          socket,
          boost::asio::buffer(writeMessages.front(),
                              writeMessages.front().size()),
          boost::bind(&Client::writeHandler, this, _1));
    }
  } else {
    closeImpl();
  }
}

void Client::writeImpl(std::array<char, MAX_IP_PACK_SIZE> message) {
  bool writeInProgress = !writeMessages.empty();
  writeMessages.push_back(message);
  if (!writeInProgress) {
    boost::asio::async_write(socket,
                             boost::asio::buffer(writeMessages.front(),
                                                 writeMessages.front().size()),
                             boost::bind(&Client::writeHandler, this, _1));
  }
}

void Client::closeImpl() {
  socket.close();
}

void Client::write(const std::array<char, MAX_IP_PACK_SIZE>& message) {
  io_service.post(boost::bind(&Client::writeImpl, this, message));
}

void Client::close() {
  io_service.post(boost::bind(&Client::closeImpl, this));
}