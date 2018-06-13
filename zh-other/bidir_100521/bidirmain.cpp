#include "bimap.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <utility>
#include <string>

const int max = 1000;

struct Sum: std::unary_function<std::pair<int, int>, void> 
{
  int s;
  Sum():s(0) {}
  void operator()(const std::pair<int, int>& p)
  {
    s+=p.first;
    s+=p.second;
  }
};

int main()
{
  int yourMark = 1;
  //* 2-es
  BidirectionalMap<int, std::string> t;
  for( int i = 1; i < max; ++i )
  {
    t.insert( i, std::string( i, 'a' ) );
  }
  BidirectionalMap<char, int> sc;
  sc.insert( 'A', 65 );
  sc.insert( 'S', 83 );
  const BidirectionalMap<char, int> c = sc;
  
  if ( c.at( 'S' ) == 83 && 
       c.at( 65 ) == 'A' && 
       t.at( "aaaaa" ) == 5 )
  {
    yourMark = c.size();
  }
  //*/
  //* 3-as
  if (c.count(83) == 1 && c.count('V') == 0)
  {
    yourMark = t["a"] + t[2].length();
  }
  //*/
  //* 4-es:
  BidirectionalMap<int, int> f;
  f.insert(3, 18);
  f.insert(8, 2);
  f.insert(7, 5);
  f.insert(9, 1);
  const BidirectionalMap<int, int> cf = f;
  
  if( f.at(5) == 7 && 
      f.count(12) == 0 && 
      f.at(8) == 2)
  {
    yourMark = cf[18] + cf[9];
  }
  //*/
  //* 5-os
  const int i = std::for_each( cf.begin(), cf.end(), Sum()).s;
  yourMark = i / 10;
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
