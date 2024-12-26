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

    std::cout << "User: " << login << " added!" << std::endl
              << "Password: " << password << std::endl;
    int reg = sqlite3_exec(db, add.str().c_str(), NULL, NULL, NULL);

    sqlite3_close(db);
    return 0;
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

    if (getUser(login)) {
      del << "DELETE FROM User WHERE login = '" << login << "';";
      int reg = sqlite3_exec(db, del.str().c_str(), NULL, NULL, NULL);
    } else {
      std::cout << "User: " << login << " is not found!" << std::endl;
    }

    sqlite3_close(db);
  }
}

struct User_t {
  std::string login;
  std::string password;
};

static int callback(void* veryUsed, int argc, char** argv, char** azColName) {
  User_t* user = (User_t*)veryUsed;
  for (int i = 0; i < argc; i++) {
    if (strcmp(azColName[i], "password") == 0) {
      user->password = argv[i];
    } else if (strcmp(azColName[i], "login") == 0) {
      user->login = argv[i];
    }
  }
  return 0;
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

    User_t user;
    int reg = sqlite3_exec(db, get.str().c_str(), callback, &user, NULL);

    if (!user.login.empty()) {
      return true;
    } else {
      return false;
    }

    sqlite3_close(db);
  }
}

std::string getPass(std::string& login) {
  sqlite3* db;
  int rc = sqlite3_open("db.sqlite3", &db);

  std::string password;

  if (rc != SQLITE_OK) {
    std::cout << "This DataBase doesn't exists";
    sqlite3_close(db);
  } else {
    std::stringstream get;
    get << "SELECT * FROM User WHERE login = '" << login << "';";

    User_t user;
    int reg = sqlite3_exec(db, get.str().c_str(), callback, &user, NULL);

    if (!user.login.empty()) {
      return user.password;
    } else {
      std::cout << "No matches with: " << login << std::endl;
      return nullptr;
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

    if (!getUser(login)) {
      std::cout << "User was not found!" << std::endl;
    }

    std::cout << "User found " << login << std::endl;
    std::cout << "Old password: " << std::endl;
    std::cin >> oldpassword;
    prom = password;

    SHA256 sha;
    sha.update(oldpassword);
    std::array<uint8_t, 32> digest = sha.digest();

    while (prom != SHA256::toString(digest)) {
      std::cout << "Wrong password!" << std::endl;
      std::cout << "Old password: " << std::endl;
      std::getline(std::cin, oldpassword);

      if (oldpassword == "\\\\exit") {
        return;
      }

      sha.update(oldpassword);
      std::array<uint8_t, 32> digest = sha.digest();
    }

    std::cout << "Type in new password: " << std::endl;
    std::cin >> newpassword;

    sha.update(newpassword);
    digest = sha.digest();

    std::cout << "New password is: " << newpassword << std::endl;
    password = SHA256::toString(digest);

    edit << "UPDATE User SET password = '" << password << "' WHERE login = '"
         << login << "';";

    int reg = sqlite3_exec(db, edit.str().c_str(), NULL, NULL, NULL);

    sqlite3_close(db);
  }
}
