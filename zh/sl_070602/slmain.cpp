#include "sl.h"
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
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
  SortedList<int> a;
  a.insert(3);
  a.insert(4);
  a.insert(2);
  const SortedList<int> ca = a;

  if (3 == ca.size())
    yourMark = ca.front();
  //*/
  
  //* 3-as
  a.insert(5);
  a.remove(2);
  SortedList<int> b;
  b = a;
  if (5 == b.back())
    yourMark = b.front();
  //*/
  
  //* 4-es
  const int c = std::for_each(ca.begin(), ca.end(), Print()).c;
  yourMark += (9 == c);
  //*/
  
  //* 5-os
  std::vector<int> l;
  l.push_back(13);
  l.push_back(10);
  l.push_back(43);
  l.push_back(15);
  const SortedList<int, Compare> vsl(l.begin(), l.end());
  
  std::deque<int> d;
  d.push_back(2);
  d.push_back(5);
  const SortedList<int, Compare> dsl(d.begin(), d.end());
  
  if (43 == vsl.front() && 10 == vsl.back())
    yourMark = dsl.front();
  //*/
  
  std::cout << std::endl << "Your mark is " << yourMark << std::endl;
  return 0;
}
