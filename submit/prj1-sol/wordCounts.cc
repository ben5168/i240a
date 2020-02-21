#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <map>
#include <vector>
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

void format_word(std::string& str){
  std::string temp;
  for (const char &c : str){
    if((c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z')){
      temp += 'a' + ((c - 'A') % ('a' - 'A'));
    }
  }
  str = temp;
}

bool wordCountCompare(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b){
  if (a.second == b.second) {
    return a.first.compare(b.first) < 0;
  }
  return (a.second > b.second);
}

int main(int argc, char  *argv[]){
  typedef int Count;
  std::map<std::string, Count> m;
  long unsigned int maxWords, minLength, maxLength;
  std::string fileName;

  auto args = std::vector<std::string>(&argv[0], &argv[argc]);
  if (args.size() != 5){
    std::cerr << "Arguments not equal to 5. Program exiting." << std::endl;
    std::exit(1);
  }
  try{
    std::string::size_type size;
    maxWords = std::stoi(args[1], &size);
    if (args[1].length() != size){
      throw std::invalid_argument("invalid integer");
    }
  } catch (const std::invalid_argument& invalidArg){
    std::cerr << "Invalid Argument: " << invalidArg.what() << std::endl;
    std::exit(1);
  }
  try {
    std::string::size_type size;
    minLength = std::stoi(args[2], &size);
    if (args[2].length() != size){
      throw std::invalid_argument("Invalid Integer");
    }
  } catch(const std::invalid_argument& invalidArg){
    std::cerr << "Invalid Argument: " << invalidArg.what() << std::endl;
    std::exit(1);
  }
  try{
    std::string::size_type size;
    maxLength = std::stoi(args[3], &size);
    if (args[3].length() != size){
      throw std::invalid_argument("Invalid Integer");
    }
}catch (const std::invalid_argument& invalidArg){
   std::cerr << "Invalid Argument: " << invalidArg.what() << std::endl;
   std::exit(1);
 }
  if(minLength > maxLength){
    std::cerr << "Invalid Input: MIN_WORD_LEN cannot be larger than MAX_WORD_LEN" << std::endl;
    std::exit(1);
  }

  std::ifstream in(argv[4]);
  while (in.good()){
    std::string w;
    in >> w;
    format_word(w);
    if (w.length() > maxLength or w.length() < minLength) { continue; }
    m[w] += 1;
  }

  typedef std::pair<std::string, Count> WordCount;
  auto wordCounts = std::vector<WordCount>(m.begin(), m.end());
  sort(wordCounts.begin(), wordCounts.end(), wordCountCompare);
  for (auto i = 0u; i < maxWords; i++){
    std::cout << wordCounts[i].first << ": " << wordCounts[i].second << std::endl;
  }
  return 0;

  if (!in.eof()){
    std::cerr << "i/o error on file \""<< fileName << "\"" <<std::endl;
    std::exit(1);
  }
}
  
