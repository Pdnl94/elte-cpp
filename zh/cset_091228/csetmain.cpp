#include "cachedset.h"
#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <functional>

struct Greater:std::binary_function<int, int, bool>
{
  bool operator()(const int& a, const int& b) const
  {
    return a > b;
  }
};

const int max = 1000;
const bool queue = true;

int main()
{
  int yourMark = 1;
  //* 2-es
  CachedSet<int, queue> q(2);
  q.insert(2);
  q.insert(1);
  q.insert(3);
  const CachedSet<int, queue> cq = q;
  
  CachedSet<std::string, !queue> s(2);
  s.insert("Hello");
  s.insert("World");
  s.insert("Test");
  const CachedSet<std::string, !queue> cs = s;
  
  if(0==cq.count(2) && 0 == cs.count("World"))
  {  
    yourMark = cq.count(max) + 
               cq.count(1) + 
	       cs.count("Hello");
  }
  //*/
  //* 3-as
  CachedSet<double, queue> t(max);
  for(int i = 0; i < max; ++i)
  {
    t.insert(4.3);
    t.erase(4.3);
  }
  q.erase(1);
  q.insert(2);
  q.erase(max);

  s.erase("Test");
  if (q.count(3) == q.count(2) && 0 == q.count(1))
    yourMark = cs.size() + s.size() + t.size();
  //*/
  //* 4-es
  CachedSet<int, queue, Greater> g(max);
  for(int i = max; i >= 1;  --i)
  {
    g.insert(i);
  }
  CachedSet<int, queue, Greater>::const_iterator it = g.begin();
  if (*it == max)
    yourMark = std::accumulate(cq.begin(), cq.end(), 0);
  //*/
  //* 5-os
  const std::stack<std::string> cst = cs.data();
  const std::stack<std::string> st = s.data();
  const std::queue<int> cque = q.data();
  if ("Test" == cst.top() && 3 == cque.front())
    yourMark = cst.size() + st.size() + cque.size();
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl(std::cout);
  return 0;
}
