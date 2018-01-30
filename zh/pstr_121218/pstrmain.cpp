#include <iostream>
#include "pstring.h"
#include <algorithm>
#include "pstring.h"

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  basic_palindrom_string<char> s;
  s.push_front_back( 'w' );
  s.push_middle( 'w' );
  const basic_palindrom_string<char> cs = s;

  basic_palindrom_string<char> t;
  t.push_front_back( 'O' );


  basic_palindrom_string<wchar_t> wp;
  for( int i = 0; i < max; ++i )
  {
    wp.push_front_back( L'A' );
    wp.push_middle( L'T' );
  }

  if ( 2 * max + 1 == wp.size() &&
       'w' == cs.at( 1 ) &&
       L'A' == wp.at( max + 1 ) &&
       3 == cs.size() )
  {
    yourMark = t.size();
  }
  //*/
  //* 3-as
  s.middle() = 'o';
  if ( 'w' == cs.middle() &&
       L'T' == wp.middle() &&
       'o' == s.middle() &&
       'w' == cs[ 0 ] )
  {
    yourMark = s.size();
  }
  //*/
  //* 4-es
  s.push_front_back( 'w' );
  basic_palindrom_string<wchar_t>::const_iterator wit =
    std::find( wp.begin(), wp.end(), L'T' );
  basic_palindrom_string<char>::const_iterator cit =
    std::find( cs.begin(), cs.end(), '?' );
  if ( cit == cs.end() && wit != wp.end() )
  {
    yourMark = std::count( s.begin(), s.end(), 'w' );
  }
  //*/
  //* 5-os
  palindrom_string fun;
  fun.push_front_back( ' ' );
  fun.push_front_back( 'n' );
  fun.push_front_back( 'o' );
  fun.push_front_back( ' ' );
  fun.push_front_back( 'e' );
  fun.push_front_back( 'v' );
  fun.push_front_back( 'i' );
  fun.push_front_back( 'l' );
  fun.push_front_back( ' ' );
  fun.push_front_back( 's' );
  fun.push_front_back( 't' );
  fun.push_front_back( 'a' );
  fun.push_front_back( 'r' );

  palindrom_wstring a;
  a.push_front_back( L'A' );
  a.push_front_back( L'B' );
  a.push_middle( L'B' );

  if ( std::cout << fun << " :-)" << std::endl )
  {
    yourMark = a.size();
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
