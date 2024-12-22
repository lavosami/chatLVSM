#include "message.h"
#include <sqlite3.h>
#include <sstream>
#include "db.h"

void addMessage(std::string& chatport, std::string& user, std::string& time,
                std::string& textofusr) {

  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream add, Userlog, Chatlog;

    Userlog << "SELECT COUNT(*) FROM User WHERE login = '" << user << "';";
    Chatlog << "SELECT COUNT(*) FROM Chat WHERE port = '" << chatport << "';";

    add << "INSERT INTO Message (chatport, user, time, textofusr) VALUES ('"
        << chatport << "', '" << user << "', '" << time << "', '" << textofusr
        << "');";

    int reg = sqlite3_exec(db, add.str().c_str(), NULL, NULL, NULL);

    sqlite3_close(db);
  }
}

bool getMessage(std::string& chatport, std::string& user,
                std::string& textofusr) {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream get;

    get << "SELECT * FROM User WHERE login = '" << user
        << "' AND SELECT * FROM Chat WHERE port = '" << chatport
        << "' AND SELECT * FROM Message WHERE textofusr = '" << textofusr
        << "';";

    if (!user.empty()) {
      std::cout << "Message from User " << user << " found - " << textofusr
                << " from chat with port " << chatport;
      return true;
    } else {
      std::cout << "User - " << user << " not found!";
      return false;
    }

    sqlite3_close(db);
  }
}

void deleteMessage(std::string& chatport, std::string& user,
                   std::string& textofusr) {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream del;

    del << "SELECT * FROM User WHERE login = '" << user
        << "' AND SELECT * FROM Chat WHRE port = '" << chatport
        << "' AND DELETE FROM Message WHERE textofusr = '" << textofusr << "';";

    if (getMessage(chatport, user, textofusr)) {
      std::cout << "Message of User- " << user << " is: " << textofusr
                << " from chat with port: " << chatport << " is deleted!";
      int rc = sqlite3_exec(db, del.str().c_str(), NULL, NULL, NULL);
    } else {
      std::cout << "User - " << user << " not found!";
    }

    sqlite3_close(db);
  }
}