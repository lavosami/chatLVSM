#include "elcc/Blowfish/Blowfish.h"
#include <stdexcept>
#include <vector>

// Feistel function: XORs each character in 'half' with the corresponding character in 'key'
std::string feistelFunction(const std::string& half, const std::string& key) {
  if (key.empty()) {
    throw std::invalid_argument("Key cannot be empty.");
  }

  std::string result = half;
  for (size_t i = 0; i < half.size(); ++i) {
    result[i] = half[i] ^ key[i % key.size()];
  }
  return result;
}

// Feistel encryption: Splits plaintext, applies rounds of XOR-based transformations
std::string feistelEncrypt(const std::string& plaintext,
                           const std::string& key) {
  if (plaintext.size() % 2 != 0) {
    throw std::invalid_argument("Plaintext length must be even.");
  }

  size_t n = plaintext.size() / 2;
  std::string left = plaintext.substr(0, n);
  std::string right = plaintext.substr(n);

  for (int round = 0; round < 16; ++round) {
    std::string temp = right;
    right = feistelFunction(right, key);  // Apply Feistel function
    for (size_t i = 0; i < left.size(); ++i) {
      right[i] = left[i] ^ right[i];  // XOR left with modified right
    }
    left = temp;  // Swap halves
  }

  return left + right;  // Combine halves for ciphertext
}

// Feistel decryption: Reverses encryption process to recover plaintext
std::string feistelDecrypt(const std::string& ciphertext,
                           const std::string& key) {
  if (ciphertext.size() % 2 != 0) {
    throw std::invalid_argument("Ciphertext length must be even.");
  }

  size_t n = ciphertext.size() / 2;
  std::string left = ciphertext.substr(0, n);
  std::string right = ciphertext.substr(n);

  for (int round = 15; round >= 0; --round) {
    std::string temp = left;
    left = feistelFunction(left, key);  // Apply Feistel function
    for (size_t i = 0; i < right.size(); ++i) {
      left[i] = right[i] ^ left[i];  // XOR right with modified left
    }
    right = temp;  // Swap halves
  }

  return left + right;  // Combine halves for plaintext
}