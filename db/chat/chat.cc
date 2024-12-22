#include "chat.h"
#include "db.h"

void addChat(std::string& port, std::string& password,
             std::string& encryption) {

  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream add;
    add << "INSERT INTO Chat (port, password, encryption) VALUES ('" << port
        << "', '" << password << "', '" << encryption << "');";

    std::cout << "Chat with port: " << port << " added!" << std::endl
              << "Password of chat: " << password << std::endl;

    int reg = sqlite3_exec(db, add.str().c_str(), NULL, NULL, NULL);

    sqlite3_close(db);
  }
}

void getChat(std::string& port) {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream get;
    get << "SELECT * FROM Chat WHERE port = '" << port << "';";

    if (!port.empty()) {
      std::cout << "Chat is found. Port= " << port << std::endl;
    } else {
      std::cout << "This chat doesn't exist";
    }

    sqlite3_close(db);
  }
}