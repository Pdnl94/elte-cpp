#include "sv.h"
#include <iostream>
#include <functional>
#include <algorithm>
#include <list>
#include <deque>

struct Compare: std::binary_function<int, int, bool>
{
  bool operator()(int a,
                  int b) const
  {
    return a > b;
  }
};

struct Print
{
  int c;
  Print() : c(0) {}
  void operator()(int a)
  {
    c += a;
    std::cout << a << ' ';
  }
};

int main()
{
  int yourMark = 1;
  //* 2-es
  SortedVector<int> svi;
  svi.insert(32);
  svi.insert(3);
  svi.insert(10);
  const SortedVector<int> csvi = svi;

  if (3 == csvi.at(0))
    ++yourMark;
  //*/
  
  //* 3-as
  svi.insert(44);
  if (32 == csvi[2] && 44 == svi[3])
    yourMark = csvi.size();
  //*/
  
  //* 4-es
  const int c = std::for_each(csvi.begin(), csvi.end(), Print()).c;
  if (45 == c)
    yourMark = svi.size();
  //*/
  
  //* 5-os
  std::list<int> l;
  l.push_back(10);
  l.push_back(4);
  l.push_back(7);
  l.push_back(5);
  const SortedVector<int, Compare> lsv(l.begin(), l.end());
  
  std::deque<int> d;
  d.push_back(10);
  d.push_back(44);
  const SortedVector<int, Compare> dsv(d.begin(), d.end());
  
  if (7 == lsv[1] && 2 == dsv.size())
    yourMark = lsv[2];
  //*/
  
  std::cout << std::endl << "Your mark is " << yourMark << std::endl;
  return 0;
}
