#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include "db.h"

int addUser(std::string& login, std::string& password);
void deleteUser(std::string& login, std::string& password);
bool getUser(std::string& login);
std::string getPass(std::string& password);
void editUser(std::string& login, std::string& password);