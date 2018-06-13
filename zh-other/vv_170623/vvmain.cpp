#include <iostream>
#include <vector>
#include "viview.h"
#include <algorithm>
#include <string>
#include <numeric>
#include "viview.h"

const int max = 1024;

int main()
{
  int your_mark = 1;
  //* 2-es
  std::vector<int> vi;
  for( int i = 0; i < max; ++i )
  {
    vi.push_back( 0 == i % 2 ? i / 2 : max - i );
  }
  vector_index_view<int> viv( vi );
  viv.swap( 0, max - 1 );
  viv.swap( 1, max / 2 );

  std::vector<std::string> vs;
  vs.push_back( "World" );
  vs.push_back( ":-)" );
  vs.push_back( "Hello" );
  vector_index_view<std::string> vsv( vs );
  vsv.swap( 0, 2 );
  vsv.swap( 1, 2 );

  std::vector<int> v;
  v.push_back( 5 );
  v.push_back( 1 );
  v.push_back( 2 );
  vector_index_view<int> vv ( v );
  vv.swap( 0, 1 );

  if( &vi[ 0 ] == &viv.at( max - 1 ) && &v[ 2 ] == &vv.at( 2 ) &&
      5 == v[ 0 ] && 1 == vv.at( 0 ) && 3 == vsv.at( 2 ).size() &&
      vs[ 0 ] != vsv.at( 0 ) && ":-)" == vs[ 1 ] && 3 == v.size() )
  {
    your_mark = vv.at( 2 );
  }
  //*/
  //* 3-as
  vv[ 1 ] = 8;
  if ( vector_index_view<int>::npos == vv.index_of( 5 ) &&
       vector_index_view<int>::npos == viv.index_of( max ) &&
       2 == vsv.index_of( ":-)" ) && 2 == vv.index_of( 2 ) )
  {
    your_mark += vv.index_of( 8 );
  }
  //*/
  //* 4-es
  -vv;
  -vv;
  -vsv;
  vsv.swap( 1, 2 );
  +vsv;
  +viv;
  +viv;

  if ( 2 == vv[ 0 ] && 1 == vv[ 2 ] && "Hello" == vsv[ 1 ] &&
       0 == viv[ max - 1 ] )
  {
    your_mark = vv.index_of( 1 ) + vsv.index_of( ":-)" );
  }
  //*/
  //* 5-os
  vector_index_view<std::string>::iterator it =
    std::find( vsv.begin(), vsv.end(), "Hello" );
  ++it;
  vector_index_view<std::string>::iterator nf =
    std::find( vsv.begin(), vsv.end(), ":-D" );

  vector_index_view<int>::iterator in =
    std::find( vv.begin(), vv.end(), 2 );
  ++in;


  if ( ":-)" == *it && nf == vsv.end() && 8 == *in &&
       std::accumulate( vi.begin(), vi.end(), 0 ) ==
       std::accumulate( viv.begin(), viv.end(), 0 ) )
  {
    your_mark = vsv.begin()->size();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
