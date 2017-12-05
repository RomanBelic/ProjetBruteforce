#include "BruteForce.h"
#include <iostream>
#include <string>
#include <thread>
#include "sha.h"
#include <cmath>



BruteForce::BruteForce()
{

}

BruteForce::~BruteForce() {

}

std::string BruteForce::hashStringSHA256(std::string stringToHash)
{
  return sha256(stringToHash);
}

void BruteForce::findWord(std::string encryptedString, int nbThreads)
{
  std::thread myThreads[nbThreads];
	std::vector<int> nb_chars = getCharNumberPerThread(nbThreads);

	int current_index = 0;
	for(int i = 0; i < nbThreads; i++) {
		int nbLetters = nb_chars.at(i);
		std::string reducedDic ="";
		for(int j = 0; j < nbLetters; j++) {
			reducedDic += dict[current_index];
			current_index++;
		}
        myThreads[i] = std::thread(&BruteForce::decryptSHA256,this,encryptedString,reducedDic);
    }
    for(int i = 0; i < nbThreads; i++) {
        myThreads[i].join();
    }
}

void BruteForce::decryptSHA256(std::string encryptedString,std::string reducedDic)
{
  bool find = false;
  std::string toTest;
  std::string first = "";
  uint8_t length = 0;

  while(!find)
  {
    for(uint8_t i = 0; i<= dict.length()-1 && !find; i++)
    {
      toTest = first + dict[i];
      std::string dig = hashStringSHA256(toTest);
      if(encryptedString == dig )
        find = true;

      std::cout<<toTest<<std::endl;
    }

    bool posFind = false;
    uint8_t charToTest = length-1;
    while(!posFind)
    {
      std::cout<<first<<std::endl;
      if(length == 0)// premier caractere
      {
        first = reducedDic[0]; //élément tableau réduit
        posFind = true;
        length++;
      }
      else
      {
        if(charToTest == 0 && first.at(charToTest) == reducedDic[reducedDic.length()-1]) //fini le premier caractère tableau réduit.
        {
          first = reducedDic[0]; // élément tableau réduit
          for(uint8_t i = 1; i<= length; i++)
          {
            first =  first + dict[0];
          }
          length++;
          posFind = true;
        }
        else
        {
          //int ascii = (int)first.at(charToTest);
          if(first.at(charToTest)== reducedDic[reducedDic.length()-1]) //tableau réduit
          {
            charToTest--;
          }
          else
          {
            std::string tmp ="";
            for(uint8_t i = charToTest+1; i < length; i++)
            {
              tmp = tmp + dict[0]; //tableau global
            }

            char c = (char)(first.at(charToTest)+1);

            first = first.substr(0,charToTest)
                  + c
                  + tmp;

            posFind = true;
          }
        }
      }
    }
  }
  std::cout<<toTest<<std::endl;
  exit(EXIT_SUCCESS);
}


std::vector<int> BruteForce::getCharNumberPerThread(int nb_threads) {
	int dict_length = dict.length();

	int default_nb_of_letters = floor(dict_length / nb_threads);
	int remaining_letters = dict_length % nb_threads;

	std::vector<int> nb_chars = {};

	for(int i = 0; i < nb_threads; i++) {
		int nb_chars_for_thread = default_nb_of_letters;
		if (remaining_letters > 0) {
			nb_chars_for_thread += 1;
			remaining_letters -= 1;
		}
		nb_chars.push_back(nb_chars_for_thread);
	}
	return nb_chars;
}
