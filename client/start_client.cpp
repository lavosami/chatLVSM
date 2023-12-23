#include "Client.hpp"

int main(int argc, char* argv[]) {
  try {
    if (argc != 4) {
      std::cerr << "Usage: client <nickname> <host> <port>\n";
      return 1;
    }
    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(argv[2], argv[3]);
    tcp::resolver::iterator iterator = resolver.resolve(query);
    std::array<char, MAX_NICKNAME> nickname;
    strcpy(nickname.data(), argv[1]);

    Client client(nickname, io_service, iterator);

    std::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

    std::array<char, MAX_IP_PACK_SIZE> message;

    while (true) {
      memset(message.data(), '\0', message.size());
      if (!std::cin.getline(message.data(), MAX_IP_PACK_SIZE - PADDING - MAX_NICKNAME)) {
        std::cin.clear();
      }
      client.write(message);
    }

    client.close();
    t.join();
    }
    catch (std::exception& e) {
      std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}