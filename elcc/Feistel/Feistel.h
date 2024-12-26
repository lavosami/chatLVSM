#ifndef FEISTEL_H
#define FEISTEL_H

#include <string>
#include <vector>

class Feistel {
 private:
  std::string key;

 public:
  Feistel(const std::string& key) : key(key) {}

 private:
  std::string function(const std::string& half, const std::string& key);

 public:
  std::string encrypt(const std::string& plaintext);
  std::string decrypt(const std::string& ciphertext);
};

#endif