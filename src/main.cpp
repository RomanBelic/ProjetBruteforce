#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cassert>
#include "BruteForce.h"


int main() *
{

  BruteForce b;

  b.findWord(BruteForce::hashStringSHA256("a5a"),4);
  std::cout<<b.result<<std::endl;
  //b.decryptSHA256(BruteForce::hashStringSHA256("abc"));

	return 0;
}
