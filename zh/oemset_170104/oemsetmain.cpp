#include <iostream>
#include <functional>
#include <cctype>
#include "oemset.h"
#include <algorithm>
#include <string>
#include <numeric>
#include "oemset.h"
#include <set>
#include <iterator>

struct string_size_less: std::binary_function<std::string, std::string, bool>
{

  bool operator()( const std::string& a, const std::string& b ) const
  {
    return a.size() < b.size();
  }

};


struct first_char_less: std::binary_function<std::string, std::string, bool>
{

  bool operator()( const std::string& a, const std::string& b ) const
  {
    return a[ 0 ] < b[ 0 ];
  }

};

struct case_insensitive_equal: std::binary_function<char, char, bool>
{

  bool operator()( char a, char b ) const
  {
    return std::tolower( a ) == std::tolower( b );
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  optional_equality_multiset<std::string, string_size_less> langs;
  langs.insert( "C++" );
  langs.insert( "Ada" );
  langs.insert( "TeX" );
  langs.insert( "C" );

  const optional_equality_multiset<std::string, string_size_less> cls = langs;
  optional_equality_multiset<std::string, string_size_less> ls = langs;

  ls.use_equality();

  optional_equality_multiset<std::string, first_char_less> ws;
  ws.insert( "Hello" );
  ws.insert( "World" );

  optional_equality_multiset<int, std::greater<int> > mi;
  for( int i = 0 ; i < max; ++i )
  {
    mi.insert( i );
  }

  if( 1 == ws.count( "Hi" ) && 3 == cls.count( "SQL" ) &&
      0 == ws.count( "Szia!" ) && 1 == langs.count( "D" ) &&
      0 == ls.count( "D" ) && 1 == cls.count( "R" ) && 1 == mi.count( 2 ) )
  {
    ws.use_equality();
    your_mark = ws.count( "Ho-ho-ho" ) + ls.count( "C++" ) + mi.count( max / 2 );
  }
  //*/
  //* 3-as
  ws.use_equivalence();
  ls.use_equivalence();
  mi.use_equality();
  langs.use_equality();
  langs.erase( "Ada" );
  ws.erase( "Why?" );
  mi.erase( max - 1 );
  ls.erase( "!!!" );

  if ( 0 == ws.count( "World" ) && 0 == ls.count( "TeX" ) &&
       0 == mi.count( max - 1 ) && 0 == ls.count( "Ada" ) &&
       0 == langs.count( "Ada" ) && 1 == langs.count( "C++" ) )
  {
    your_mark = ls.count( "A" ) + ws.count( "Hi" ) + mi.count( 0 );
  }
  //*/
  //* 4-es
  optional_equality_multiset<std::string, string_size_less>::const_iterator ci =
    langs.find( "TeX" );
  optional_equality_multiset<std::string, first_char_less>::const_iterator wi =
    ws.find( "Haskell" );

  if ( ( ( max - 1 ) * ( max - 2) ) / 2 == std::accumulate( mi.begin(), mi.end(), 0 ) &&
       "TeX" == *ci && "Hello" == *wi && ws.end() == ws.find( "Java" ) &&
       langs.end() == langs.find( "Java" ) )
  {
    langs.use_equivalence();
    your_mark = langs.begin()->size() + langs.count( ":-)" ) + std::distance( ws.begin(), ws.end() );
  }
  //*/
  //* 5-os
  const std::multiset<int> msi = mi;
  std::multiset<std::string, first_char_less> mss = cls;
  optional_equality_multiset<char, std::less<char>, case_insensitive_equal> c;
  c.insert( 'A' );
  c.insert( 'B' );
  c.use_equality();
  if ( 1 == c.count( 'a' ) && max - 1 == msi.size() &&
       1 == msi.count( max / 3 ) && 1 == mss.count( "TeX" ) )
  {
    your_mark = mss.size() + c.count( 'B' );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
