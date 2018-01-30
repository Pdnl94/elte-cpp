#include <iostream>
#include "samatrix.h"
#include "samatrix.h"
#include <string>
#include <algorithm>

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  symmetric_associative_matrix<std::string, int> distances;
  distances.add_row_column( "Budapest" );
  distances.add_row_column( "Helsinki" );
  distances.add_row_column( "London" );
  distances.set( "Budapest", "Helsinki", 1462 );
  distances.set( "London",   "Helsinki", 1826 );
  distances.set( "London",   "Budapest", 1455 );
  const symmetric_associative_matrix<std::string, int> cdist = distances;

  symmetric_associative_matrix<int, bool> relation;
  for( int i = 0; i < max; ++i )
  {
    relation.add_row_column( i );
    relation.set( i, i, true );
  }

  if ( max * max == relation.size() &&
       1462 == distances.at( "Helsinki", "Budapest" ) &&
       1826 == cdist.at( "London", "Helsinki" ) )
  {
    your_mark = cdist.size() -
                cdist.at( "Helsinki", "Budapest" ) +
                distances( "London", "Budapest" );
  }
  //*/
  //* 3-as
  distances.add_row_column( "Stockholm" );
  distances.add_row_column( "Espoo" );
  distances( "Stockholm", "Budapest" ) = 1319;
  distances( "Espoo", "Budapest" ) = 1461;
  --distances( "Budapest", "Helsinki" );
  distances.at( "London", "Helsinki" ) = 1828;

  if ( 1462 == cdist( "Budapest", "Helsinki" ) &&
       distances( "Budapest", "Espoo" ) == distances( "Helsinki", "Budapest" ) &&
       1828 == distances( "Helsinki", "London" ) &&
       25 == distances.size() &&
       1319 == distances( "Budapest", "Stockholm" ) )
  {
    your_mark += cdist( "Helsinki", "Budapest" ) - distances( "Budapest", "Helsinki" );
  }
  //*/
  //* 4-es
  relation( 1, 1 ) = false;
  relation( 2, 1 ) = true;
  relation( 2, 2 ) = false;

  distances.erase( "Espoo" );
  distances.erase( "Stockholm" );
  distances.erase( "London" );
  if ( 1461 == distances( "Helsinki", "Budapest" ) &&
       !relation( 1, 1 ) &&
       relation( 2, 1 ) )
  {
    your_mark = distances.size();
  }
  //*/
  //* 5-os
  symmetric_associative_matrix<char, int> x;
  x.add_row_column( 'A' );
  x.add_row_column( 'B' );
  x( 'A', 'B' ) = 2;
  x( 'A', 'A' ) = x( 'B', 'B' ) = 1;

  symmetric_associative_matrix<char, int> y;
  y.add_row_column( 'A' );
  y.add_row_column( 'C' );
  y( 'A', 'A' ) = y( 'C', 'C' ) = 1;
  y( 'C', 'A') = 4;

  const symmetric_associative_matrix<char, int> s = x + y;

  if ( 9 == s.size() &&
       s( 'A', 'B' ) == s( 'A', 'A' ) &&
       0 == s( 'C', 'B' ) )
  {
    your_mark = s( 'C', 'A' ) + s( 'B', 'B' );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
