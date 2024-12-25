#include "db.h"

#include <cstdio>
#include <iostream>
#include <sstream>

void createUser() {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream user;
    user << "CREATE TABLE User("
            "login TEXT PRIMARY KEY NOT NULL,"
            "password TEXT NOT NULL);";
    std::cout << user.str() << std::endl;

    int usrreg = sqlite3_exec(db, user.str().c_str(), NULL, NULL, NULL);
    sqlite3_close(db);
  }
}

void createChat() {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream chat;
    chat << "CREATE TABLE Chat("
            "port INTEGER PRIMARY KEY NOT NULL,"
            "password TEXT NOT NULL,"
            "encryption TEXT NOT NULL);";
    std::cout << chat.str() << std::endl;

    int chatreg = sqlite3_exec(db, chat.str().c_str(), NULL, NULL, NULL);
    sqlite3_close(db);
  }
}

void createMessage() {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream message;
    message << "CREATE TABLE Message("
               "port INTEGER NOT NULL,"
               "user TEXT NOT NULL,"
               "time DATETIME NOT NULL,"
               "textofusr TEXT,"
               "FOREIGN KEY (user) REFERENCES User(login) ON DELETE CASCADE);";
    std::cout << message.str() << std::endl;

    int messagereg = sqlite3_exec(db, message.str().c_str(), NULL, NULL, NULL);
    sqlite3_close(db);
  }
}

void createDB() {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::cout << "Результат: " << rc << std::endl;

    createUser();
    createChat();
    createMessage();

    sqlite3_close(db);
  }
}

void deleteDB() {
  int rc = remove("db.sqlite3");

  if (rc != 0) {
    std::perror("Error deleting database");
  } else {
    std::cout << "Database deleted successfully" << std::endl;
  }
}
