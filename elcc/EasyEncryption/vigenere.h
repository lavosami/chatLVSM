#pragma once
#include <string>

class Vigenere {
 public:
  static int index(char c);
  static std::string extend_key(std::string& msg, std::string& key);
  static std::string encrypt_vigenere(std::string& msg, std::string& key);
  static std::string decrypt_vigenere(std::string& encryptedMsg,
                                      std::string& newKey);
};