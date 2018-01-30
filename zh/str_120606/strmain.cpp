#include <iostream>
#include "bsstring.h"
#include <algorithm>
#include <functional>
#include <list>
#include <string>
#include "bsstring.h"

const int max = 1024;

int main()
{
  int yourMark = 1;
  //* 2-es
  basic_safe_string<char> str;
  basic_safe_string<char> s;
  basic_safe_string<wchar_t> wstr;

  for( int i = 0; i < max; ++i )
  {
    str.push_back( 'a' );
    s.push_back( 'T' );
    if ( i > 1 )
    {
      s.erase( str.length() - 1, 1 );
    }
    str.erase( str.length() - 1, 1 );
  }
  str.at( max, ' ' ) = '!';
  wstr.at( max / 2, L'_' ) = L'?';
  const basic_safe_string<char> cs = str;
  if ( sizeof( str.at( 0, ' ' ) ) != sizeof( wstr.at( 0, L' ' ) ) &&
       max + 1 == cs.length() &&
       ' ' == str.at( 1, '?' ) &&
       L'?' == wstr.at( max / 2, L'+' ) )
  {
    yourMark = s.length();
  }
  //*/
  //* 3-as
  basic_safe_string<wchar_t> wsub = wstr.substr( 1, 3 );
  wsub[ 1 ] = L'A';
  basic_safe_string<char> sub = str.substr( 1, 4 );
  sub.erase( 1, 1 ).erase( 1, 1 ).erase( 1, 1 );
  sub[ 4 ] = 'E';
  if ( wsub.at( 1, L'O' ) == L'A' &&
      5 == sub.length() &&
      char() == sub[ 3 ] )
  {
    yourMark = wsub.length();
  }
  //*/
  //* 4-es
  basic_safe_string<char>::iterator i = 
    std::find( sub.begin(), sub.end(), 'A' );
  if ( i == sub.end() )
  {
    yourMark = std::count_if( 
      sub.begin(), 
      sub.end(), 
      std::not1( std::bind2nd( std::equal_to<char>(), 'E' ) ) );
  }
  //*/
  //* 5-os
  safe_string h( "Hello" );
  safe_wstring w( L"World" );
  std::string r( "andy" );
  h.replace( h.begin() + 1, h.end(), r.begin(), r.end() );
  std::list<wchar_t> li;
  li.push_back( L'I' );
  w.replace( w.begin() + 1, w.begin() + 2, li.begin(), li.end() );
  if ( 'y' == h[ 4 ] && L'I' == w[ 1 ] && 5 == w.length() )
  {
    yourMark = h.length();
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
