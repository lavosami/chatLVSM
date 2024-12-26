#include "RSA.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

int gcd(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

int modInverse(int a, int m) {
  a = a % m;
  for (int x = 1; x < m; ++x) {
    if ((a * x) % m == 1)
      return x;
  }
  return -1;
}

RSAKeyPair RSA::generateRSAKeyPair() {
  int p = 61;     // First prime
  int q = 53;     // Second prime
  int n = p * q;  // Modulus
  int phi = (p - 1) * (q - 1);

  int e = 3;  // Public key
  while (gcd(e, phi) != 1)
    ++e;

  int d = modInverse(e, phi);  // Private key

  RSAKeyPair keyPair = {e, d, n};

  // clang-format off
  std::cout << "Public key: " << e
            << "\nPrivate key: " << d 
            << "\nModulus: " << n 
            << std::endl;
  // clang-format on

  return keyPair;
}

std::string RSA::encrypt(const std::string& plaintext) {
  std::ostringstream oss;
  for (char c : plaintext) {
    int encryptedChar = static_cast<int>(std::pow(c, this->keyPair.publicKey)) %
                        this->keyPair.modulus;
    oss << encryptedChar << " ";
  }
  return oss.str();
}

std::string RSA::decrypt(const std::string& ciphertext) {
  std::istringstream iss(ciphertext);
  std::ostringstream oss;
  int encryptedChar;
  while (iss >> encryptedChar) {
    char decryptedChar =
        static_cast<char>(std::pow(encryptedChar, this->keyPair.privateKey)) %
        this->keyPair.modulus;
    oss << decryptedChar;
  }
  return oss.str();
}