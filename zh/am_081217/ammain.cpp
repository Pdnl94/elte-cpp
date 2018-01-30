#include <iostream>
#include "amatrix.h"
#include <string>
#include <functional>
#include <algorithm>

struct Subjects
{
  int max;
  
  Subjects():max(0) {}
  
  void operator()(const std::pair<std::string, int>& p)
  {
    std::cout << ' ' << p.first 
              << ":" << p.second 
	      << std::endl;
    if (p.second > max)
      max = p.second;
  }
};

struct Print
{
  int best;
  
  Print():best(0) {}
  
  template <class Element>
  void operator()(const Element& e)
  {
     std::cout << e.first << ":" << std::endl;
     int i = std::for_each(e.second.begin(), e.second.end(), Subjects()).max;
     if (i > best)
       best = i;
  }
  
  
};

const int max = 10000;

int main()
{
  int yourMark = 1;
  //* 2-es
  AssocMatrix<std::string, int> jegyek;
  jegyek.set("PANGAAT.ELTE", "C++", 2);
  jegyek.set("SZZEDGT.ELTE", "Analizis", 5);
  jegyek.set("POZKACT.ELTE", "Numanal", 4);
  jegyek.set("POZKACT.ELTE", "Java", 3);
  
  AssocMatrix<int, std::string> t;
  t.set(4,2, "teszt");

  const AssocMatrix<std::string, int> cjegyek = jegyek;
  
  yourMark = cjegyek.get("PANGAAT.ELTE", "C++");
  //*/

  //* 3-as
  for(int k = 0; k<max; ++k)
    jegyek.set("POZKACT.ELTE", "Java", k);
  
  if (3 == cjegyek("POZKACT.ELTE", "Java"))
    yourMark = cjegyek.rows();
  //*/
  //* 4-es
  jegyek("PANGAAT.ELTE", "C++") = 4;
  
  if (4 == jegyek("PANGAAT.ELTE", "C++"))
    yourMark = jegyek.cols() + cjegyek.cols();
  //*/
  //* 5-os
  yourMark = std::for_each(cjegyek.begin(), cjegyek.end(), Print()).best;
  std::cout << std::endl;
  //*/
  
  std::cout << "Your mark is " << yourMark << std::endl;
  return 0;
}
