#include <iostream>
#include "setops.h"
#include <set>
#include "setops.h"
#include <algorithm>
#include <iterator>
#include <string>
#include <numeric>

struct string_size_less
{

  bool operator()( const std::string& a,
                   const std::string& b )
  {
    return a.size() < b.size();
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  std::set<int> si;
  for( int i = 0; i < max; ++i )
  {
    si.insert( i );
  }

  std::set<std::string> msgs;
  msgs.insert( "Hi" );
  msgs.insert( "Hello" );
  msgs.insert( "Ciao" );
  msgs.insert( "Aloha" );

  set_operations<std::string> ops( msgs );
  const set_operations<std::string> cops( msgs );

  set_operations<int> opi( si );
  for( int i = 0; i < max; ++i )
  {
    opi.complement();
  }

  ops.complement();

  if ( cops.contains( "Hi" ) && opi.contains( max / 2 ) &&
       !ops.contains( "Ciao" ) && !ops.contains( "Aloha" ) &&
       !opi.contains( 2 * max ) && !cops.contains( "?" ) &&
       !cops.contains( "NullPointerException" ) && ops.contains( "C++" ) )
  {
    your_mark += ops.contains( ":-D" );
  }
  //*/
  //* 3-as
  std::set<std::string> w;
  w.insert( ":-)" );
  w.insert( ":-P" );
  w.insert( "Ciao" );
  ops.set_union( w );

  std::set<int> nums;
  nums.insert( max / 2 );
  nums.insert( max / 3 );
  nums.insert( max );

  opi.complement();
  opi.set_union( nums );
  opi.complement();

  if ( !opi.contains( max / 2 ) && opi.contains( max / 4 ) &&
       ops.subset( w ) && !cops.subset( w ) &&
       !ops.contains( "Hi" ) && ops.contains( "Ciao" ) &&
       ops.contains( ":-P" ) && !cops.contains( ":-P" ) )
  {
    ops.complement();
    your_mark += ops.contains( "Aloha" ) && !ops.contains( "Ciao" );
  }
  //*/
  //* 4-es
  std::set<std::string, string_size_less> x;
  x.insert( "Hello" );
  x.insert( "Ciao" );

  std::set<std::string, std::greater<std::string> > a;
  a.insert( ":-o" );

  set_operations<std::string> m( x );
  m.set_union( a );

  if ( !m.contains( ":-/" ) && !m.subset( msgs ) )
  {
    your_mark += m.contains( "Hello" );
  }
  //*/
  //* 5-os
  m += cops;
  m += ops;

  if ( m.contains( ":-o" ) && m.contains( "Aloha" ) )
  {
    your_mark += m.contains( "Ciao" );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
