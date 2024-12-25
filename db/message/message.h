#include <sqlite3.h>
#include <iostream>
#include <string>

void addMessage(std::string& port, std::string& user, std::string& time,
                std::string& textofusr);
void deleteMessage(std::string& port, std::string& user,
                   std::string& textofusr);
bool getMessage(std::string& port, std::string& user);
void editMessage(std::string& port, std::string& user, std::string& textofusr);