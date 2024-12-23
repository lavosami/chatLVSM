#include "elcc/ECC/ECC.h"

std::pair<int, int> eccEncrypt(int plaintext, int basePoint, int privateKey) {
  int sharedSecret = basePoint * privateKey;
  int cipherX = plaintext + sharedSecret;
  int cipherY = basePoint * plaintext;
  return {cipherX, cipherY};
}

int eccDecrypt(const std::pair<int, int>& ciphertext, int privateKey) {
  int sharedSecret = ciphertext.second / privateKey;
  return ciphertext.first - sharedSecret;
}