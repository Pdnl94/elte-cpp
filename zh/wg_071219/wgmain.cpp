#include <iostream>
#include <string>
#include "wgraph.h"

int main()
{
  int yourMark = 1;
  
  //* 2-es
  WGraph<char, double, true> dirgraph;
  WGraph<std::string, int, false> undirgraph;
  dirgraph.add('A');
  dirgraph.add('B');
  dirgraph.add('C');
  dirgraph.add('A', 'B', 4.54);
  dirgraph.add('C','A', 6.32);
  undirgraph.add("AA", "BB", 3);
  const WGraph<std::string, int, false> c = undirgraph;
  yourMark += (c.is_directed() + dirgraph.is_directed());
  //*/
  //* 3-as
  if (!dirgraph.has('B', 'A') &&
      c.has("BB", "AA"))
  {
    yourMark = c.weight("BB", "AA");
  }
  //*/
  //* 4-es
    dirgraph.weight('A','B') = 7.32;
    undirgraph.weight("BB", "AA") = 7;
    dirgraph.remove('A','B');
    if (1 == dirgraph.countEdges() && 
        7 == undirgraph.weight("AA", "BB"))
    {
      yourMark += c.countEdges();
    }
  //*/
  //* 5-os
    dirgraph.add('D');
    dirgraph.add('E');
    dirgraph.add('F');
    dirgraph.add('G');
    dirgraph.add('A', 'D', 4.32);
    dirgraph.add('A', 'E', 5.6);
    dirgraph.add('E', 'D', 3.2);
    dirgraph.add('C', 'F', 5.11);
    dirgraph.add('C', 'A', 8.91);
    dirgraph.add('F', 'A', 3.76);
    dirgraph.add('A', 'B', 2.13);
    dirgraph.add('A','G', 8.98); 
    dirgraph.remove('C');
    yourMark = dirgraph['A'].countEdges();
  //*/
  std::cout << "Your mark is " << yourMark << std::endl;
}
