#include <iostream>
#include "mlset.h"
#include <string>
#include <list>
#include "mlset.h"

struct StringSizeLess
{
  bool operator()( const std::string& a, const std::string& b ) const
  {
    return a.size() < b.size();
  }
};

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  multilevel_set<std::string> s;
  s.insert( "Hello" );
  s.insert( "World" );
  s.insert( "World" );
  s.insert( "Hello" );
  s.insert( "Hello" );
  const multilevel_set<std::string> c = s;

  multilevel_set<int> x;
  for( int i = 0; i < max; ++i )
  {
    x.insert( i );
    x.insert( i + 1 );
  }

  if ( 3 == c.count( "Hello" ) && 3 == c.height() && 0 == c.count( "C++" ) &&
       x.count( 0 ) != x.count( 1 ) && 2 == x.count( max / 2 ) )
  {
    if ( c.size( 0 ) == c.size( 1 ) &&
         c.size( 1 ) != c.size( 2 ) &&
         2 == c.size( 1 ) )
    {
      yourMark = c.count( "World" );
    }
  }
  //*/
  //* 3-as
  s.remove( "World" );
  if ( 0 == s.count( "World" ) && 2 * max == x.size() )
  {
    yourMark = s.size();
  }
  //*/
  //* 4-es
  multilevel_set<std::string, StringSizeLess> p;
  p.insert( "AAA" );
  p.insert( "BBB" );
  p.insert( "CCC" );
  p.insert( "DDD" );
  if ( 4 == p.height() )
  {
    yourMark = p.count( "EEE" );
  }
  //*/
  //* 5-os
  std::string msg = "Hello World";
  multilevel_set<char> hw( msg.begin(), msg.end() );
  std::list<int> li;
  li.push_back( 1 );
  li.push_back( 3 );
  li.push_back( 1 );
  multilevel_set<int> ls( li.begin(), li.end() );

  if ( 3 == hw.height() && 2 == hw.count( 'o' ) )
  {
    yourMark = ls.size() + ls.count( 3 ) + hw.count( 'e' );
  }
  //*/
  std::cout << "Your mark is "
            << yourMark;
  std::endl( std::cout );
}
