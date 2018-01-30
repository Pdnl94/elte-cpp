#include <iostream>
#include "arfiltview.h"
#include <algorithm>
#include <numeric>
#include <string>
#include <functional>
#include "arfiltview.h"

struct is_good_language : std::unary_function<std::string, bool>
{

  bool operator()( const std::string& s ) const
  {
    return s == "C++";
  }

};

struct prefix : std::unary_function<std::string, bool>
{

  bool operator()( const std::string& s ) const
  {
    return 'A' == s[ 0 ] || 'J' == s[ 0 ];
  }

};

struct is_even : std::unary_function<int, bool>
{

  bool operator()( int i ) const
  {
    return 0 == i % 2;
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  int v[ max ];
  for( int i = 0; i < max; ++i )
  {
    v[ i ] = i;
  }

  std::string langs[] = { "Java", "Javascript", "C++", "Cobol", "Ada" };
  bool ok = false;
  {
    const array_filter_view<std::string, is_good_language> sv(
      langs, sizeof( langs ) / sizeof( langs[ 0 ] ) );

    const array_filter_view<int, is_even> iv( v, max );

    if ( 1 == sv.size() && "C++" == langs[ 0 ] && max / 2 == iv.size() &&
         max / 2 == v[ max / 4 ] )
    {
      ok = true;
    }
  }
  if ( ok && "Java" == langs[ 0 ] && "C++" == langs[ 2 ] &&
      max / 3 == v[ max / 3 ] )
  {
    your_mark = langs[ 3 ].length() - langs[ 4 ].length();
  }
  //*/
  //* 3-as
  ok = false;
  {
    const array_filter_view<std::string, prefix> sv(
      langs, sizeof( langs ) / sizeof( langs[ 0 ] ) );

    const array_filter_view<int, is_even> iv( v, max );

    if ( array_filter_view<int, is_even>::npos == iv.index_of( max / 3 ) &&
         array_filter_view<std::string, prefix>::npos == sv.index_of( "C" ) &&
         3 == sv.size() && 2 == sv.index_of( "Ada" ) && 1 == iv.index_of( 2 ) )
    {
      ok = true;
    }
  }
  if ( v[ max - 1 ] == max - 1 && "Ada" == langs[ 4 ] )
  {
    your_mark += ok;
  }
  //*/
  //* 4-es
  {
    const array_filter_view<int, is_even> iv( v, max );

    const array_filter_view<std::string, prefix> sv(
      langs, sizeof( langs ) / sizeof( langs[ 0 ] ) );

    if ( 0 == iv.index_if( is_even() ) &&
         array_filter_view<int, is_even>::npos == iv.index_if( std::not1( is_even() ) ) &&
         array_filter_view<std::string, prefix>::npos == sv.index_if( is_good_language() ) )
    {
      your_mark = langs[ 0 ].length();
    }
  }
  //*/
  //* 5-os
  {
    const array_filter_view<std::string, prefix> sv(
      langs, sizeof( langs ) / sizeof( langs[ 0 ] ) );

    array_filter_view<std::string, prefix>::const_iterator it =
      std::find( sv.begin(), sv.end(), "Cobol" );

    array_filter_view<int, is_even> iv( v, max );

    if ( it == sv.end() && 1 == std::count( iv.begin(), iv.end(), max / 5 ) &&
         17 == std::accumulate( sv.begin(), sv.end(), std::string() ).length() )
    {
      your_mark += std::count( sv.begin(), sv.end(), "Ada" );
    }
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
