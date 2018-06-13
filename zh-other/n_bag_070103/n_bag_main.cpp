#include "nbag.h"
#include <vector>
#include <iostream>
#include <list>

struct IsOdd
{
  bool operator()(const int& i) const
  {
    return 1==i%2;
  }
};

int main()
{
  int yourMark(1);
  //* 2-es
  NBag<int, 3> bi;
  bi.insert(0, 3);
  bi.insert(0, 3);
  bi.insert(0, 3);
  bi.insert(1, 1).insert(1,3);
  bi.insert(2,2).insert(2,3);
  const NBag<double, 2> cbd;
  if (0==cbd.size())
    yourMark = cbd.getN();
  //*/
  //* 3-as
  const NBag<int, 3> cbi = bi;
  bi.insert(0,4);
  yourMark = cbi.mul(0,3);
  //*/
  //* 4-es
  bi.insert(1,3);

  std::vector<int> v;
  for(int i = 0; i < bi.getN(); ++i)
  {
    v.push_back(bi.mul(i,3));
  }
  
  std::list<int> l;
  l.push_back(bi.getN());
  l.push_back(cbd.getN());
  
  int a1[2];
  copy_if(v.begin(), v.end(), a1, IsOdd());
  
  int a2[1];
  copy_if(l.begin(), l.end(), a2, IsOdd());
  
  if (3 == a2[0])
    yourMark = a1[0] + a1[1];
  //*/
  //* 5-os
  NBag<int, 4> a;
  a.insert(0,1).insert(0,3).insert(1,1);
  
  NBag<int, 4> b;
  b.insert(0,3).insert(1,3);
  NBag<int, 4> Bagunion1 = a + b;
 
  NBag<double, 1> d1a;
  d1a.insert(0, 3.14);
  NBag<double, 1> d1b;
  d1b.insert(0, 2.43);
  d1b.insert(0, 3.14);
  NBag<double, 1> Bagunion2 = d1a + d1b;
  
  if (2 == Bagunion2.mul(0, 3.14) && 
      1 == Bagunion2.mul(0, 2.43))
  {
    yourMark = Bagunion1.mul(0,3) +
               Bagunion1.mul(1,3) +
	       Bagunion1.mul(1,1) +
	       Bagunion1.mul(0,1);
  }
  //*/
  std::cout << "Your mark is " << yourMark << std::endl;
  return 0;
}
