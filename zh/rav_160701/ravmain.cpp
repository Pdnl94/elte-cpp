#include <iostream>
#include "revarrview.h"
#include <string>
#include <vector>
#include <algorithm>
#include "revarrview.h"

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  int a[] = { 7, 2, 1, 8 };
  reverse_array_view<int> rai( a, sizeof( a ) / sizeof( a[ 0 ] ) );
  int b[] = { 9, 2 };
  rai.add( b, sizeof( b ) / sizeof( b[ 0 ] ) );
  int c[] = { 6, 4 , 4 };
  rai.add( c, sizeof( c ) / sizeof( c[ 0 ] ) );

  std::string s[] = { "Hello", "World" };
  reverse_array_view<std::string> ras( s, sizeof( s ) / sizeof( s[ 0 ] ) );
  for( int i = 1 ; i < max; ++i )
  {
    ras.add( s, sizeof( s ) / sizeof( s[ 0 ] ) );
  }

  const reverse_array_view<int> cr( b, sizeof( b ) / sizeof( b[ 0 ] ) );

  if ( 9 == rai.size() && 2 * max == ras.size() &&
       "World" == ras.at( 0 ) && 2 == rai.at( 3 ) &&
       9 == cr.at( 1 ) && a == &( rai.at( 8 ) ) &&
       s + 1 == &( ras.at( max / 2 ) ) )
  {
    your_mark = cr.size();
  }
  //*/
  //* 3-as
  ++rai[ 7 ];
  ras[ 2 ] += "!";

  if ( 6 == s[ 1 ].size() && 2 == cr[ 0 ] )
  {
    your_mark = rai[ 7 ];
  }
  //*/
  //* 4-es
  int t[] = { 2 };
  rai.add( t );
  int tt[] = { 3, 2 };
  rai.add( tt );
  int ttt[] = { 1, 8, 9 };
  rai.add( ttt );
  int tttt[] = { 1, 2, 3, 4, 5 };
  rai.add( tttt );
  ++rai[ 10 ];

  if ( 3 == t[ 0 ] && 20 == rai.size() && 5 == rai[ 0 ] && 9 == rai[ 5 ] )
  {
    your_mark = rai[ 1 ];
  }
  //*/
  //* 5-os
  std::vector<int> vi;
  vi.push_back( 1 );
  vi.push_back( 2 );
  rai.add( vi );
  std::vector<int> ve;
  ve.push_back( 1 );
  rai.add( ve );
  ++rai[ 0 ];

  std::vector<std::string> vs;
  vs.push_back( ":-)" );
  ras.add( vs );

  if ( 2 == ve[ 0 ] && 23 == rai.size() && 1 == rai[ 2 ] && ":-)" == ras[ 0 ] )
  {
    your_mark = rai[ 0 ] + rai[ 1 ] + rai[ 2 ];
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
