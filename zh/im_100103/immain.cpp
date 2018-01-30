#include "invmap.h"
#include <iostream>
#include <functional>
#include <list>
#include <map>
#include <string>
#include <algorithm>

class Sum
{
  int s;
public:  
  void operator()(const std::pair<int, int>& a)
  {
    s+=a.first;
    s+=a.second;
    ++s;    
  }
  
  Sum():s(0) {}
  
  int get() const
  {
    return s;
  }
};

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  Invmap<int> id;
  for(int i = 0; i < max; ++i)
  {
    id.insert(i,i);
  }
  
  Invmap<std::string> phones;
  phones.insert("Aniko", "+3670-555-4242");
  phones.insert("Botond", "+3630-555-1234");
  const Invmap<std::string> cp = phones;
  if (cp.get("Aniko") == "+3670-555-4242" &&
      cp.get("+3630-555-1234")=="Botond")
  {
    yourMark = cp.size();
  }
  //*/
  //* 3-as
  for(int i = 2; i < max; ++i)
  {
    id.remove(i);
  }
  phones.remove("+3630-555-1234");
  if (cp["+3630-555-1234"]=="Botond" && cp["Aniko"] == "+3670-555-4242")
  {
    yourMark = id.size()+phones.size();
  }  
  //*/
  //* 4-es
  Sum s;
  s = std::for_each(id.begin(), id.end(), s);
  yourMark = s.get();
  //*/
  //* 5-os
  std::map<double, double> m;
  m[2.4] = 5.4;
  m[7.5] = 8.5;
  const Invmap<double> cm(m.begin(), m.end());
  
  std::list<std::pair<int, int> > l;
  l.push_back(std::make_pair(5, 2));
  l.push_back(std::make_pair(1, 6));
  const Invmap<int> cl(l.begin(), l.end());
  if (cl.size() == 2 && 8.5 == cm[7.5])
    yourMark = cm.size() + cl[6] + cl[5];  
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl(std::cout); 
  return 0;
}
