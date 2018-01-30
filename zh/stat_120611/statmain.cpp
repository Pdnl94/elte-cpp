#include "stat.h"
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "stat.h"

struct StringSizeLess
{
  bool operator()( const std::string& a,
                   const std::string& b ) const
  {
    return a.size() < b.size();
  }
};

const int max = 1024;

int main()
{
  int yourMark = 1;
  //* 2-es
  std::vector<int> v1;
  v1.push_back( 2 );
  v1.push_back( 7 );
  v1.push_back( 8 );
  v1.push_back( 7 );
  const Statistics<std::vector<int>, int > stvec( v1 );
  std::list<double> ld;
  ld.push_back( 6.66 );
  ld.push_back( 8.11 );
  const Statistics<std::list<double>, double> cs( ld );
  std::deque<int> d;
  d.push_back( 3 );
  Statistics<std::deque<int>, int > stdeq( d );
  for( int i = 0; i < max; ++i )
  {
    stdeq.insert( i % 2 );
  }
  if ( sizeof( stvec ) != sizeof( cs ) &&
       cs.max() > 7.2 &&
       6 == stvec.average() &&
       3 == stdeq.max() &&
       stdeq.size() == max + 1 )
  {
    yourMark = cs.size();
  }
  //*/
  //* 3-as
  stdeq.insert( 1 );
  Statistics<std::vector<std::string>, std::string> strstat;
  strstat.insert( "Hello" );
  strstat.insert( "World" );
  if ( 3 == stdeq.numberOfDifferentElements() &&
       "World" == strstat.max() &&
       7 == stvec.mostFrequentElement() &&
       1 == strstat.count( "Hello" ) &&
       1 == stdeq.mostFrequentElement() )
  {
    yourMark = stvec.numberOfDifferentElements();
  }
  //*/
  //* 4-es
  Statistics<std::vector<int> > vs;
  vs.insert( 5 );
  vs.insert( 4 );
  const std::string msg = "Hello";
  const Statistics<std::string> sthello( msg );
  if ( 'l' == sthello.mostFrequentElement() &&
       4 == vs.min() &&
       "Hello" == strstat.min() )
  {
    yourMark = sthello.numberOfDifferentElements();
  }
  //*/
  //* 5-os
  strstat.insert( "Goodbye" );
  strstat.insert( "World" );
  strstat.insert( "!" );
  if ( "!" == strstat.min( StringSizeLess() ) &&
       "Goodbye" == strstat.max( StringSizeLess() ) )
  {
    yourMark = strstat.mostFrequentElement().length();
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
