#include <iostream>
#include <algorithm>
#include <numeric>
#include "dqview.h"
#include <deque>
#include <algorithm>

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
  std::deque<int> d;
  d.push_back( 7 );
  d.push_back( 2 );
  d.push_back( 3 );
  std::deque<int> a;
  a.push_back( 1 );
  a.push_back( 5 );
  std::deque<int> b;
  for( int i = 0; i < max; ++i )
  {
    b.push_back( i );
  }

  std::deque<std::string> s;
  s.push_back( "Hello" );
  s.push_back( "World" );
  const deques_view<std::string> vs( s );

  deques_view<int> di( d );
  di.add( a );
  di.add( b );

  if ( 5 == di.at( 4 ) && &( d[ 0 ] ) == &(di.at( 0 ) ) &&
       s[ 1 ] == vs.at( 1 ) && max - 5 == di.at( max ) &&
       &( a[ 0 ] ) ==  &( di.at( 3 ) ) )
  {
    your_mark = di.at( 1 );
  }
  //*/
  //* 3-as
  di[ 0 ] -= di[ 2 ];
  ++di[ 5 ];
  if ( "Hello" == vs[ 0 ] && your_mark == vs.size() &&
       max + 5 == di.size() && 4 == d[ 0 ] && 1 == b[ 0 ])
  {
    your_mark =  di[ 2 ];
  }
  //*/
  //* 4-es
  std::deque<std::string> langs;
  langs.push_back( "Cobol" );
  langs.push_back( "Go" );
  langs.push_back( "C++" );
  langs.push_back( "Fortran" );
  deques_view<std::string> lv( langs );
  lv.sort( string_size_less() );

  di.sort();

  if ( d[ 0 ] == d[ 1 ] && 1 == di[ 2 ] && "Go" == langs[ 0 ] 
       && "C++" == langs[ 1 ] && 2 == a[ 0 ] )
  {
    your_mark = lv.size();
  }
  //*/
  //* 5-os
  deques_view<int>::iterator it = std::find( di.begin(), di.end(), max - 1 );

  if ( it != di.end() && max - 1 == *it &&
       17 == std::accumulate( lv.begin(), lv.end(), std::string() ).size() )
  {
    your_mark += std::binary_search( di.begin(), di.end(), max / 2 );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
