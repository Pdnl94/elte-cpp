#include "valmap.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <functional>

struct StringSizeLess : std::binary_function<std::string, std::string, bool>
{
  bool operator()(const std::string& a,
                  const std::string& b) const
  {
    return a.size() < b.size();
  }		  
};

struct Sum
{
  void operator()(const std::pair<std::string, int>& p)
  {
    i += p.first.size();
    i += p.second;
  }
  
  int get() const
  {
    return i;
  }
  
  Sum():i(0) {}
private:
  int i;
};

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  Valmap<std::string, int> m;
  for(int i = 0; i < max; ++i)
  {
    m.insert("Test", 0).insert("OK", 3);
  }
  const Valmap<std::string, int> cm = m;
  
  Valmap<int, std::string> t;
  t.insert(max, "A");
  t.inval(max);
  
  const Valmap<int, std::string> ct = t;
  
  if (1 == cm.count("OK") && 0 == ct.size() )
  {
    yourMark = cm.size() + ct.count(max);
  }
  //*/
  //* 3-as
  t.val(max);
  if (1 == t.count(max) && "A" == t[max])
  {
     yourMark = cm["OK"];
  }
  //*/
  //* 4-es
  m.inval("Test");
  Valmap<std::string, int>::const_iterator i = cm.begin();

  Sum s;
  s = std::for_each(m.begin(), m.end(), s);
  
  if (5 == s.get())
  {
    ++i;
    yourMark = i->first.size();
  }
  //*/
  //* 5-os
  Valmap<std::string, int, StringSizeLess> v;  
  v.insert("longerstring", 2).insert("shorter", 5).insert("short", 4);
  v.inval("short");
  Valmap<std::string, int, StringSizeLess>::const_iterator ci = v.begin();
  yourMark = ci->second;
  //*/
  std::cout << "Your mark is " 
            << yourMark;
  std::endl(std::cout);
  return 0;
}
