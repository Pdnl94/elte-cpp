#include <algorithm>
#include <list>
#include <iostream>
#include "multistack.h"
#include <numeric>
#include <string>
#include "multistack.h"
#include <stack>
#include <vector>

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  multistack<std::string> p;
  p.push( "Some text" );

  multistack<int> s;
  for( int i = 0; i < max; ++i )
  {
    s.push( i );
  }
  s.join( max / 2 );
  s.join( max / 4 );
  s.push( max );

  multistack<char> hw;
  hw.push( 'H' ).push( 'e' ).push( 'l' ).push( 'l' ).push( 'o' );
  hw.push( 'W' ).push( 'o' ).push( 'r' ).push( 'l' ).push( 'd' );
  hw.join( 3 );

  multistack<int> m;
  m.push( 3 );
  m.push( 6 );
  m.push( 4 );
  m.push( 7 );
  m.push( 2 );
  m.join( 2 );
  m.join( 2 );
  const multistack<int> cm = m;

  if ( 8 == hw.height() &&
       3 == cm.height() &&
       1 == p.height() &&
       9 == p.top()[ 0 ].size() &&
       3 + max / 4 == s.height() &&
       max == s.top()[ 0 ] &&
       3 == hw.top().size() &&
       'r' == hw.top()[ 2 ] )
  {
    your_mark = cm.top()[ 0 ];
  }
  //*/
  //* 3-as
  m.pop();
  m.pop();
  if ( 5 == cm.size() &&
       10 == hw.size() &&
       3 == m.top()[ 0 ] )
  {
    your_mark += m.size();
  }
  //*/
  //* 4-es
  m.replace_top( 4 );
  s.pop();
  s.replace_top( 5 );

  std::stack<double> sta;
  sta.push( 2.3 );
  sta.push( 6.5 );
  sta.push( 1.1 );
  multistack<double> msta( sta );

  if ( 3 == msta.height() &&
       3 == sta.size() &&
       2 > msta.top()[ 0 ] &&
       3 == msta.size() &&
       1 == s.top().size() &&
       4 == m.top()[ 0 ] )
  {
    your_mark = m.top()[ 0 ];
  }
  //*/
  //* 5-os
  std::stack<int, std::list<int> > stb;
  stb.push( 3 );
  stb.push( 5 );
  multistack<int> mstb( stb );

  std::stack<std::string, std::vector<std::string> > stc;
  stc.push( "Foo" );
  stc.push( "bar" );
  multistack<std::string> mstc( stc );

  multistack<char>::const_iterator it = std::find( hw.begin(), hw.end(), 'l' );
  ++it;

  if ( 5 == mstb.top()[ 0 ] &&
       2 == mstb.size() &&
       2 == mstc.size() &&
       'r' == *it )
  {
    your_mark += ( 22 == std::accumulate( cm.begin(), cm.end(), 0 ) );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
