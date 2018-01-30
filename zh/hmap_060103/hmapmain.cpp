#include <iostream>
#include <numeric>
#include <string>
#include "hashmap.h"

class Func {
  const int n;
public:
  Func(int i):n(i) { }
  
  int operator()(const std::string& s) const {
    return ((std::accumulate(s.begin(),s.end(),0)) % n );
  }
};

int main() {
  int yourMark = 1;
  const int buckets = 23;
  
  //* 2-es
  HashMap<std::string,std::string, Func> Directory(buckets);
  Directory.insert("Gipsz Jakab","1234534");
  Directory.insert("Bill Gates", "555-Billy");
  Directory.insert("Bjarne Stroustrup", "(70) 386-44-12");
  
  yourMark += Directory.size(16);
  //*/
  
  //* 3-as
  const HashMap<std::string, std::string, Func> CDirectory = Directory;
  
  if("555-Billy" == CDirectory.get("Bill Gates"))
    yourMark = CDirectory.size();
  //*/
  
  //* 4-es
    Directory.erase("Bill Gates");
    yourMark += (Directory.size() - CDirectory.size(22));
  //*/
  
  //* 5-os
  HashMap<std::string,std::string, Func2> Directory2(buckets);
  Directory2.insert("Gipsz Jakab","1234534");
  if (Directory.size(18) == Directory2.size(18))
    std::cout << "Use another hashing function!" << std::endl;
  else
    ++yourMark;
  //*/
  
  std::cout << "Your mark is " << yourMark << std::endl;
  
  return 0;
}
