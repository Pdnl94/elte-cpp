#include "mmmap.h"
#include <iostream>
#include <utility>
#include <string>
#include <algorithm>
#include "mmmap.h"

struct Limited
{

  int val;

public:

  static int cnt;

  Limited( int i = 0 ) : val( i ) { }

  int get() const
  {
    return val;
  }
};

int Limited::cnt = 0;

bool operator<( const Limited& a, const Limited& b )
{
  ++Limited::cnt;
  return a.get() < b.get();
}

struct Pred
{
  bool operator()( const std::pair<int, std::string>& p ) const
  {
    return p.first < 4 && p.second < "W";
  }
};

const int max = 1024;

int main()
{
  int yourMark = 1;
  //* 2-es
  MinMaxMap<std::string, Limited> p;
  MinMaxMap<int, std::string> v;
  for( int i = 0; i < max; ++i )
  {
    v.insert( i, "Hello" );
    v.insert( max + i, "World" );
    p.insert( std::string( i, 'A' ), Limited( 2 * max - i  ) );
  }
  const MinMaxMap<int, std::string> s = v;
  if ( 2 * max == p.max().get() &&
       max + 1 == p.min().get() &&
       "World" == v.max() )
  {
    int tmp = Limited::cnt;
    v.at( max + 3 ).append( "!" );
    v.at( max / 2 ) = "Hali";
    if ( p.size() == max &&
         s.size() == p.max().get() &&
         max + 1 == p.min().get() &&
         max * 2 == p.at( "" ).get() &&
         tmp == Limited::cnt )
    {
      yourMark = v.max().length() - v.min().length();
    }
  }
  //*/
  //* 3-as
  if ( s.at( 3 ) == s.min() &&
       s.at( max + 13 ) == s.max() )
  {
    p[ "C++" ] = Limited( 3 * max );
    p.at( "AAA" ) = Limited( max );
    if ( max + 1 == p.size() )
    {
      yourMark = p.max().get() / p.min().get();
    }
  }
  //*/
  //* 4-es
  yourMark = std::count_if( v.begin(), v.end(), Pred() );
  //*/
  //* 5-os
  int k = 0;
  for( MinMaxMap<int, std::string>::iterator it = v.begin(); it != v.end(); ++it )
  {
    it->second = std::string( k % 6, 'W' );
    ++k;
  }
  int tmp = Limited::cnt;
  if ( p.begin() != p.end() && 
       p.max().get() == 3 * max &&
       "" == v.min() &&
       tmp == Limited::cnt )
  {
    yourMark = v.min().length() + v.max().length();
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
