#include "pstack.h"
#include <iostream>
#include <algorithm>
#include <string>

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
  priority_stack<double> sd;
  for(int i = 0; i < max; ++i)
    sd.push(i, 6.7);
  
  priority_stack<int> si;
  si.push(5, 2);
  si.push(5, 3);
  si.push(4, 7);
  const priority_stack<int> csi = si;
  if (1 == sd.size(0) && 3 == si.top())
  {
    yourMark = si.size(5);    
  }  
  //*/
  //* 3-as
  si.top() = 5;
  if (5 == si.top())
    yourMark = csi.size();
  //*/
  //* 4-es
  si.pop();
  si.pop();
  
  priority_stack<int, double> sid;
  sid.push(6.5, 4);
  
  if (si.size() == sid.size())
  {
    yourMark = sid.top();
  }
  //*/
  //* 5-os
  priority_stack<int, std::string, StringSizeLess> strst;
  strst.push("abcdg", 5);
  strst.push("dfg", 4);
  if (2 == strst.size())
    yourMark = strst.top();
  //*/
  std::cout << "Your mark is " << yourMark
            << std::endl;
  return 0;
}
