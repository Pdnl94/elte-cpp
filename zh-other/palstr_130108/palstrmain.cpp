#include <iostream>
#include "pstring.h"
#include <algorithm>
#include "pstring.h"

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  basic_palindrom_string<char> a;
  a.push_front_back( 'w' );
  a.push_middle( 'o' );

  const basic_palindrom_string<char> ca = a;

  basic_palindrom_string<wchar_t> w;
  for( int i = 0; i < max; ++i )
  {
    w.push_front_back( i % 2 == 0 ? L'a' : L'b' );
  }

  if ( w.find( L"babab" ) == 0 && w.find( L"wow" ) == -1 )
  {
    yourMark = ca.size() - ca.find( "ow" );
  }
  //*/
  //* 3-as
  a[2] = 'L';
  a[1] = 'O';
  if ( 'L' == a[0] && 'w' == ca[0] &&
       0 == a.compare( "LOL" ) &&
       0 < ca.compare( "w" ) &&
       0 > w.compare( L"bbbb" ) )
  {
    yourMark = a.size();
  }
  //*/
  //* 4-es
  basic_palindrom_string<char>::const_iterator i =
    std::find( ca.begin(), ca.end(), 'o' );
  basic_palindrom_string<char>::const_iterator j =
    std::find( ca.begin(), ca.end(), 'x' );

  if ( i != ca.end() && j == ca.end() )
  {
    yourMark += i - ca.begin();
  }
  //*/
  //* 5-os
  basic_palindrom_string<char> s;
  s.push_front_back( 'w' );
  s.push_middle( 'w' );

  yourMark = std::count( s.begin(),  s.end(),   'w' ) +
             std::count( ca.begin(), ca.end(),  'w' ) +
             std::count( w.begin(),  w.end(),  L'm' );
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
