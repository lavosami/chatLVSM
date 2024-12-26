#include "vigenere.h"
#include <ctype.h>
#include <string.h>
#include <iostream>

static const std::string AVAILABLE_CHARS =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()"
    "_+-=[]{}|;':,.<>/?`~''\\\" ";

int Vigenere::index(char c) {
  for (int ii = 0; ii < AVAILABLE_CHARS.size(); ii++) {
    if (AVAILABLE_CHARS[ii] == c) {
      return ii;
    }
  }
  return -1;
}

std::string Vigenere::extend_key(std::string& msg, std::string& key) {
  int msgLen = msg.size();
  std::string newKey(msgLen, 'x');
  int keyLen = key.size(), i, j;
  for (i = 0, j = 0; i < msgLen; ++i, ++j) {
    if (j == keyLen)
      j = 0;

    newKey[i] = key[j];
  }
  newKey[i] = '\0';
  return newKey;
}

std::string Vigenere::encrypt_vigenere(std::string& msg, std::string& key) {
  int msgLen = msg.size(), keyLen = key.size(), i, j;
  std::string encryptedMsg(msgLen, 'x');

  std::string newKey = extend_key(msg, key);

  for (i = 0; i < msgLen; ++i) {
    if (isalnum(msg[i]) or msg[i] == ' ') {
      encryptedMsg[i] = AVAILABLE_CHARS[(
          (index(msg[i]) + index(newKey[i])) % AVAILABLE_CHARS.size())];
    } else {
      encryptedMsg[i] = msg[i];
    }
  }

  encryptedMsg[i] = '\0';
  return encryptedMsg;
}

std::string Vigenere::decrypt_vigenere(std::string& encryptedMsg,
                                       std::string& newKey) {
  int msgLen = encryptedMsg.size();
  std::string decryptedMsg(msgLen, 'x');
  int i;
  for (i = 0; i < msgLen; ++i) {
    if (isalnum(encryptedMsg[i]) or encryptedMsg[i] == ' ') {
      decryptedMsg[i] =
          AVAILABLE_CHARS[(((index(encryptedMsg[i]) - index(newKey[i])) +
                                  AVAILABLE_CHARS.size()) %
                                 AVAILABLE_CHARS.size())];
    } else {
      decryptedMsg[i] = encryptedMsg[i];
    }
  }
  decryptedMsg[i] = '\0';
  return decryptedMsg;
}
