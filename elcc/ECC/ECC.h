#ifndef ECC_H
#define ECC_H

#include <string>
#include <utility>

std::pair<int, int> eccEncrypt(int plaintext, int basePoint, int privateKey);
int eccDecrypt(const std::pair<int, int>& ciphertext, int privateKey);

#endif