#include <map>
#include <iostream>
#include "maputil.h"
#include <string>
#include <algorithm>

struct string_size_less
{

  bool operator()( const std::string& lhs,
                   const std::string& rhs ) const
  {
    return lhs.size() < rhs.size();
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  std::map<int, int> t;
  for( int i = 0; i < max; ++i )
  {
    t[ i ] = i + 1;
  }
  std::map<std::string, std::string> s;
  s[ "Hello" ] = "World!";
  s[ "World" ] = "Hello!";
  std::map<std::string, std::string> cs = s;

  map_util<std::string, std::string> su( s );
  map_util<int, int> tu( t );
  const map_util<std::string, std::string> csu( s );
  tu.reverse();
  su.reverse().reverse();
  if ( 1 == tu.count( max ) && cs == s && t[ max - 1 ] == 1 &&
       t[ 2 ] == max - 2 && 1 == csu.count( "World!" ) &&
       0 == csu.count( "C++" ) )
  {
    your_mark = t[ max - 2 ];
  }
  //*/
  //* 3-as
  std::map<int, std::string> mi;
  for( int i = 0; i < max; ++i )
  {
    mi[ i ] = "C++";
  }
  map_util<int, std::string> miu( mi );
  miu.unique().reverse();
  su.unique();

  if ( 1 == mi.size() && mi.begin() == miu.find( "C++" ) &&
       csu.find( "C++" ) == s.end() )
  {
    your_mark = miu.count( "C++" ) + s.size();
  }
  //*/
  //* 4-es
  tu.sort();
  std::map<int, int> x;
  x[ 3 ] = 2;
  x[ 7 ] = 1;
  x[ 4 ] = 8;
  map_util<int, int> ux( x );
  ux.sort();

  std::map<int, std::string> langs;
  langs[ 0 ] = "C++";
  langs[ 1 ] = "C";
  langs[ 2 ] = "Python";
  langs[ 3 ] = "Java";
  map_util<int, std::string> ulangs( langs );
  ulangs.sort( string_size_less() );

  if ( 8 == x[ 7 ] && "C" == langs[ 0 ] && 1 == ulangs.count( "Java" ) &&
       1 + max / 2 == t[ max / 2 ] )
  {
    your_mark = langs[ 3 ].size() - x[ 4 ];
  }
  //*/
  //* 5-os
  std::map<std::string, int, string_size_less> ls;
  ls[ "C++" ] = 8;
  ls[ "Ada 95" ] = 9;
  ls[ "Javascript" ] = 5;

  map_util<std::string, int, string_size_less> uls( ls );
  uls.sort().unique().reverse().reverse();

  if ( 1 == uls.count( 9 ) && 3 == ls.size() && ls.end() == uls.find( 7 ) )
  {
    your_mark = ls[ "C++" ];
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}

