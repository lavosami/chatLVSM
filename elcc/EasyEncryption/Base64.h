#ifndef BASE64_H
#define BASE64_H

#include <string>
#include <vector>

class Base64 {
 public:
  static std::string encode(const std::vector<char>& data);
  static std::vector<char> decode(const std::string& data);
};

#endif