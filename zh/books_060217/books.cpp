#include <iostream>
#include <string>
#include <functional>
#include "ommap.h"

struct Print 
{
  int c;
  Print():c(0) { }
  void operator()(const std::pair<std::string, std::string>& p)
  {
    std::cout << p.first << ':' << p.second << std::endl;
    c+=p.first.length();
  }
};

int main()
{
  int yourMark = 1;
  //* 2-es
  OrderedMMap<std::string, std::string> cppbooks;
  cppbooks.insert("Bjarne Stroustrup", "The C++ Programming Language");
  cppbooks.insert("Scott Meyers", "Effective C++");
  cppbooks.insert("Scott Meyers", "More Effective C++");
  cppbooks.insert("Scott Meyers", "Effective STL");
  cppbooks.insert("Herb Sutter", "Exceptional C++");
  cppbooks.insert("Herb Sutter", "More Exceptional C++");
  cppbooks.insert("Herb Sutter", "Exceptional C++ Style");
  cppbooks.insert("Herb Sutter", "C++ Coding Standards");
  
  const OrderedMMap<std::string, std::string> ccppbooks = cppbooks;
  
  if ("Effective STL"==ccppbooks.at("Scott Meyers", 2))
    ++yourMark;
  //*/
  
  //* 3-as
  cppbooks.erase("Herb Sutter", 3);
  yourMark = cppbooks.size() - ccppbooks.count("Herb Sutter");
  //*/
  
  //* 4-es
  cppbooks("Scott Meyers",0).swap(cppbooks("Scott Meyers",1));
  if ("C++ Coding Standards" == ccppbooks("Herb Sutter",3))
    ++yourMark;
  //*/
  
  //* 5-os
  if (86 == std::for_each(cppbooks.begin(), cppbooks.end(), Print()).c)
    ++yourMark;
  //*/
  
  std::cout << "Your mark is " << yourMark << std::endl;
  return 0;
}
