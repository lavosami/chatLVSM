#include "user.h"

void addUser(sqlite3* db, std::string& login, std::string& password) {
  std::stringstream add;
  add << "INSERT INTO User (login, password) VALUES ('" << login << "', '"
      << password << "');";

  std::cout << "Пользователь: " << login << " добавлен!" << std::endl
            << "Пароль: " << password << std::endl;
  int reg = sqlite3_exec(db, add.str().c_str(), NULL, NULL, NULL);
}

bool deleteUser(sqlite3* db, std::string& login) {
  std::stringstream del;
  del << "DELETE FROM User WHERE login = '" << login << "';";

  std::cout << "Пользователь: " << login << " удален!" << std::endl;
}

bool getUser(sqlite3* db, std::string& login) {
  std::stringstream get;
  get << "SELECT * FROM User WHERE login = '" << login << "';";
  if (!login.empty()) {
    std::cout << "Пользователь найден: " << login << std::endl;
    return true;
  } else {
    std::cout << "Такого пользователя нет" << std::endl;
    return false;
  }
}
