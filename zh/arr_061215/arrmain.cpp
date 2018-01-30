#include <iostream>
#include "array.h"
#include <functional>
#include <list>
#include <deque>

template <class T>
class Less: public std::unary_function<T, bool>
{
  T x;
public:
  Less(const T& t):x(t) {}
  bool operator()(const T& t) const
  {
    return t<x;
  }
};

template <class T>
class Print
{
  T s;
public:
  Print():s(0) {}
  void operator()(const T& a)
  {
    std::cout << a << ' ';
    s+=a;
  }
  T get() const 
  {
    return s;
  }
  
  ~Print()
  {
    std::cout << std::endl;
  }
};

int main() 
{
  int yourMark = 1;
  //* 2-es
  Array<int, 5> ai;
  Array<double, 3> ad(2.0);
  const Array<char, 2> ac('a');
  if ('a' == ac.at(0))
    yourMark = ac.size();
  //*/
  //* 3-as
  const Array<double, 3> cad = ad;
  ai[0] = ai[1] = ai[2] = 3;
  ai[3] = ai[4] = 1;
  const Array<int, 5> cai = ai;
  yourMark = cai[0];
  //*/
  //* 4-es
  std::list<int> ld;
  ld.push_back(ai[0]);
  ld.push_back(ai[3]);
  std::deque<int> di (ld.begin(), ld.end());
  di[1] = 42;
  
  Print<int> p1 = for_each_if(ld.begin(), ld.end(), Less<int>(2), Print<int>());
  Print<int> p2 = for_each_if(di.begin(), di.end(), Less<int>(10), Print<int>());
  
  if (1 == p1.get() && 3 == p2.get())
    yourMark = p1.get() + p2.get();
  
  //*/
  //* 5-os
  Print<double> p3 = for_each_if(cad.begin(), cad.end(), Less<double>(2.3), Print<double>());
  if ( 6.0 == p3.get())
    yourMark = ai.size();
  //*/
  std::cout << "Your mark is " << yourMark << std::endl;
  return 0; 
}
