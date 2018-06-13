#include "cgraph.h"
#include <string>
#include <iostream>

enum RGB
{
  red, green, blue
};

enum CYMK
{
  cyan, magenta, yellow, key
};

int main()
{
  int yourMark = 1;
  //* 2-es
  CGraph<int, RGB, true> cg1;
  CGraph<std::string, CYMK, false> cg2;
  
  cg1.add(3, red);
  cg1.add(7, blue);
  cg1.add(3,7);
  
  cg2.add("A", key);
  cg2.add("B", key);
  cg2.add("C", key);
  cg2.add("D", magenta);
  cg2.add("A","B");
  cg2.add("B","D");
  cg2.add("C","D");
  
  CGraph<std::string, CYMK, false> ccg2 = cg2;
  yourMark += (ccg2.is_directed() + cg1.is_directed());
  //*/
  
  //* 3-as
  if (ccg2.has("D","B") &&
      !cg1.has(7,3))
  {
    yourMark = ccg2.count(key);
  }
  //*/
  
  //* 4-es
  cg2["C"] = yellow;
  if (magenta == ccg2["D"] && yellow == cg2["C"])
    yourMark = ccg2.countNodes();
  //*/
  
  //* 5-os
  const CGraph<std::string, CYMK, true> d = ccg2;
  yourMark = d.countEdges() - cg1.countEdges();
  //*/
  std::cout << "Your mark is " << yourMark << std::endl;
}
