#include "user.h"

int addUser(std::string& login, std::string& password) {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream add;
    add << "INSERT INTO User (login, password) VALUES ('" << login << "', '"
        << password << "');";

    if (getUser) {
      std::cout << "User: " << login << " added!" << std::endl
                << "Password: " << password << std::endl;
      int reg = sqlite3_exec(db, add.str().c_str(), NULL, NULL, NULL);
      return 1;
    } else {
      std::cout << "User already exists!";
      return -1;
    }

    sqlite3_close(db);
  }
}

void deleteUser(std::string& login) {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream del;
    del << "DELETE FROM User WHERE login = '" << login << "';";
    if (getUser) {
      std::cout << "User: " << login << " deleted!" << std::endl;
      int reg = sqlite3_exec(db, del.str().c_str(), NULL, NULL, NULL);
    } else {
      std::cout << "User: " << login << " is not found!" << std::endl;
    }

    sqlite3_close(db);
  }
}

bool getUser(std::string& login) {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream get;
    get << "SELECT * FROM User WHERE login = '" << login << "';";

    if (!login.empty()) {
      std::cout << "User is found!: " << login << std::endl;
      return true;
    } else {
      std::cout << "No matches with: " << login << std::endl;
      return false;
    }

    sqlite3_close(db);
  }
}

void editUser(std::string& login, std::string& password) {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream edit;
    std::stringstream nedit;
    std::string oldpassword, newpassword, prom;

    nedit << "SELECT * FROM User WHERE password = '" << password << "';";

    if (!getUser) {
      std::cout << "User was not found!" << std::endl;
    }

    std::cout << "User found" << login << std::endl;
    std::cout << "Old password: " << std::endl;
    std::cin >> oldpassword;
    prom = password;

    while (prom != oldpassword) {
      std::cout << "Wrong password!" << std::endl;
      std::cout << "Old password: " << std::endl;
      std::getline(std::cin, oldpassword);

      if (oldpassword == "\\\\exit") {
        return;
      }
    }

    std::cout << "Type in new password: " << std::endl;
    std::cin >> newpassword;

    std::cout << "New password is: " << newpassword << std::endl;
    password = newpassword;
    std::cout << password << std::endl;

    edit << "UPDATE User SET password = '" << password << "' WHERE login = '"
         << login << "';";

    int reg = sqlite3_exec(db, edit.str().c_str(), NULL, NULL, NULL);

    sqlite3_close(db);
  }
}
