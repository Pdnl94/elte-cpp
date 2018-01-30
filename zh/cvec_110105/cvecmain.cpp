#include "cachevec.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <set>
#include <functional>

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

struct Predicate: std::unary_function<int, bool>
{
  bool operator()( const int& i ) const
  {
    return ( 0 == (i % 2) );
  }
};

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
    lim.index_of( max / 2 );
  }

  if ( max / 3 == cvi.index_of( max/3 ) &&
       cvi.not_in_vec() == cvi.index_of( max ) )
  {
    yourMark = chw.size();
  }
  //*/
  //* 3-as
  int idx = cvi.index_of( 1 );
  cvi[0] = 1;
  ++cvi[1];
  
  for ( int i = 3; i < max ; ++i )
  {
    cvi.erase( i );
  }

  if ( "Hello" == chw[0] && 
       idx != cvi.index_of( 1 ) &&
       2 == lim[2].get() && 
       cvi.not_in_vec() == cvi.index_of( max / 2 ) )
  {
    yourMark = cvi[0] + cvi[1];
  }
  //*/
  //* 4-es
  for( int i = 0; i < max; ++i)
  {
    cvi.push_back( i );
  }
  if ( 0 == cvi.predicate_index_of( std::not1( Predicate() ) ) )
  {
    yourMark += cvi.predicate_index_of( Predicate() );
  }
  //*/
  //* 5-os
  std::list<double> li;
  li.push_back( 6.38 );
  li.push_back( 1.4 );

  std::set<std::string> s;
  s.insert( "c++" );
  s.insert( "hello" );
  s.insert( "world" );

  const CachedVector<double> cl( li.begin(), li.end() );
  CachedVector<std::string> cs( s.begin(), s.end() );

  if ( 1 == cs.index_of( "hello" ) && cl[0] > 2.5 )
  {
    yourMark = cs.size() + cl.size();
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
