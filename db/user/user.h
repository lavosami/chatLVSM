#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include "db.h"

void addUser(sqlite3* db, std::string& login, std::string& password);
bool deleteUser(sqlite3* db, std::string& login);
bool getUser(sqlite3* db, std::string& login);
void editUser(sqlite3* db, std::string& login);