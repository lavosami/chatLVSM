#ifndef RSA_H
#define RSA_H

#include <string>

struct RSAKeyPair {
  int publicKey;
  int privateKey;
  int modulus;
};

class RSA {
 private:
  RSAKeyPair keyPair;

 public:
  RSA(int publicKey, int privateKey, int modulus) {
    keyPair = {publicKey, privateKey, modulus};
  }

 public:
  static RSAKeyPair generateRSAKeyPair();
  std::string encrypt(const std::string& plaintext);
  std::string decrypt(const std::string& ciphertext);
};

#endif