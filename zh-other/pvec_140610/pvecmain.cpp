#include <iostream>
#include <list>
#include <functional>
#include "partvec.h"
#include <string>
#include "partvec.h"

struct short_enough: std::unary_function<std::string, bool>
{
  bool operator()( const std::string& a ) const
  {
    return a.length() < 4;
  }
};

struct is_even: std::unary_function<int, bool>
{
  bool operator()( int i ) const
  {
    return 0 == i % 2;
  }
};

const unsigned int max = 1000u;

int main()
{
  int your_mark = 1;
  //* 2-es
  partitioned_vector<unsigned int, is_even> pa;
  for( unsigned int i = 0u; i < max; ++i )
  {
    pa.insert( i );
  }

  partitioned_vector<std::string, short_enough> ps;
  ps.insert( "C" );
  ps.insert( "Cobol" );
  ps.insert( "C++" );
  const partitioned_vector<std::string, short_enough> cps = ps;

  if ( 3u == cps.size() &&
       max / 2 + 1 == pa[ 3 * max / 4 ] &&
       "Cobol" == cps[ 2 ] &&
       8u == pa[ 4 ] &&
       max == pa.size() )
  {
    your_mark = pa[ 1 ];
  }
  //*/
  //* 3-as
  partitioned_vector<std::string, short_enough> pss;
  pss.insert( "Java" );
  pss.insert( "Javascript" );
  pss.insert( "PHP" );

  pss.swap( ps );

  if ( "PHP" == ps.front() &&
       "C" == cps.front() &&
       "Cobol" == cps.back() &&
       "Cobol" == pss.back() )
  {
    your_mark = cps[ 1 ].size();
  }
  //*/
  //* 4-es
  partitioned_vector<unsigned int> v;
  for( unsigned int i = 0u; i < 2 * max; ++i )
  {
    v.insert( i );
  }
  v.swap( pa );

  if ( v.size() == max &&
       pa.size() == 2 * max &&
       8u == v[ 4 ] &&
       3u == pa[ max + 1 ] )
  {
    your_mark = v[ 2 ];
  }
  //*/
  //* 5-os
  partitioned_vector<bool> d;
  d.insert( true );

  std::list<unsigned int> c;
  c.push_back( 3u );
  c.push_back( 8u );
  c.push_back( 19u );
  partitioned_vector<unsigned int, is_even> pl( c.begin(), c.end() );

  if ( d.front() &&
       d[ 0 ] &&
       8u == pl.front() &&
       pl.size() == pl[ 1 ] )
  {
    your_mark += d.back();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
