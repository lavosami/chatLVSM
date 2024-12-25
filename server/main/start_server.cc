#include "db/db/db.h"
#include "db/user/user.h"
#include "server/lib/Server.h"

int main(int argc, char* argv[]) {
  try {
    if (argc < 2) {
      std::cerr << "Usage: server <port> [<port> ...]\n";
      return 1;
    }

    std::shared_ptr<boost::asio::io_service> io_service(
        new boost::asio::io_service);
    boost::shared_ptr<boost::asio::io_service::work> work(
        new boost::asio::io_service::work(*io_service));
    boost::shared_ptr<boost::asio::io_service::strand> strand(
        new boost::asio::io_service::strand(*io_service));

    std::cout << "[" << std::this_thread::get_id() << "]" << "server starts"
              << std::endl;

    std::list<std::shared_ptr<Server>> servers;
    for (int i = 1; i < argc; ++i) {
      tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
      std::shared_ptr<Server> a_server(
          new Server(*io_service, *strand, endpoint));
      servers.push_back(a_server);
    }

    boost::thread_group workers;
    for (int i = 0; i < 1; ++i) {
      boost::thread* t =
          new boost::thread{boost::bind(&WorkerThread::run, io_service)};
      workers.add_thread(t);
    }

    createDB();

    std::string command;

    while (true) {
      std::cout << ">> ";
      std::getline(std::cin, command);  // Считывает строку, включая пробелы

      // Обработка команд
      if (command == "exit") {
        std::cout << "exiting..." << std::endl;
        //deleteDB();
        return 0;
      } else if (command == "hello") {
        std::cout << "hello." << std::endl;
      } else if (command == "help") {
        std::cout << "avaliable commands: hello - to print hello." << std::endl
                  << "help - to see available commands" << std::endl
                  << "exit - to exit." << std::endl;
      } else if (command == "reg") {
        std::string login, password;

        std::cout << "Login: ";
        std::getline(std::cin, login);  // Считывает строку, включая пробелы
        std::cout << "Login - " << login << std::endl;

        std::cout << "Password: ";
        std::getline(std::cin, password);  // Считывает строку, включая пробелы
        std::cout << "password - " << password << std::endl;

        addUser(login, password);
      } else {
        std::cout << "command not found: " << command << std::endl;
      }
    }

    workers.join_all();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}