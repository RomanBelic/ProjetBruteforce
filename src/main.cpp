#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cassert>
#include "cryptopp/cryptlib.h"
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>
#include "BruteForce.h"


int main() {

  BruteForce b;

  b.findWord(BruteForce::hashStringSHA256("kok"),4);
  //b.decryptSHA256(BruteForce::hashStringSHA256("abc"));

	return 0;
}

/*class BruteForce {

private:

  const uint8_t start_ascii = 32;
  const uint8_t end_ascii = 122;

public:


  BruteForce()
  {

  }

  BruteForce(std::string stringToHash)
	        :stringToHash(stringToHash)
  {
    encryptedString = BruteForce::hashStringSHA256(stringToHash);
    std::cout<< encryptedString <<std::endl;
    BruteForce::decryptSHA256(encryptedString);
  }


	~BruteForce() {

	}

  static std::string hashStringSHA256(std::string stringToHash)
  {
    std::string digest;
    CryptoPP::SHA256 hash;
    CryptoPP::StringSource foo(stringToHash,true,
      new CryptoPP::HashFilter(hash,
        new CryptoPP::Base64Encoder(
          new CryptoPP::StringSink(digest))));

    return digest;

  }

  std::string decryptSHA256(std::string encryptedString)
  {
    //if(encryptedString=="" || encryptedString == NULL)
    //  return NULL;

    bool find = false;
    std::string toTest;
    std::string stringToHash;
    std::string first = "";
    uint8_t length = 0;

    while(!find)
    {
      for(uint8_t i = 32; i<= 122 && !find; i++)
      {
        toTest = first + (char) i;
        std::string dig = BruteForce::hashStringSHA256(toTest);
        if(encryptedString == dig )
          find = true;
        if(i==32)
          i = 47;
        else if( i == 57)
          i = 64;
        else if( i == 90)
          i = 96;
        std::cout<<toTest<<std::endl;
      }

      bool posFind = false;
      uint8_t charToTest = length-1;
      while(!posFind)
      {
        std::cout<<first<<std::endl;
        if(length == 0)
        {
          first = (char)start_ascii;
          posFind = true;
          length++;
        }
        else
        {
          if(charToTest == 0 && first.at(charToTest) == (char)end_ascii)
          {
            first = (char)start_ascii;
            for(uint8_t i = 1; i<= length; i++)
            {
              first = first +(char)32;
            }
            length++;
            posFind = true;
          }
          else
          {
            int ascii = (int)first.at(charToTest);
            if(ascii == 122)
            {
              charToTest--;
            }
            else
            {
              std::string tmp ="";
              for(uint8_t i = charToTest+1; i < length; i++)
              {
                tmp = tmp + (char) 32;
              }

              char c=(char)(first.at(charToTest)+1);
              if(c == '!')
                c = '0';
              else if(c == ':')
                c = 'A';
              else if(c == '[')
                c = 'a';

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
    return toTest;
}

};
*/
