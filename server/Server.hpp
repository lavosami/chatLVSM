#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio/buffer.hpp>

#include "protocol.hpp"

#include <ctime>
#include <string>
#include <deque>
#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <thread>
#include <mutex>
#include <algorithm>
#include <iomanip>
#include <array>

using boost::asio::ip::tcp;

namespace {
  std::string getTimestamp() {
    time_t t = time(0);
    struct tm * now = localtime(&t);
    std::stringstream ss;
    ss << '[' << (now->tm_year + 1900) << '-' << std::setfill('0')
      << std::setw(2) << (now->tm_mon + 1) << '-' << std::setfill('0')
      << std::setw(2) << now->tm_mday << ' ' << std::setfill('0')
      << std::setw(2) << now->tm_hour << ":" << std::setfill('0')
      << std::setw(2) << now->tm_min << ":" << std::setfill('0')
      << std::setw(2) << now->tm_sec << "] ";

    return ss.str();
  }

  class WorkerThread {
  private:
    static std::mutex mutex;

  public:
    static void run(std::shared_ptr<boost::asio::io_service> io_service) {
      {
        std::lock_guard <std::mutex> lock(mutex);
        std::cout << "[" << std::this_thread::get_id() << "] Thread starts" << std::endl;
      }

      io_service->run();

      {
        std::lock_guard <std::mutex> lock(mutex);
        std::cout << "[" << std::this_thread::get_id() << "] Thread ends" << std::endl;
      }

    }
  };

  std::mutex WorkerThread::mutex;
}


class Participant {
public:
  virtual ~Participant() {};
  virtual void onMessage(std::array<char, MAX_IP_PACK_SIZE>& message) = 0;
};

class Room {
private:
  std::unordered_set<std::shared_ptr<Participant>> participants;
  std::unordered_map<std::shared_ptr<Participant>, std::string> nicknames;
  std::deque<std::array<char, MAX_IP_PACK_SIZE>> recentMessages;
  enum {
    maxRecentMessages = 100
  };

public:
  void enter(std::shared_ptr<Participant> participant, const std::string& nickname);
  void leave(std::shared_ptr<Participant> participant);
  void broadcast(std::array<char, MAX_IP_PACK_SIZE>& message, std::shared_ptr<Participant> participant);
  std::string getNickname(std::shared_ptr<Participant> participant);
};


class Session : public Participant, public std::enable_shared_from_this<Session> {
private:
  tcp::socket socket;
  boost::asio::io_service::strand& strand;
  Room& room;
  std::array<char, MAX_NICKNAME> nickname;
  std::array<char, MAX_IP_PACK_SIZE> readMessage;
  std::deque<std::array<char, MAX_IP_PACK_SIZE>> writeMessages;

public:
  Session(boost::asio::io_service& io_service, boost::asio::io_service::strand& strand, Room& room);

private:
  void nicknameHandler(const boost::system::error_code& err);
  void readHandler(const boost::system::error_code& err);
  void writeHandler(const boost::system::error_code& err);

public:
  tcp::socket& getSocket();
  void start();
  void onMessage(std::array<char, MAX_IP_PACK_SIZE>& message);
};


class Server {
private:
  boost::asio::io_service& io_service;
  boost::asio::io_service::strand& strand;
  tcp::acceptor acceptor;
  Room room;

public:
  Server(boost::asio::io_service& io_service, boost::asio::io_service::strand& strand, const tcp::endpoint& endpoint);

public:
  void run();
  void onAccept(std::shared_ptr<Session> newParticipant, const boost::system::error_code& err);
};