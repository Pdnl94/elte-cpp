#include <iostream>
#include "checksum.h"
#include <list>
#include <set>
#include <vector>
#include "checksum.h"
#include <algorithm>
#include <string>
#include <functional>

struct string_size: std::unary_function<std::string, int>
{

  int operator()( const std::string& s ) const
  {
    return s.size();
  }

};

struct identity: std::unary_function<int, int>
{

  int operator()( int i ) const
  {
    return i;
  }

};

struct parity: std::binary_function<int, int, int>
{

  int operator()( int x, int y ) const
  {
    return ( x + y ) % 2;
  }

};

struct mul: std::binary_function<int, int, int>
{

  int operator()( int x, int y ) const
  {
    return x * y;
  }

};


const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  std::set<int> s;
  std::vector<int> v;
  v.reserve( max );
  for( int i = 0; i < max; ++i )
  {
    v.push_back( i );
    s.insert( i % 2 );
  }
  const checksum<std::vector<int>, identity, int> cv( v );
  const checksum<std::set<int>, identity, int> cs( s );

  std::list<std::string> a;
  a.push_back( "Hello" );
  a.push_back( "World" );

  checksum<std::list<std::string>, string_size, std::string> ca( a );

  if ( 10 == ca.get_checksum() && 1 == cs.get_checksum() )
  {
    your_mark = ( max * ( max - 1 ) )/ cv.get_checksum();
  }
  //*/
  //* 3-as
  a.back() += "!";
  std::swap( v[ 0 ], v[ max / 2 ] );

  if ( !ca.validate_checksum() && cs.validate_checksum() )
  {
    your_mark += cv.validate_checksum();
  }
  //*/
  //* 4-es
  std::list<std::string> c;
  c.push_back( "Y U NO write integration tests?" );
  checksum<std::list<std::string>, string_size> cc( c );
  const checksum<std::set<int>, identity> ccs( s );

  ca.update_checksum();
  if ( 11 == ca.get_checksum() && ccs.get_checksum() == cs.get_checksum() &&
       c.front().size() == cc.get_checksum() * 1U)
  {
    your_mark += ca.validate_checksum();
  }
  //*/
  //* 5-os
  checksum<std::vector<int>, identity, int, parity> pv( v );
  checksum<std::list<std::string>, string_size, std::string, mul> ml( a, 1 );

  if ( 0 == pv.get_checksum() )
  {
    your_mark = ml.get_checksum() / a.back().size();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
