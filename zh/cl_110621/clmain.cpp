#include <set>
#include <string>
#include "clist.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "clist.h"

const int max = 1000;

class Uncached{};

class Limited
{
  int val;
public:
  static int cnt;

  Limited( int i ): val( i ) {}
  
  int get() const
  {
    return val;
  }
};

int Limited::cnt = 0;

bool operator==( const Limited& a, const Limited& b )
{
  if( Limited::cnt < 3 * max )
  {
    ++Limited::cnt;
    return a.get() == b.get();
  }
  else
  {
    throw Uncached();
  }
}

int main()
{
  int yourMark = 1;
  //* 2-es
  cached_list<char> lc;
  lc.push_back( 'H' ).push_back( 'e' ).push_back( 'l' ).push_back( 'l' ).push_back( 'o' );
  lc.push_back( 'W' ).push_back( 'o' ).push_back( 'r' ).push_back( 'l' ).push_back( 'd' );

  cached_list<double> ld;
  ld.push_back( 5.2 );
  ld.push_front( 2.1 );

  cached_list<Limited> clim;
  for( int i = 0; i < max; ++i )
  {
    clim.push_back( i * 2 );
  }

  for( int i = 0; i < max; )
  {
    if ( clim.contains( max ) )
    {
      ++i;
    }
  }
  if ( clim.contains( max ) && ld.front() < 3.1 )
  {
    if ( 'H' == lc.front() && !clim.contains( max * max ) )
    {
      yourMark = ld.size();
    }
  }
  //*/
  //* 3-as
  const cached_list<char> clc = lc;
  lc.unique();
  if ( 'd' == clc.back() && 9 == lc.size() )
  {
    yourMark += ( clc.size() - lc.size() );
  }
  //*/
  //* 4-es
  yourMark = std::count( clc.begin(), clc.end(), 'l' ) +
             std::count( clc.begin(), clc.end(), 'H' );
  //*/
  //* 5-os
  std::set<int> si;
  si.insert( 8 );
  si.insert( 3 );
  si.insert( 1 );
  
  std::vector<std::string> vs;
  vs.push_back( "Hello" );
  vs.push_back( "World" );
  
  const cached_list<int> csi( si.begin(), si.end() );
  const cached_list<std::string> cvs( vs.begin(), vs.end() );
  
  if ( 8 == csi.back() && "Hello" == cvs.front() )
  {
    yourMark = csi.size() + cvs.size();
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
