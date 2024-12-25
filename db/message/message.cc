#include "message.h"
#include <sqlite3.h>
#include <sstream>
#include "db.h"

void addMessage(std::string& port, std::string& user, std::string& time,
                std::string& textofusr) {

  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream add, userlog;

    userlog << "SELECT COUNT(*) FROM User WHERE login = '" << user << "';";

    add << "INSERT INTO Message (port, user, time, textofusr) VALUES ('" << port
        << "', '" << user << "', '" << time << "', '" << textofusr << "');";

    int reg = sqlite3_exec(db, add.str().c_str(), NULL, NULL, NULL);

    sqlite3_close(db);
  }
}

bool getMessage(std::string& port, std::string& user, std::string& textofusr) {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream get;

    get << "SELECT * FROM User WHERE login = '" << user
        << "' AND SELECT * FROM Chat WHERE port = '" << port
        << "' AND SELECT * FROM Message WHERE textofusr = '" << textofusr
        << "';";

    if (!user.empty()) {
      std::cout << "Message from User " << user << " found - " << textofusr
                << " from chat with port " << port;
      return true;
    } else {
      std::cout << "User - " << user << " not found!";
      return false;
    }

    sqlite3_close(db);
  }
}

void deleteMessage(std::string& port, std::string& user,
                   std::string& textofusr) {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream del;

    del << "SELECT * FROM User WHERE login = '" << user
        << "' AND SELECT * FROM Chat WHRE port = '" << port
        << "' AND DELETE FROM Message WHERE textofusr = '" << textofusr << "';";

    if (getMessage(port, user, textofusr)) {
      std::cout << "Message of User- " << user << " is: " << textofusr
                << " from chat with port: " << port << " is deleted!";
      int rc = sqlite3_exec(db, del.str().c_str(), NULL, NULL, NULL);
    } else {
      std::cout << "User - " << user << " not found!";
    }

    sqlite3_close(db);
  }
}