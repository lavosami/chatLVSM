#include <sqlite3.h>
#include <iostream>
#include <string>

void addMessage(std::string& chatport, std::string& user, std::string& time,
                std::string& textofusr);
void deleteMessage(std::string& chatport, std::string& user,
                   std::string& textofusr);
bool getMessage(std::string& chatport, std::string& user);
void editMessage(std::string& chatport, std::string& user,
                 std::string& textofusr);