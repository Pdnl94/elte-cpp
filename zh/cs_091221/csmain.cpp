#include "cset.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <list>

struct Greater:std::binary_function<int, int, bool>
{
  bool operator()(const int& a,
                  const int& b) const
  {
    return a > b;
  }			    
};

struct LastDigitLess:std::binary_function<int, int, bool>
{
  bool operator()(const int& a,
                  const int& b) const
  {
    return ((a%10) < (b%10));
  }
};	    

const int max = 1000;
const int cacheSize = 2;

int main()
{
  int yourMark = 1;
  //* 2-es
  CachedSet<int, cacheSize> a;
  a.insert(1);
  a.insert(2);
  a.insert(3);
  
  CachedSet<std::string, max> t;
  for(int i = 0; i < max; ++i)
  {
    t.insert("TESTING");
  }  
  
  const CachedSet<int, cacheSize> ca = a;
  if (2 == ca.size() && 1==t.size())
  {
    yourMark = ca.count(1) + 
               ca.count(2) + 
	       ca.count(3) + 
	       ca.count(1);
  }
  //*/
  //* 3-as
  CachedSet<int, cacheSize> b;
  b.insert(2);
  b.insert(7);
  
  const CachedSet<int, cacheSize> un = ca.set_union(b);
  const CachedSet<int, cacheSize> is = ca.set_intersection(b);
  
  if(1==is.size() && 0==un.count(2) && 1==un.count(7))
  {
    yourMark = un.size()+un.count(3);
  }
  //*/
  //* 4-es  
  b.insert(4);
  CachedSet<int, cacheSize>::const_iterator ci = std::lower_bound(b.begin(), b.end(), 4);
  if (ci!=b.end())
    yourMark = *ci;
  //*/
  //* 5-os
  const int v[] = {2, 7};
  const int N = sizeof(v)/sizeof(v[0]);
  const CachedSet<int, cacheSize, Greater> f(v,v+N);
  
  std::list<int> l;  
  l.push_back(8);  
  l.push_back(12);
  const CachedSet<int, cacheSize, LastDigitLess> g(l.begin(), l.end());
  yourMark = *(g.begin()) - *(f.begin());
  //*/
  std::cout << "Your mark is " 
            << yourMark 
	    << std::endl;
}
