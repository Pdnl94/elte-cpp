#include "valvec.h"
#include <iostream>
#include <algorithm>
#include <list>
#include <set>

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  Valvec<double> vd;
  for(int i = 0; i < max;++i)
  {
    vd.push_back(2.3);
    vd.inval(0);
  }

  Valvec<int> vi;  
  vi.push_back(2);
  vi.push_back(1);
  vi.push_back(2);
  vi.inval(0);
  const Valvec<int> c = vi;
  
  if (2 == c.size() )
  {
    vi.val(0);
    yourMark = vi.front(); 
  }
  //*/
  //* 3-as
  vi.inval(2);
  vi.pop_back();
  vi.val(1);
  if (c.front() != c.back())
  {
    yourMark = c.front() + vi.back();    
  }
  //*/
  //* 4-es
  vi.inval(1);
  Valvec<int>::const_iterator i1 = std::find(vi.begin(), vi.end(), 1);
  Valvec<int>::const_iterator i2 = std::find(vi.begin(), vi.end(), 2);
  if (i1 == vi.end() && i2 != vi.end())
  {
    yourMark = c.size() + *i2;
  }
  //*/
  //* 5-os
  std::list<int> l;
  l.push_back(3);
  l.push_back(8);
  l.push_back(1);
  std::set<std::string> s;
  s.insert("Hello");
  s.insert("World");
  const Valvec<std::string> vs(s.begin(), s.end());
  const Valvec<int> vl(l.begin(), l.end());
  if (8 == vl[1] && "Hello" == vs[0])
  {
    yourMark = vs.size() + vl[0];
  }
  //*/
  std::cout << "Your mark is " << yourMark 
            << std::endl;
  return 0;
}
