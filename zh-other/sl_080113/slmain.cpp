#include "sl.h"
#include <deque>
#include <iostream>
#include <string>
#include <numeric>
#include <functional>
#include <vector>

struct Compare: std::binary_function<int, int, bool>
{
  bool operator()(int a, int b) const
  {
    return a > b;
  }
};

int main()
{
  int yourMark = 1;
  
  //* 2-es
  SortedList<int> li;
  SortedList<double> ls;
  ls.insert(5.6);
  ls.insert(3.2);
  li.insert(7);
  li.insert(2);
  li.insert(5);
  
  const SortedList<int> cli = li;
  if (3 == cli.size())
    yourMark = cli.front();
  //*/
  
  //* 3-as
  li.insert(8);
  li.remove(5);
  if (7 == cli.back())
    yourMark = cli.size();
  //*/
  
  //* 4-es
  const int N = std::accumulate(cli.begin(), cli.end(), 0);
  yourMark += (14 == N);
  //*/
  
  //* 5-os
  std::deque<int> d;
  d.push_back(2);
  d.push_back(1);
  d.push_back(3);
  
  const SortedList<int, Compare> lc1(d.begin(), d.end());
  
  std::vector<int> v;
  v.push_back(3);
  v.push_back(7);
  const SortedList<int, Compare> lc2(v.begin(), v.end());
  
  if (7 == lc2.front())
    yourMark = lc1.front() + lc2.size();
  //*/
  std::cout << "Your mark is " << yourMark << std::endl;
}
