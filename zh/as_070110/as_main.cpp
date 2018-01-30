#include "as.h"
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <vector>

template <class T>
class Plus
{
  T a;
public:
  Plus(const T& t):a(t) {}
  T operator()(const T& t) const
  {
    return a+t;
  }
};

template <class T>
class Greater
{
  T a;
public:
  Greater(const T& t):a(t) {}
  bool operator()(const T& t) const
  {
    return t>a;
  }
};

int main()
{
  int yourMark(1);
  //* 2-es
  AssocSet<char, int> as;
  as.insert('a', 3);
  as.insert('T', 2);
  as.insert('T', 2);
  
  const AssocSet<std::string, int> cas;
  if (0 == cas.count("DNA", 42))
  {
    yourMark = as.count('a', 3) +
               as.count('T', 2);
  }
  //*/
  //* 3-as
  as.erase('T', 2);
  const AssocSet<char, int> c = as;
  if (0==as.erase('M', 34))
    yourMark += c.size();
  //*/
  //* 4-es
  std::multiset<int> m;
  m.insert(4);
  m.insert(3);
  m.insert(4);
  AssocSet<int, int> AS1(m.begin(), m.end(), 0);
  std::list<int> l;
  l.push_back(30);
  l.push_back(10);
  AssocSet<int, int> AS2(l.begin(), l.end(), 4);
  
  if (2 == AS1.size(0) && 2 == AS2.size())
  {
    yourMark = AS1.size() + AS2.size(4);
  }
  //*/
  //* 5-os
  std::vector<double> v;
  v.push_back(4.12);
  v.push_back(3.12);
  
  double a1[2];
  transform_if(v.begin(), v.end(), a1, Plus<double>(1.0), Greater<double>(2.11));
  
  int a2[2];
  transform_if(m.begin(), m.end(), a2, Plus<int>(1), Greater<int>(3));

  if (5.12 == a1[0] && 4.12 == a1[1])
    yourMark = a2[1];
  //*/
  std::cout << "Your mark is " << yourMark << std::endl;
  return 0;
}
