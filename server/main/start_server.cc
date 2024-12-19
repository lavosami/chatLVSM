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

    std::string login = "admin";
    std::string password = "password";

    createDB();

    addUser(login, password);
    getUser(login);
    editUser(login, password);

    workers.join_all();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}