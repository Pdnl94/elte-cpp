#include <iostream>
#include "partdeq.h"
#include <functional>
#include <string>
#include "partdeq.h"

struct is_odd: std::unary_function<unsigned int, bool>
{

  bool operator()( unsigned int i ) const
  {
    return 1 == i % 2;
  }

};

struct string_pred: std::unary_function<std::string, bool>
{

  bool operator()( const std::string& s ) const
  {
    return !is_odd()( s.length() );
  }

};

const unsigned int max = 1000u;

struct less_than_max: std::unary_function<unsigned int, bool>
{

  bool operator()( unsigned int i ) const
  {
    return i < max;
  }

};

int main()
{
  int your_mark = 1;
  //* 2-es
  partitioned_deque<unsigned int, is_odd> a;
  for( unsigned int i = 0; i < max; ++i )
  {
    a.push_front( i );
  }

  partitioned_deque<unsigned int, is_odd> d;
  d.push_back( 1u );
  d.push_front( 2u );
  const partitioned_deque<unsigned int, is_odd> cd = d;
  d.push_back( 4u );

  partitioned_deque<std::string, string_pred> s;
  s.push_back( "C" );
  s.push_front( "C++" );
  s.push_back( "Java" );

  if ( 2u == cd.size() &&
       3u == s.size() &&
       max == a.size() &&
       "C" == s[ 2 ] &&
       max - 1 == a[ 0 ] )
  {
    your_mark = d[ 1 ];
  }
  //*/
  //* 3-as
  partitioned_deque<unsigned int, is_odd> o;
  o.push_back( max );

  partitioned_deque<std::string, string_pred> p;
  p.push_back( "text" );

  if ( p.front() == p.back() &&
       o.front() == o.back() &&
       2u == cd.back() &&
       max == o.front() )
  {
    your_mark += d.front();
  }
  //*/
  //* 4-es
  partitioned_deque<unsigned int, less_than_max> r;
  r.push_back( 1u );
  r.push_back( 2u );

  partitioned_deque<unsigned int, less_than_max> q;
  q.push_back( max );

  p.push_back( "Some text" );
  p.push_back( "More text" );

  if ( !( cd != r ) &&
       !( p == s ) )
  {
    your_mark += ( q == o );
  }
  //*/
  //* 5-os
  partitioned_deque<bool> v;
  v.push_front( true );

  for( unsigned int i = 0; i < 2 * max; ++i )
  {
    q.push_back( i );
  }

  partitioned_deque<unsigned int, is_odd> cq = q;

  if ( v.back() && v[ 0 ] &&
       q.size() == cq.size() &&
       0 == cq[ max ] )
  {
    your_mark = cq[ 2 ];
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
