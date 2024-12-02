/* 
Name: Jay Kumar Roy
Email: jroy4@crimson.ua.edu
Course Section: Fall 2024 CS 201
Homework #: 2
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "ST.hpp"
#include <regex>

using namespace std;

// Use default c++ sorting algorithm to sort the parsed text in the vectors
int main(int argc, char *argv[]) {

   if (argc < 2) {
      std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
      return 1;
   }

   std::ifstream fp1(argv[1]);
   if (!fp1.is_open()) {
      std::cerr << "Error: Could not open file " << argv[1] << std::endl;
      return 1;
   }

    auto timestart = std::chrono::high_resolution_clock::now();


   std::string text;
   ST<std::string, int> wordFrequencyST;
   const std::regex delim("\\s+"); 

   while (fp1 >> text) {
      auto begin = std::sregex_token_iterator(text.begin(), text.end(), delim, -1);
      auto end = std::sregex_token_iterator();
      for (std::sregex_token_iterator word = begin; word != end; word++) {
         if (!word->str().empty()) {
               wordFrequencyST[*word]++;  
         }
      }
   }

    auto timeend = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeend - timestart);

   fp1.close();

   std::cout << "Word Frequencies (in sorted order):" << std::endl;
   wordFrequencyST.display();

   std::cout << "Total number of unique words: " << wordFrequencyST.size() << std::endl;
   std::cout << "Time taken by function: " << duration.count() << " microseconds" << endl;


   return 0;
}