#include "elcc/SHA256/SHA256.h"
#include <iomanip>
#include <sstream>

std::string hash(const std::string& data) {
  unsigned long hash = 5381;
  for (char c : data) {
    hash = ((hash << 5) + hash) + c;  // hash * 33 + c
  }
  std::ostringstream oss;
  oss << std::hex << hash;
  return oss.str();
}