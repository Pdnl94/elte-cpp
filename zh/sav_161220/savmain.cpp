#include <iostream>
#include "saview.h"
#include <algorithm>
#include <numeric>
#include <list>
#include <deque>
#include <string>
#include "saview.h"

class Comparing
{
  int i;

public:

  Comparing( int s ): i ( s ) { }


  int get() const
  {
    return i;
  }

};

bool operator<( const Comparing& lhs, const Comparing& rhs )
{
  return lhs.get() < rhs.get();
}

struct Comparing_greater: std::binary_function<Comparing, Comparing, bool>
{

  bool operator()( const Comparing& lhs, const Comparing& rhs ) const
  {
    return lhs.get() > rhs.get();
  }

};

struct string_size_less: std::binary_function<std::string, std::string, bool>
{

  bool operator()( const std::string& lhs, const std::string& rhs ) const
  {
    return lhs.size() < rhs.size();
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  int ia[] = { 9, 2, 5, 1, 8 };
  std::string sa[] = { "Merry" , "Christmas" };
  int iam[ max ];
  for( int i = 0; i < max; ++i )
  {
    iam[ i ] = ( i % 2 == 0 ? i : max - i );
  }
  bool sorted = 1 == ia[ 0 ];
  if ( !sorted )
  {
    const sorted_array_view<int> siam( iam, max );
    const sorted_array_view<int> sia( ia, sizeof( ia ) / sizeof( ia[ 0 ] ) );
    const sorted_array_view<std::string> ssa( sa, sizeof( sa ) / sizeof( sa[ 0 ] ) );

    if ( 8 == ia[ 3 ] && 9 == ia[ 4 ] && "Merry" == sa[ 1 ] &&
         5 == sia.size() && max == siam.size() && max - 1 == iam[ max - 1 ] )
    {
      sorted = 1 == ia[ 0 ];
    }
  }
  your_mark += sorted && ( 1 != ia[ 0 ] ) && ( sa[ 0 ] == "Merry" );
  //*/
  //* 3-as
  Comparing ca[] = { 7, 2, 1, 7, 6, 3, 9 };
  sorted = 1 == ca[ 0 ].get();
  if ( !sorted )
  {
    const sorted_array_view<Comparing> sca( ca, sizeof( ca ) / sizeof( ca[ 0 ] ) );
    const sorted_array_view<std::string> ssa( sa, sizeof( sa ) / sizeof( sa[ 0 ] ) );

    if ( 2 == sca.count( 7 ) && 0 == sca.index_of( 1 ) &&
         1 == sca.count( 3 ) && 3 == sca.index_of( 6 ) &&
         0 == ssa.count( "Hello") && 1 == ssa.index_of( "Merry" ) )
    {
      your_mark = ca[ 2 ].get();
    }
  }
  //*/
  //* 4-es
  sorted = 1 == ca[ 0 ].get();
  if ( !sorted )
  {
    const sorted_array_view<Comparing> sca( ca, sizeof( ca ) / sizeof( ca[ 0 ] ) );
    const sorted_array_view<std::string> ssa( sa, sizeof( sa ) / sizeof( sa[ 0 ] ) );
    std::deque<std::string> d;
    d.push_back( ":-o" );
    std::list<Comparing> c;
    sca.copy( c );
    ssa.copy( d );

    if ( sorted_array_view<std::string>::npos == ssa.index_of( "Hello" ) &&
         sorted_array_view<Comparing>::npos == sca.index_of( max ) &&
         2 == d.size() && "Christmas" == d[ 0 ] &&
         1 == c.front().get() && 9 == c.back().get() )
    {
      your_mark = c.size() - ca[ 2 ].get();
    }
  }
  //*/
  //* 5-os
  sorted = 9 == ca [ 0 ].get();
  if ( !sorted )
  {
    const sorted_array_view<Comparing, Comparing_greater> gsca( ca, sizeof( ca ) / sizeof( ca[ 0 ] ) );
    const sorted_array_view<std::string, string_size_less> sl( sa, sizeof( sa ) / sizeof( sa[ 0 ] ) );

    if ( 9 == ca[ 0 ].get() && "MerryChristmas" == std::accumulate( sl.begin(), sl.end(), std::string() ) &&
         1 == gsca.count( 3 ) && 2 == gsca.count( 7 ) )
    {
      your_mark = ca[ 3 ].get() - ca[ 6 ].get();
    }
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
