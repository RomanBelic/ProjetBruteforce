#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <iostream>
#include <string>

class BruteForce {

private:

  const uint8_t start_ascii = 32;
  const uint8_t end_ascii = 122;

public:

  BruteForce();
  ~BruteForce();

  static std::string hashStringSHA256(std::string stringToHash)
  std::string decryptSHA256(std::string encryptedString);

};

#endif
