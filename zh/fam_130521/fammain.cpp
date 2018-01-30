#include <iostream>
#include "amatrix.h"
#include <algorithm>
#include "amatrix.h"

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  assoc_matrix<std::string, int> distances;
  distances.add_row_column( "Budapest" );
  distances.add_row_column( "Helsinki" );
  distances.add_row_column( "London" );
  distances.set( "Budapest", "Helsinki", 1461 );
  distances.set( "Helsinki", "Budapest", 1461 );
  distances.set( "Budapest", "London",   1455 );
  distances.set( "London",   "Budapest", 1455 );
  distances.set( "Helsinki", "London",   1826 );

  const assoc_matrix<std::string, int> cdistances = distances;

  assoc_matrix<int, bool> relation;
  for( int i = 1; i <= max; ++i )
  {
    relation.add_row_column( i );
  }
  relation.set( 1, 2, true  );
  relation.set( 2, 1, false );

  if ( 9 == cdistances.size() && 
       1461 == cdistances.at( "Budapest", "Helsinki" ) &&
       0 == cdistances.at( "London", "London" ) )
  {
    your_mark += relation.size() == max * max;
  }
  //*/
  //* 3-as
  distances( "London"  , "Budapest" ) = 1452;
  distances( "Budapest", "London" )   = 1452;
  distances.add_row_column( "Stockholm" );
  distances.at( "Stockholm", "Budapest"  ) = 1319;
  distances.at( "Budapest" , "Stockholm" ) = 1320;
  distances.transpose();

  if ( 1 == distances( "Stockholm", "Budapest" ) - distances( "Budapest", "Stockholm" ) &&
       0x10 == distances.size() )
  {
    your_mark = cdistances( "London", "Budapest" ) - distances( "London", "Budapest" );
  }
  //*/
  //* 4-es
  distances.erase( "Stockholm" );
  for( int i = 3; i <= max; ++i )
  {
    relation.erase( i );
  }
  relation( 2, 1 ) = true;
  relation( 2, 2 ) = true;
  relation( 1, 1 ) = false;
  const assoc_matrix<int, bool> crel = relation;
  if ( relation( 2, 1 ) && crel( 2, 2 ) && 9 == distances.size() )
  {
    your_mark = relation.size();
  }
  //*/
  //* 5-os
  assoc_matrix<int, int> a;
  a.add_row_column( 1 );
  a.add_row_column( 4 );
  a( 1, 1 ) = 5;
  a( 1, 4 ) = 3;
  a( 4, 1 ) = 2;
  a( 4, 4 ) = 1;

  assoc_matrix<int, int> b;
  b.add_row_column( 4 );
  b.add_row_column( 2 );
  b( 2, 2 ) = 1;
  b( 2, 4 ) = 6;
  b( 4, 2 ) = 3;
  b( 4, 4 ) = 7;

  const assoc_matrix<int, int> s = a + b;

  if ( 9 == s.size() &&
       8 == s( 4, 4 ) &&
       6 == s( 2, 4 ) &&
       3 == s( 1, 4 ) )
  {
    your_mark = s( 1, 1 );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
