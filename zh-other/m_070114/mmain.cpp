#include "matrix.h"
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

struct Compare
{
  template <class T>
  bool operator()(const T& a, const T& b) const
  {
    return a<b;
  }
};

int main()
{
  int yourMark(1);
  //* 2-es
  Matrix<double, 1, 1> m1;
  const Matrix<char, 2, 2> m2('A');
  
  if ('A' == m2.at(1,0) && 'A' == m2.at(0,1))
    yourMark = m2.rows();
  //*/
  //* 3-as
  std::list<int> l;
  l.push_back(45);
  l.push_back(30);
  l.push_back(20);
  l.push_back(3);
  slow_sort(l.begin(), l.end());
  
  std::vector<double> d;
  d.push_back(2.1);
  d.push_back(1.3);
  d.push_back(1.5);
  slow_sort(d.begin(), d.end());
  
  if (2.1 == d[2])
    yourMark = *(l.begin());
  //*/
  //* 4-es
  m1(0,0) = 4.15;
  const Matrix<double, 1, 1> cm1 = m1;
  m1(0,0) = 2.4;
  if (cm1(0,0) == 4.15)
    yourMark += (m1(0,0) == 2.4);
  
  //*/
  //* 5-os
  slow_sort(d.begin(), d.end(),Compare());
  slow_sort(l.begin(), l.end(),Compare());
  if (1.5 == d[1])
    yourMark = *(l.begin()) % 10;

  //*/
  std::cout << "Your mark is " << yourMark << std::endl;
  return 0;
}
