#include "protocol.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <array>
#include <chrono>
#include <cstring>
#include <deque>
#include <iostream>
#include <thread>

using boost::asio::ip::tcp;

class Client {
 private:
  boost::asio::io_service& io_service;
  tcp::socket socket;
  std::array<char, MAX_IP_PACK_SIZE> readMessage;
  std::deque<std::array<char, MAX_IP_PACK_SIZE>> writeMessages;
  std::array<char, MAX_NICKNAME> nickname;

 public:
  Client(const std::array<char, MAX_NICKNAME>& nickname,
         boost::asio::io_service& io_service,
         tcp::resolver::iterator endpoint_iterator);

 private:
  void onConnect(const boost::system::error_code& err);
  void readHandler(const boost::system::error_code& err);
  void writeHandler(const boost::system::error_code& err);
  void writeImpl(std::array<char, MAX_IP_PACK_SIZE> message);
  void closeImpl();

 public:
  void write(const std::array<char, MAX_IP_PACK_SIZE>& message);
  void close();
};