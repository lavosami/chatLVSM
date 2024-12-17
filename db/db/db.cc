#include "db.h"

#include <cstdio>
#include <iostream>
#include <sstream>

void createUser(sqlite3* db) {
  std::stringstream user;
  user << "CREATE TABLE User("
          "login TEXT PRIMARY KEY NOT NULL,"
          "password TEXT NOT NULL);";
  std::cout << user.str() << std::endl;

  int usrreg = sqlite3_exec(db, user.str().c_str(), NULL, NULL, NULL);
}

void createChat(sqlite3* db) {
  std::stringstream chat;
  chat << "CREATE TABLE Chat("
          "port INTEGER PRIMARY KEY NOT NULL,"
          "password TEXT NOT NULL,"
          "encryption TEXT NOT NULL);";
  std::cout << chat.str() << std::endl;

  int chatreg = sqlite3_exec(db, chat.str().c_str(), NULL, NULL, NULL);
}

void createMessage(sqlite3* db) {
  std::stringstream message;
  message << "CREATE TABLE Message("
             "chatport INTEGER PRIMARY KEY NOT NULL,"
             "user TEXT NOT NULL,"
             "time DATETIME NOT NULL,"
             "textofusr TEXT,"
             "FOREIGN KEY (chatport) REFERENCES chat(port) ON DELETE CASCADE,"
             "FOREIGN KEY (user) REFERENCES User(login) ON DELETE CASCADE);";
  std::cout << message.str() << std::endl;

  int messagereg = sqlite3_exec(db, message.str().c_str(), NULL, NULL, NULL);
}

sqlite3* createDB(sqlite3* dbName) {
  int rc = sqlite3_open("db.sqlite3", &dbName);
  std::cout << "Результат: " << rc << std::endl;

  createUser(dbName);
  createChat(dbName);
  createMessage(dbName);

  sqlite3_close(dbName);
}

void deleteDB(const std::string dbName) {
  int rc = remove(dbName.c_str());
}
