#include <sqlite3.h>
#include <cstdio>
#include <string>

void createUser(sqlite3* db);
void createChat(sqlite3* db);
void createMessage(sqlite3* db);

sqlite3* createDB(sqlite3* dbName);
void deleteDB(const std::string dbName);