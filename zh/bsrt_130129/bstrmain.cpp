#include <algorithm>
#include <vector>
#include "bstring.h"
#include <deque>
#include <list>
#include "bstring.h"
#include <iostream>

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  const basic_string_adapter<std::deque<wchar_t>, wchar_t> x( L"aaaab" );

  basic_string_adapter<std::vector<wchar_t>, wchar_t> ws( L"Hello" );
  ws.push_back( L'W' ).push_back( L'o' ).push_back( L'r' ).push_back( L'l' ).push_back( L'd' );

  basic_string_adapter<std::deque<char>, char> str;
  str.push_back( 'C' ).push_back( '+' ).push_back( '+' );
  const basic_string_adapter<std::deque<char>, char> cstr = str;

  basic_string_adapter<std::vector<char>, char> vs;
  for( int i = 0; i < max; ++i )
  {
    vs.push_back( 'x' ).push_back( 'y' ).push_back( 'z' );
  }

  if ( 10 == ws.size() &&
       1 == x.find( L"aaab" ) &&
       sizeof( str ) != sizeof( vs ) &&
       3 * max == vs.size() &&
       1 == vs.find( "yzxy" ) &&
       6 == ws.find( L"or" ) &&
       1 == str.find( "+" ) &&
      -1 == ws.find( L"lll" ) )
  {
    yourMark = cstr.size() + cstr.find( "Java" );
  }
  //*/
  //* 3-as
  const basic_string_adapter<std::list<wchar_t>, wchar_t> t( L"Some text" );
  str += "++";
  ws += L"!";
  str[ 1 ] = str[ 2 ] = '-';
  if ( '+' == cstr[ 1 ] &&
       9 == t.size() &&
       L'e' == t[ 3 ] &&
       '-' == str[ 2 ] &&
       5 == str.size() &&
       L'!' == ws[ 10 ] &&
       11 == ws.size() )
  {
    yourMark = str.size() - str.find( "-+" );
  }
  //*/
  //* 4-es
  const basic_string_adapter<std::deque<char> > msg( "Hello" );
  if ( L"Some text" == t && "C++" == cstr && !( ws == t ) && 'e' == msg[ 1 ] )
  {
    yourMark = t.size() - t.find( L"text" );
  }
  //*/
  //* 5-os
  const basic_string_adapter<std::list<char> > cm = msg;
  const basic_string_adapter<std::list<wchar_t> > cws = ws;

  if ( cm == msg && cws == ws && cws[ 0 ] == cm[ 0 ] )
  {
    yourMark = cm.size();
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
