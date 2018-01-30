#include "stque.h"
#include <list>
#include <iostream>
#include <algorithm>
#include <string>

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
  const std::stack<int> st_stack = st.get_stack();
  const std::queue<int> cst_queue = cst.get_queue();
  const std::queue<double> q_que = q.get_queue();
  
  const int si = q_que.size() + st_stack.size() + cst_queue.size();
  
  if (3 == si && q_que.size() > st_stack.size() )
    yourMark = st_stack.top();
    
  //*/
  //* 5-os
  std::list<int> l;
  l.push_back(6);
  l.push_back(5);
  l.push_back(17);
  
  std::deque<std::string> d;
  d.push_back("abcd");
  d.push_back("fgh");
  
  StackQueue<int, true, std::deque<int> > stackVect(l.begin(), l.end());
  StackQueue<std::string, false, std::list<std::string> > qList(d.begin(), d.end());
  
  if (17 == stackVect.get() && "abcd" == qList.get())
    yourMark = l.size() + qList.get_queue().size();
  //*/
  std::cout << "Your mark is " << yourMark << std::endl;    
  return 0;
}
