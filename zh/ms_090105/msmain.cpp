#include <iostream>
#include <functional>
#include <set>
#include <deque>
#include <string>
#include "multiable.h"

struct Compare: std::binary_function<int, int, bool>
{
  bool operator()(const int& a, const int& b) const
  {
    return a > b;
  }
};

const int max = 10000;

int main()
{
  int yourMark = 1;
  //* 2-es
  MultiableSet<int, true> mi;
  MultiableSet<std::string, false> nms;
  
  mi.insert(3).insert(4).insert(3);
  
  nms.insert("Hello").insert("World").insert("Hello");
  
  const MultiableSet<int, true> cmi = mi;
  const MultiableSet<std::string, false> cnms = nms;
  
  if (3 == cmi.size())
    yourMark = cnms.size();
  //*/
  //* 3-as
  MultiableSet<int, false> nmt;
  MultiableSet<int, true> mt;
  for(int i = 0; i < max; ++i)
  {
    mt.insert(0);
    nmt.insert(0);
    nms.insert("Testing");
    nms.insert("Checking");
  }
  nms.erase("Checking");
  
  if (cmi.count(4) == nmt.count(0) && mt.count(0) == max)
    yourMark = nms.size();
  //*/
  //* 4-es
  const int v[] = {3, 1, 2, 1, 2, 1, 1};
  const int N = sizeof(v) / sizeof(v[0]);
  
  std::deque<int> d(v, v + N);
  
  MultiableSet<int, true, Compare> m1;
  MultiableSet<int, false, Compare> m2;
  
  m1.insert<const int*>(v, v + N);
  m2.insert(d.begin(), d.end());
  
  Compare c = m1.key_comp();
  
  if (3 == m2.size())
    yourMark = m1.count(1);
  //*/
  //* 5-os
  const std::multiset<int, Compare> m = m1.data();
  const std::set<int, Compare> s = m2.data();
  
  if (3 == s.size())
    yourMark = m.size() - m.count(2);
  //*/
  std::cout << "Your mark is " << yourMark << std::endl;
}
