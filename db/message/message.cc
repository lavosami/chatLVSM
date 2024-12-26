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

    get << "SELECT * FROM Message WHERE (login, port, textofusr) VALUES ('"
        << user << "', '" << port << "', '" << textofusr << "');";

    if (!user.empty()) {
      int reg = sqlite3_exec(db, get.str().c_str(), NULL, NULL, NULL);
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
    std::stringstream del, userlog;

    userlog << "SELECT COUNT(*) FROM User WHERE login = '" << user << "';";

    del << "DELETE FROM Message WHERE user = '" << user << "' AND textofusr ='"
        << textofusr << "';";

    if (getMessage(port, user, textofusr)) {
      int reg = sqlite3_exec(db, del.str().c_str(), NULL, NULL, NULL);
      std::cout << "Message of User " << user << " - " << textofusr
                << " is deleted!" << std::endl;
    } else {
      std::cout << "User " << user << " not found!";
    }

    sqlite3_close(db);
  }
}