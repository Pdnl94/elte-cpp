#include "priority.h"
#include <algorithm>
#include <queue>
#include <list>
#include <iostream>
#include <deque>
#include <vector>

struct StringSizeLess
{
  bool operator()(const std::string& a, 
                  const std::string& b) const
  {
    return a.size() < b.size();
  }		  
};

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  PrioritySequence<std::list<double>, double> psd;
  psd.push_back(3, 4.3);
  psd.push_back(4, 8.7);
  psd.push_back(4, 6.5);
  
  PrioritySequence<std::list<int>, int> t;
  t.push_back(max, max);
  for(int i = 0; i < max; ++i)
  {
    t.push_back(i, i);
    t.pop_back();
  }
  
  const PrioritySequence<std::list<double>, double> cpsd = psd;
  
  PrioritySequence<std::deque<int>, int> pqi;
  pqi.push_back(6, 2);
  pqi.push_back(6, 6);
  pqi.push_back(6, 3);
  
  if (6.9 < cpsd.front() && 1 == cpsd.size(3) && 0 == t.front())
  {
    yourMark = pqi.front();
  }
  //*/
  //* 3-as
  ++pqi.front();
  if (pqi.front() == pqi.back())
  {
    yourMark = cpsd.size();
  }
  //*/
  //* 4-es
  PrioritySequence<std::vector<std::string> > pvs;
  pvs.push_back(3, "Hell");
  pvs.back()+="o";
  
  PrioritySequence<std::list<int>, int, double> pld;
  pld.push_back(3.2, 3);
  pld.push_back(3.8, 4);

  if ("Hello" == pvs.back())
    yourMark = pld.front();
  //*/  
  //* 5-os
  PrioritySequence<std::list<int>, int, std::string, StringSizeLess> p;
  p.push_back("longer", 5);
  p.push_back("short", 4);
  p.push_back("morelonger", 4);
  p.pop_back();
  yourMark = p.back();
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl(std::cout);
}
