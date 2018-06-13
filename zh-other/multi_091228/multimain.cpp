#include <string>
#include <list>
#include <vector>
#include <functional>
#include "cms.h"
#include <iostream>
#include <map>
#include <numeric>
#include <algorithm>

const int max = 1000;
const int cache = 3;

struct Greater:std::binary_function<int, int, bool>
{
  bool operator()(const int& a, 
                  const int& b) const
  {
    return a > b;
  }		  
};

int main()
{
  int yourMark = 1;
  //* 2-es
  CachedMultiset<int, cache> t;
  CachedMultiset<std::string, cache> s;
  s.insert("Xmas");
  
  for(int i = max; i > 0; --i)
  {
    t.insert(i);
    s.insert("Testing");
  }
  const CachedMultiset<int, cache> ct = t;
  t.insert(2);
  if (2 == t.count(2) && 0 == ct.count(max))
    yourMark = s.count("Testing")-ct.count(2)-s.count("Xmas");
  //*/
  //* 3-as
  std::map<char, int> mc;
  mc['l'] = 2;
  mc['o'] = 1;
  mc['W'] = 1;
  CachedMultiset<char, 10> c(mc);
  c.insert('H').insert('e').insert('l').insert('l').insert('o');
  c.insert('W').insert('o').insert('r').insert('l').insert('d');
  
  std::map<double, int> md;
  md[1.25] = 1;
  CachedMultiset<double, cache> d(md);
  for(int i = 0; i < max; ++i)
    d.insert(1.25);
  
  if (8 == c.size() && 1 == d.size())
    yourMark = c.count('l') + c.count('W');
  //*/
  //* 4-es
  yourMark += (std::accumulate(c.begin(), c.end(), 0)%10);
  //*/
  //* 5-os
  std::list<int> l;
  l.push_back(5);
  std::vector<int> v;
  v.push_back(3);
  v.push_back(2);
  v.push_back(3);
  v.push_back(5);
  const CachedMultiset<int, cache, Greater> vm(v.begin(), v.end());
  const CachedMultiset<int, cache, Greater> lm(l.begin(), l.end());
  CachedMultiset<int, cache, Greater>::const_iterator i = vm.begin();
  if (1 == vm.count(3) && 1==lm.size())
    yourMark = *i;
  //*/
  std::cout << "Your mark is " 
            << yourMark;
  std::endl(std::cout);
  return 0;
}
