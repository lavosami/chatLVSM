#include "db.h"

#include <iostream>
#include <sstream>

void createChatTable(sqlite3* db) {
  std::stringstream chat;

  chat << "CREATE TABLE Chat("
          "port INTEGER PRIMARY KEY NOT NULL,"
          "password TEXT NOT NULL,"
          "encryption TEXT NOT NULL);";
  std::cout << chat.str() << std::endl;

  int rc = sqlite3_exec(db, chat.str().c_str(), NULL, NULL, NULL);
}

void createMessageTable(sqlite3* db) {
  std::stringstream message;

  message << "CREATE TABLE Message("
             "chatport INTEGER PRIMARY KEY NOT NULL,"
             "user TEXT NOT NULL,"
             "time DATETIME NOT NULL,"
             "textofusr TEXT,"
             "FOREIGN KEY (chatport) REFERENCES chat(port),"
             "FOREIGN KEY (user) REFERENCES User(login));";
  std::cout << message.str() << std::endl;

  int rc = sqlite3_exec(db, message.str().c_str(), NULL, NULL, NULL);
}

void createUserTable(sqlite3* db) {
  std::stringstream user;

  user << "CREATE TABLE User("
          "login TEXT PRIMARY KEY NOT NULL,"
          "password TEXT NOT NULL);";
  std::cout << user.str() << std::endl;

  int rc = sqlite3_exec(db, user.str().c_str(), NULL, NULL, NULL);
}

void createDB() {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);
  std::cout << "Результат: " << rc << std::endl;

  sqlite3_close(db);
}
