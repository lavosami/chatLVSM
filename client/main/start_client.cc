#include <ctime>

#include "client/lib/Client.h"

#include "db/db/db.h"
#include "db/message/message.h"
#include "db/user/user.h"

#include "elcc/EasyEncryption/encrypt.h"
#include "elcc/Feistel/Feistel.h"
#include "elcc/RSA/RSA.h"
#include "elcc/SHA256/SHA256.h"

std::string getCurrentTime() {
  auto now = std::time(nullptr);
  auto tm = *std::localtime(&now);
  char buffer[80];
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
  return std::string(buffer);
}

int main(int argc, char* argv[]) {
  try {
    if (argc != 5) {
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

    std::string login = argv[1];
    std::string password, msg;
    std::string port = argv[3];

    SHA256 sha;

    if (getUser(login)) {
      std::cout << "User " << login << " exists" << std::endl;

      std::cout << "Enter your password: ";
      std::getline(std::cin, password);

      sha.update(password);
      std::array<uint8_t, 32> digest = sha.digest();

      while (getPass(login) != SHA256::toString(digest)) {
        std::cout << "Wrong password. Try again: ";
        std::getline(std::cin, password);
        sha.update(password);
        std::array<uint8_t, 32> digest = sha.digest();
      }
    } else {
      std::cout << "User: " << login << " doesn't exist" << std::endl;

      std::cout << "Enter password: ";
      std::getline(std::cin, password);
      sha.update(password);
      std::array<uint8_t, 32> digest = sha.digest();
      password = SHA256::toString(digest);
      addUser(login, password);
      std::cout << login << " added to chat";
    }

    std::cout << "Hello, " << login << "!" << std::endl;

    while (true) {
      memset(message.data(), '\0', message.size());
      if (!std::cin.getline(message.data(),
                            MAX_IP_PACK_SIZE - PADDING - MAX_NICKNAME)) {
        std::cin.clear();
      }
      std::string input = message.data();
      if (input == "\\\\exit") {
        std::cout << "Goodbye " << login << "!" << std::endl;
        break;
      } else if (input == "\\\\IWANNAQUIT") {
        std::cout << "Okay " << login
                  << " we will glad to see you in future chats!";
        deleteUser(login);
        break;
      } else if (input == "\\\\editpass") {
        std::cout << "Enter your old password: ";
        std::getline(std::cin, password);

        while (getPass(login) != password) {
          std::cout << "Wrong password. Try again: ";
          std::getline(std::cin, password);
        }

        std::cout << "Enter new password:";
        std::getline(std::cin, password);
        editUser(login, password);

      } else if (input == "\\\\deletemsg") {
        std::cout << "Which message you wanna delete: ";
        std::getline(std::cin, msg);
        deleteMessage(port, login, msg);

      } else {
        std::string msg = message.data();
        std::string datetime = getCurrentTime();
        addMessage(port, login, datetime, msg);
        client.write(message);
      }
    }
    client.close();
    t.join();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}