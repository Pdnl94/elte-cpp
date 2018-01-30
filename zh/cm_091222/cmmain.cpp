#include "cachedmap.h"
#include <iostream>
#include <string>
#include <functional>
#include <algorithm>

class Check
{
  int cnt;
public:
  Check():cnt(0) {}
  
  void operator()(const std::pair<int, int>& a)
  {
    cnt += a.first;
    cnt += a.second;
  }
  
  int get() const
  {
    return cnt;
  }
};

struct StringSizeLess : std::binary_function<std::string, std::string, bool>
{
  bool operator()(const std::string& a, const std::string& b) const
  {
    return a.size() < b.size();
  }
};

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  const int cacheSize = 10;
  
  CachedMap<double, std::string> s(cacheSize);
  s.insert(3.7, "OK");
  
  CachedMap<int, int> mi(cacheSize);
  mi.insert(-1, 4);
  mi.insert(-2, 3);
  
  const CachedMap<int, int> cmi = mi;
  
  for(int i = 0; i <= max; ++i)
  {
    mi.insert(i, i);
  }
  
  if (mi.size() == cacheSize && 
      mi.get(max) == max &&
      4 == cmi.get(-1))
  {
    yourMark = cmi.size(); 
  }  
  //*/
  //* 3-as
  mi.insert(1, 4);
  mi.erase(max);
  --mi[1];
  if (mi.size() == cacheSize-1)
    yourMark = mi[1];
  //*/
  //* 4-es
  Check a;
  a = std::for_each(cmi.begin(), cmi.end(), a);
  yourMark = a.get();
  //*/
  //* 5-os rendezes
  CachedMap<std::string, int, StringSizeLess> marks(cacheSize);
  marks.insert("analizis", 2);
  marks.insert("cpp", 5);
  yourMark = marks.begin()->second;
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl(std::cout);
  return 0;
}
