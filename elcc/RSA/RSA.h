#ifndef RSA_H
#define RSA_H

#include <string>

struct RSAKeyPair {
  int publicKey;
  int privateKey;
  int modulus;
};

RSAKeyPair generateRSAKeyPair();
std::string rsaEncrypt(const std::string& plaintext, int publicKey,
                       int modulus);
std::string rsaDecrypt(const std::string& ciphertext, int privateKey,
                       int modulus);

#endif