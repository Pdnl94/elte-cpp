#include "stque.h"
#include <list>
#include <iostream>
#include <algorithm>

const int max = 10000;

int main()
{
  int yourMark = 1;
  //* 2-es
  StackQueue<int, true> st;
  st.push(3);
  st.push(4);

  StackQueue<double, false> q;
  q.push(5.33);
  q.push(4.78);

  const StackQueue<int, true> cst = st;

  if (4 == cst.get() && 5.33 == q.get())
    yourMark = cst.size();
  //*/
  //* 3-as
  st.pop();
  for(int i = 0; i < max; ++i)
  {
    st.push(i);
    st.pop();
  }
  if (!st.empty())
    yourMark = st.get();
  //*/
  //* 4-es
  ++st.get();
  StackQueue<int, true, std::list<int> > lsq;
  lsq.push(1);
  StackQueue<double, false, std::deque<double> > dsq;
  dsq.push(4.3);
  dsq.push(8.2);
  
  if (2 == dsq.size() && 1 == lsq.get())
    yourMark = st.get();
  //*/
  //* 5-os
  const std::stack<int> si = lsq.data();
  const std::queue<double> qd = dsq.data();
  const std::stack<int> csi = cst.data();
  yourMark = si.top() + qd.size() + csi.size();
  //*/
  std::cout << "Your mark is " << yourMark << std::endl;
  return 0;
}

