#include "array.h"
#include <iostream>
#include <list>
#include <vector>
#include <functional>

struct Count
{
  int i;
public:
  Count():i(0) {}
  void operator()(int)
  {
    ++i;
  }
  
  int get() const
  {
    return i;
  }
};

int main()
{
  int yourMark = 1;
  //* 2-es
  // elso parameter: milyen tipusu elemeket tarol az Array.
  // masodik parameter: hany eleme van az Array-nek.
  // harmadik parameter: a default konstruktor ilyen elemmel 
  // toltse fel az Array osszes elemet.
  Array<int, 4, 7> ai;
  Array<char, 3, 'F'> d;
  const Array<int, 2, 2> ca;
  if (7 == ai.at(0) && 2 == ca.size())
    yourMark = ca.at(1);
  //*/
  
  //* 3-as
  ai[0] = ai[3] = 6;
  ai[1] = ai[2] = 10;
  if (2 == ca.front() && 6 == ai.back())
    yourMark = d.size();
  //*/
  
  //* 4-es
  // feladat a for_each_if (template fuggveny) implementalasa:
  std::vector<int> v;
  v.push_back(3);
  v.push_back(4);
  v.push_back(3);
  std::list<int> l;
  l.push_back(6);
  l.push_back(3);
  l.push_back(7);
  l.push_back(1);
  l.push_back(8);
  
  int m = 
    for_each_if(v.begin(), 
                v.end(), 
		std::bind2nd(std::equal_to<int>(), 3), 
		Count()).get();
		
  int k =
    for_each_if(l.begin(),
                l.end(),
		std::bind2nd(std::not_equal_to<int>(), 1),
		Count()).get();
  if (2 == m)
    yourMark = k;
  //*/
  
  //* 5-os
  const Array<int, 5, 4> a;
  const Array<int, 5, 3> b = a;
  if (4 == b[1] && 4 == b[2])
    yourMark = b.size();
  //*/
  std::cout << "Your mark is " << yourMark << std::endl;
  return 0;
}
