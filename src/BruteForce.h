#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <iostream>
#include <string>
#include <vector>
#include <mutex>

class BruteForce {

private:

  std::string dict = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";
  std::mutex mtx;

public:

  BruteForce();
  ~BruteForce();

  static std::string hashStringSHA256(std::string stringToHash);
  void decryptSHA256(std::string encryptedString,std::string reducedDic);
  std::vector<int> getCharNumberPerThread(int nb_threads);
  void findWord(std::string encryptedString, int nbThreads);
  std::string result;

};

#endif
