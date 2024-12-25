#include "client/lib/Client.h"
#include "db/db/db.h"
#include "db/user/user.h"

int main(int argc, char* argv[]) {
  try {
    if (argc != 5) {
      std::cerr << "Usage: client <nickname> <host> <port> <encryption>\n";
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

    std::string login = argv[1];
    std::string password;
    std::string command;

    if (getUser(login)) {
      std::cout << "User: " << login << " exists" << std::endl;

      std::cout << "Enter your password: ";
      std::getline(std::cin, password);

      while (getPass(login) != password) {
        std::cout << "Wrong password. Try again: ";
        std::getline(std::cin, password);
      }
    } else {
      std::cout << "User: " << login << " doesn't exist" << std::endl;

      std::cout << "Enter password: ";
      std::getline(std::cin, password);
      addUser(login, password);
      std::cout << login << " added to chat";
    }

    std::cout << "Hello, " << login << "!" << std::endl;

    std::cout << "You choose " << argv[4] << " encryption. " << std::endl;

    while (true) {
      memset(message.data(), '\0', message.size());
      if (!std::cin.getline(message.data(),
                            MAX_IP_PACK_SIZE - PADDING - MAX_NICKNAME)) {
        std::cin.clear();
      }
      client.write(message);
    }
    client.close();
    t.join();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}