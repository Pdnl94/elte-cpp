#include <iostream>
#include <string>
#include "invmmap.h"
#include <algorithm>
#include <functional>
#include "invmmap.h"
#include <cctype>


template<int n>
struct mod: std::unary_function<int, int>
{

  int operator()( int x ) const
  {
    return x % n;
  }

};


struct lowercase: public std::unary_function<std::string, std::string>
{

  std::string operator()( const std::string& s ) const
  {
    std::string ret;
    ret.resize( s.size() );
    std::transform( s.begin(), s.end(), ret.begin(), ::tolower );
    return ret;
  }

};


struct string_size_less: std::binary_function<std::string, std::string, bool>
{

  bool operator()( const std::string& lhs, const std::string& rhs ) const
  {
    return lhs.size() < rhs.size();
  }

};


const int max = 1024;

int main()
{
  int your_mark = 1;
  //* 2-es
  invertable_multimap<int> si;
  for( int i = 0; i < max; ++i )
  {
    si.insert( max, i );
  }
  const invertable_multimap<int> csi = si;
  si.invert( max );

  invertable_multimap<std::string> langs;
  langs.insert( "C++", ":-)" );
  langs.insert( "Ada", ":-/" );
  langs.insert( "PHP", "LOL" );
  langs.insert( "Scala", ":-o" );
  langs.insert( "C++", "Awesome" );
  langs.insert( "C++", "Legendary" );

  langs.invert( "PHP" );

  const invertable_multimap<std::string> clangs = langs;

  if ( 0 == langs.count( "PHP" ) && 1 == si.count( max / 2 ) &&
       max == csi.count( max ) && 1 == si.count( 1 ) &&
       1 == clangs.count( "Ada" ) && clangs.count( "LOL" ) == si.count( 0 ) )
  {
    your_mark = clangs.count( "C++" ) - clangs.count( "Scala" );
  }
  //*/
  //* 3-as
  si.invert();
  si.erase( max );

  langs.invert();
  langs.erase( ":-o" );
  langs.invert();

  if ( 0 == si.count( max ) && 0 == langs.count( "Scala" ) )
  {
    your_mark = langs.count( "C++" );
  }
  //*/
  //* 4-es
  si = csi;
  si.transform_key( mod<2>() );
  si.transform_value( mod<4>() );

  langs.transform_key( lowercase() );
  langs.transform_value( lowercase() );

  if ( 3 == langs.count( "c++" ) && 1 == langs.count( "ada" ) )
  {
    langs.invert();
  }

  if ( 0 == langs.count( "Awesome" ) && 1 == langs.count( "legendary" ) &&
       0 == si.count( max ) && max == si.count( 0 ) )
  {
    langs.invert();
    your_mark = langs.count( "c++" ) + langs.count( "lol" );
  }
  //*/
  //* 5-os
  invertable_multimap<std::string, string_size_less> al;
  al.insert( "C++", "<3" );
  al.insert( "Fortran", ":-S" );
  al.insert( "Fortran", "Formula Translation?" );

  al += langs;

  if ( 2 == al.count( "Haskell" ) && 6 == al.count( "C++" ) )
  {
    al.invert();
    your_mark = al.count( "C++" ) + al.count( "Formula Translation?" );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
