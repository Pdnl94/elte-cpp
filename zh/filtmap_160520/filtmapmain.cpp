#include <iostream>
#include "filtmap.h"
#include <string>
#include <algorithm>
#include "filtmap.h"
#include <map>
#include <functional>

class x
{

  int s;

public:

  x( int i = 0 ): s( i ) { }


  int get() const
  {
    return s;
  }

};

struct x_comp: std::binary_function<x, x, bool>
{

  bool operator()( const x& a, const x& b ) const
  {
    return a.get() > b.get();
  }

};

struct is_even: std::unary_function<int, bool>
{

  bool operator()( const int& i ) const
  {
    return 0 == i % 2;
  }
};

struct is_x_odd: std::unary_function<x, bool>
{

  bool operator()( const x& a ) const
  {
    return 0 != a.get() % 2;
  }

};

struct short_enough: std::unary_function<std::string, bool>
{

  bool operator()( const std::string& s ) const
  {
    return s.length() < 3;
  }
};

const int max = 1024;

int main()
{
  int your_mark = 1;
  //* 2-es
  filterable_map<int, int, is_even> id;

  for( int i = 0; i < max; ++i )
  {
    id.insert( i, i );
    id.set_filter_on();
    id.set_filter_off();
  }
  id.set_filter_on();
  const filterable_map<int, int, is_even> cid = id;
  id.set_filter_off();

  filterable_map<std::string, std::string, short_enough> ms;
  ms.insert( "Hello", "World" );
  ms.insert( "A", "B" );
  ms.set_filter_on();

  filterable_map<int, int, is_even> s;
  s.insert( 7, 5 );
  s.insert( 9, 1 );
  s.insert( 8, 5 );
  s.set_filter_on();
  if ( max / 2 == cid.size() && max == id.size() && 1 == ms.size() &&
       0 == ms.count( "A" ) && 0 == ms.count( "World" ) &&
       1 == ms.count( "Hello" ) && 0 == cid.count( max / 2 ) &&
       1 == cid.count( max - 1 ) && 1 == s.count( 7 ) && 0 == s.count( max ) )
  {
    your_mark = s.size();
  }
  //*/
  //* 3-as
  s.set_filter_off();
  s.at( 7 ) = 3;
  s.at( 8 ) = 2;
  ms.at( "Hello" ).push_back( '!' );

  if ( max - 1 == cid.at( max - 1 ) && 2 == s.at( 8 ) && 3 == s.size() )
  {
    your_mark = ms.at( "Hello" ).length() - s.at( 7 );
  }
  //*/
  //* 4-es
  filterable_map<x, x, is_x_odd, x_comp> xm;
  xm.insert( x( 2 ), x( 1 ) );
  xm.insert( x( 5 ), x( 4 ) );
  xm.set_filter_on();
  xm.at( x( 2 ) ) = x( 8 );

  if ( 1 == xm.size() && 8 == xm.at( x( 2 ) ).get() )
  {
    xm.set_filter_off();
    your_mark = xm.at( x( 5 ) ).get();
  }
  //*/
  //* 5-os
  const std::map<x, x, x_comp> mx = xm;
  const std::map<int, int> im = cid;
  const std::map<std::string, std::string> sm = ms;

  if ( max / 2 == im.size() && 2 == mx.size() && 
       1 == sm.count( "Hello" ) && 0 == im.count( max / 2 ) )
  {
    your_mark = mx.begin()->first.get();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
