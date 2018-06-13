#include "lgraph.h"
#include <iostream>
#include <string>

int main()
{
  int yourMark = 1;
  //*2-es
  LGraph<int, std::string, true> dg;
  dg.add(1);
  dg.add(2);
  dg.add(3);
  dg.add(8);
  dg.add(2,1, "Ady utca");
  dg.add(1,3, "Kossuth utca");
  dg.add(2,3, "Nap utca");
  dg.add(8,3, "Lehel utca");
  const LGraph<int, std::string, true> cdg = dg;
  LGraph<char, std::string, false> ug;
  ug.add('A');
  ug.add('G');
  ug.add('H');
  ug.add('A','H', "Baross utca");
  yourMark += cdg.is_directed() + ug.is_directed();
  //*/
  
  //* 3-as
  if (!cdg.has("Ilyen nincs") &&
      "Kossuth utca" == cdg(1,3))
  {
    yourMark = ug.countNodes();
  }
  //*/
  
  //* 4-es
  dg(2,3) = "Hunyadi utca";
  
  if (4 == cdg.countEdges() && 
      !dg.has("Nap utca"))
  {
    dg.remove(1);
    yourMark = ug.countEdges() + dg.countNodes();
  }
  //*/
  
  //* 5-os
  const LGraph<char, std::string, true> cdg2 = ug;
  const LGraph<char, std::string, false> cdg3 = ug;
  if  (1 == cdg3.countEdges())
    yourMark = cdg2.countEdges() + cdg2.countNodes();
  //*/
  std::cout << "Your mark is " << yourMark << std::endl;
  return 0;
}
