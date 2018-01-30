#include <iostream>
#include "indapper.h"
#include <vector>
#include <algorithm>
#include <string>
#include "indapper.h"
#include <deque>

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  std::deque<int> da;
  index_appender_view<std::deque<int>, int> idi;
  for( int i = 0; i < max; ++i )
  {
    da.push_back( i );
  }
  std::deque<int> db = da;
  std::deque<int> dc = da;
  idi.add( da );
  idi.add( db );
  idi.add( dc );

  index_appender_view<std::string, char> is;
  std::string h( "Hallo" );
  std::string w( "Worl" );
  is.add( h );
  is.add( w );
  h[ 1 ] = 'e';
  w.push_back( 'd' );

  const index_appender_view<std::string, char> cis = is;

  std::vector<double> v;
  v.push_back( 1.76 );
  v.push_back( 3.31 );
  index_appender_view<std::vector<double>, double> ivd;

  ivd.add( v );

  v[ 0 ] = 5.45;

  if ( 3 * max == idi.size() && ivd.at( 0 ) > v[ 1 ] &&
       0 == idi.at( max ) && 'H' == cis.at( 0 ) &&
       'e' == is.at( 1 ) && 'o' == cis.at( 6 ) &&
       10 == cis.size() && 0 == idi.at( 2 * max ) )
  {
    your_mark = ivd.size();
  }
  //*/
  //* 3-as
  ivd[ 1 ] += 4.58;
  std::swap( idi[ 0 ], idi[ 1 ] );

  if ( 7.2 < ivd[ 1 ] && 'l' == cis[ 2 ] && 0 == idi[ max ] &&
       7.3 < v[ 1 ] && 0 == da[ 1 ] && 1 == da[ 0 ] )
  {
    your_mark += idi[ 0 ];
  }
  //*/
  //* 4-es
  index_appender_view<std::string> s;
  s.add( w );

  std::vector<bool> c;
  c.push_back( true );
  c.push_back( false );
  index_appender_view<std::vector<bool> > ivb;
  ivb.add( c );

  ivb[ 0 ] = false;
  ivb[ 1 ]  = true;

  const index_appender_view<std::vector<bool> > civb = ivb;

  if ( c[ 1 ] && 2 == ivb.size() && 'o' == s[ 1 ] && 5 == s.size() )
  {
    your_mark += civb[ 1 ];
  }
  //*/
  //* 5-os
  std::deque<char> dh( h.begin(), h.end() );
  dh.insert( dh.end(), w.begin(), w.end() );
  index_appender_view<std::deque<char> > idc;
  idc.add( dh );

  if ( cis == idc && !( s == idc ) )
  {
    your_mark = idc.size() - s.size();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
