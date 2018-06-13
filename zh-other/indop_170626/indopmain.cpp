#include <vector>
#include <iostream>
#include "indops.h"
#include <deque>
#include "indops.h"
#include <string>
#include <algorithm>
#include <vector>

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  std::string msg = "Hello World";
  std::deque<int> d;
  d.push_back( 4 );
  d.push_back( 3 );
  d.push_back( 7 );
  d.push_back( 2 );
  std::vector<int> v( d.size() );
  std::transform( d.begin(), d.end(), v.begin(), std::bind1st( std::plus<int>(), 3 ) );

  index_operations<std::deque<int>, int> dop( d );
  for( int i = 0; i < max; ++i )
  {
    dop.shift_left();
  }

  index_operations<std::string, char> sop( msg );
  sop.shift_left();
  sop.shift_left();
  sop.shift_left();

  index_operations<std::vector<int>, int> vop( v );
  vop.shift_left();

  if ( 'H' == msg[ 0 ] && 7 == v[ 0 ] && 2 == d[ 3 ] && 'W' == sop.at( 9 ) &&
       'd' == sop.at( 2 ) && dop.at( 3 ) == d[ 3 ] && 4 == d.size() &&
       &d[ 0 ] == &d.at( 0 ) && 5 == vop.at( 0 ) && &v[ 1 ] == &vop.at( 2 ) )
  {
    your_mark = dop.at( 3 );
  }
  //*/
  //* 3-as
  dop.shift_right( max - 2 );
  dop.shift_right();

  vop >> 4 ;
  vop.shift_left( 2 );
  ++vop[ 2 ];

  sop << 2;
  sop[ 0 ] = 'w';
  sop[ 5 ] = 'h';

  if ( 'w' == msg[ 6 ] && 'h' == msg[ 0 ] &&
       your_mark == std::count( v.begin(), v.end(), 6 ) )
  {
    your_mark = dop[ 2 ];
  }
  //*/
  //* 4-es
  std::vector<bool> bv;
  bv.push_back( true );
  bv.push_back( true );
  bv.push_back( false );
  index_operations<std::vector<bool> > o( bv );
  o[ 0 ] = false;
  o << 1;
  o.reverse();

  std::string li = "Lorem ipsum dolor sit amet.";
  index_operations<std::string> oli( li );

  oli.reverse();
  oli.reverse();
  oli >> 2;

  if ( 'r' == oli[ 0 ] && oli[ 0 ] && 'm' == oli.at( 2 ) )
  {
    your_mark = std::count( bv.begin(), bv.end(), false ) +
                std::count( li.begin(), li.end(), 'e' );
  }
  //*/
  //* 5-os
  char str[] = { 'C', '+', '+' };
  index_operations<char*> cppo( str, sizeof( str ) / sizeof( str[ 0 ] ) );
  cppo >> 3;

  int array[] = { 7, 1, 4, 5 };
  index_operations<int*> ao( array, sizeof( array ) / sizeof( array[ 0 ] ) );
  ++ao[ 1 ];
  ao >> 2;
  ~ao;

  if ( &array[ 0 ] == &ao[ 1 ] && 2 == ao[ 0 ] && 'C' == cppo[ 0 ] )
  {
    your_mark = ao[ 2 ];
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
