#include <iostream>
#include "repcharstr.h"
#include <algorithm>
#include "repcharstr.h"

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  basic_repeating_string<char> s;
  s.push_back( 'H' );
  s.push_back( 'i' );
  s.print( std::cout );
  std::endl( std::cout );

  basic_repeating_string<wchar_t> w;
  w.push_back( L'C' );
  w.push_back( L'+' );
  w.set_repeating( 2 );
  w.print( std::wcout );
  std::endl( std::wcout );

  basic_repeating_string<char> t;
  for( int i = 0; i < max; ++i )
  {
    t.push_back( 0 == i % 2 ? 'X' : 'Y' );
  }
  t.set_repeating( 3 );

  const basic_repeating_string<wchar_t> cw = w;
  w.push_back( L'+' );

  if ( 2 == cw.rfind( L"++" ) &&
       2 == s.size() &&
       -1 == cw.rfind( L"+C" ) &&
       3 * max - 4 == t.rfind( "XYY" ) &&
       3 * max == t.size() )
  {
    yourMark = w.size() - cw.size();
  }
  //*/
  //* 3-as
  s.set_repeating( 4 );
  s[ 6 ] = 'o';
  t[ 0 ] = 'T';

  if ( 1 == t.rfind( "TT" ) &&
       L'C' == cw[ 0 ] &&
       0 == w.compare( L"CC++++" ) &&
       0 < cw.compare( L"BLABLA" ) &&
       0 > s.compare( "HI" ) )
  {
    yourMark = s.rfind( "Hoo" );
  }
  //*/
  //* 4-es
  std::fill( s.begin(), s.end(), 'a' );
  basic_repeating_string<wchar_t>::iterator i =
    std::find( w.begin(), w.end(), L'+' );
  if ( i != w.end() && 'a' == s[ 2 ] )
  {
    yourMark = s.rfind( "aaaa" );
  }
  //*/
  //* 5-os
  basic_repeating_string<char> a;
  a.push_back( 'A' );
  a.push_back( 'T' );
  a.set_repeating( 3 );
  *(a.begin() ) = 'B';
  a[ 5 ] = 'O';
  yourMark = std::count( s.begin(), s.end(), 'a' ) -
             std::count( a.begin(), a.end(), 'A' ) -
             std::count( a.begin(), a.end(), 'T' ) -
             std::count( a.begin(), a.end(), 'O' );
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
