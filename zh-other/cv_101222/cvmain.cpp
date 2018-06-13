#include "cachevec.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <set>

struct UncachedContainer
{
};

const int max = 1000;

class Limited
{
  int v;
public:
  static int cnt;

  Limited( const int& i ): v ( i ) { }

  int get() const
  {
    return v;
  }
};

bool operator==( const Limited& a, const Limited& b )
{
  if ( Limited::cnt < max * 2 )
  {
    ++Limited::cnt;
    return a.get() == b.get();
  }
  else
  {
    throw UncachedContainer();
  }
}

int Limited::cnt = 0;

int main()
{
  int yourMark = 1;
  //* 2-es
  CachedVector<Limited> lim;
  CachedVector<int>     cvi;

  CachedVector<std::string> vec;
  vec.push_back( "Hello" );
  vec.push_back( "World" );
  const CachedVector<std::string> chw = vec;

  for( int i = 0; i < max; ++i )
  {
    lim.push_back( i );
    cvi.push_back( i );
  }
  for( int i = 0; i < max; ++i )
  {
    lim.contains( max / 2 );
  }
  if ( cvi.contains( max / 3 ) &&
       !cvi.contains( max ) )
  {
    yourMark = chw.size();
  }
  //*/
  //* 3-as
  for ( int i = 0; i < max - 1; ++i )
  {
    if ( cvi.contains( 0 ) )
    {
      cvi.erase( i + 1 );
    }
  }
  if ( "Hello" == chw[0] && 
       2 == lim[2].get() && 
       !cvi.contains( max / 2 ) )
  {
    yourMark += cvi.size();
  }
  //*/
  //* 4-es
  cvi.push_back( 3 );
  cvi.push_back( 1 );
  std::sort( cvi.begin(), cvi.end() );
  if ( 1 == cvi[1] )
  {
    yourMark = std::accumulate( cvi.begin(), cvi.end(), 0 );
  }
  //*/
  //* 5-os
  std::list<double> li;
  li.push_back( 3.2 );
  li.push_back( 1.1 );

  std::set<std::string> s;
  s.insert( "bla" );
  s.insert( "hello" );
  s.insert( "world" );

  const CachedVector<double> cl( li.begin(), li.end() );
  CachedVector<std::string> cs( s.begin(), s.end() );

  if ( cs.contains( "hello" ) && cl[0] > 2.5 )
  {
    yourMark = cs.size() + cl.size();
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
