#pragma once

#include <iostream>
#include <string>
#include "Base64.h"
#include "vigenere.h"

class Encrypt {
 public:
  static std::string encrypt(std::string& msg, std::string& key);
  static std::string sanitize_utf8(std::string& str);
  static std::string decrypt(std::string& encrypted_msg, std::string& key);
};