#ifndef BLOWFISH_H
#define BLOWFISH_H

#include <string>
#include <vector>

std::string feistelEncrypt(const std::string& plaintext,
                           const std::string& key);
std::string feistelDecrypt(const std::string& ciphertext,
                           const std::string& key);

#endif