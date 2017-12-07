#include "BruteForce.h"
#include <iostream>
#include <string>
#include <thread>
#include "sha.h"
#include <cmath>
#include <mutex>



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
	for(int i = 0; i < nbThreads; i++)
  {
		  int nbLetters = nb_chars.at(i);
		  std::string reducedDic ="";
		  for(int j = 0; j < nbLetters; j++)
      {
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
  //std::cout<<reducedDic<<std::endl;

  while(!find)
  {
	  ///////fonction search_word
	  
	  /////fonction change_last_letter param (first,toTest) return find (il faut que toTest soit modifié par la méthode)
    for(uint8_t i = 0; i<= dict.length()-1 && !find; i++)
    {
      toTest = first + dict[i];
      std::string dig = hashStringSHA256(toTest);
      if(encryptedString == dig )
        find = true;

      std::cout<<toTest<<std::endl;
    }
	///// fin fonction change_last_letter
    bool posFind = false;
    uint8_t charToTest = length-1;
    while(!posFind)
    {
	    /////fonction find_pos_letter_to_change param (posFind, charToTest,reducedDic,length) return first
      std::cout<<first<<std::endl;
      if(length == 0)// premier caractere
      {
	      ///// fonction set_first_letter param (reducedDic, length) return first length doit avoir changé en sorti de fonction
        first = reducedDic[0]; //élément tableau réduit
        posFind = true;
        length++;
	      /////fin fonction set_first_letter
      }
      else
      {
	      
        if(charToTest == 0 && first.at(charToTest) == reducedDic[reducedDic.length()-1]) //si on doit rajouter une lettre, on prend la première lettre de la plage du thread, et on complète par le premier caractère du dico complet jusqu'à avoir rajouté une lettre
        {
		////fonction add_letter param(reducedDic, length) return first length doit avoir changé en sorti de fonction
          first = reducedDic[0]; // élément tableau réduit
          for(uint8_t i = 1; i<= length; i++)
          {
            first =  first + dict[0];
          }
          length++;
          posFind = true;
		//// fin fonction add_letter
        }
        else
        {
          //int ascii = (int)first.at(charToTest);
          if(first.at(charToTest)== dict[dict.length()-1]) //si le charactère à tester est égale au dernier caractère du dico, alors on testera celui avant
          {
            charToTest--;
          }
          else
          {
            std::string tmp ="";
		  ////fonction set_end_of_first param(charToTest) return tmp
            for(uint8_t i = charToTest+1; i < length; i++)
            {
              tmp = tmp + dict[0]; //tableau global
            }
		 ////fin fonction get_end_of_first
	    //char c = (char)(first.at(charToTest)+1);
		  
		  ///fonction change_good_letter_from_first param (currentChar,first,tmp) return first
	    size_t currentChar = dict.find(first.at(charToTest)); // à changer il faut mettre une variable (attention avec le charToTest-- faudra appeler le find)
            first = first.substr(0,charToTest) ///je vois pas comment ça peut marche ça mdr faudrait que ça soit currentChar je suppose
                  + dict[currentChar+1]
                  + tmp;

            posFind = true;
          }
        }
      }
	    /////fin fonction find_pos_letter_to_change
    }
	  ////////fin fonction search_word
  }
  std::cout<<toTest<<std::endl;

  mtx.lock();
  result = toTest;
  mtx.unlock();

  exit(EXIT_SUCCESS);
}


std::vector<int> BruteForce::getCharNumberPerThread(int nb_threads) {

  int dict_length = dict.length();
	int default_nb_of_letters = floor(dict_length / nb_threads);
	int remaining_letters = dict_length % nb_threads;

	std::vector<int> nb_chars = {};

	for(int i = 0; i < nb_threads; i++)
  {
		int nb_chars_for_thread = default_nb_of_letters;
		if (remaining_letters > 0)
    {
			nb_chars_for_thread += 1;
			remaining_letters -= 1;
		}
		nb_chars.push_back(nb_chars_for_thread);
	}
	return nb_chars;
}
