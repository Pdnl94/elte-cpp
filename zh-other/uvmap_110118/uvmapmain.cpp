#include "uvmap.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include "uvmap.h"

struct StringSizeLess
{
  bool operator()( const std::string& a, const std::string& b ) const
  {
    return a.size() < b.size();
  }
};

struct StringSizeSum
{
  int operator()( int i, const std::pair<std::string, std::string>& p )
  {
    return i + p.first.size() + p.second.size();
  }  
};

class Limited
{
  int v;
public:
  Limited( const int& i ): v ( i ) { }
  int get() const
  {
    return v;
  } 
};

bool operator==( const Limited& l, const Limited& r )
{
  return l.get() == r.get();
}

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  UniqueValuedMap<int, int> imap;
  UniqueValuedMap<int, Limited> lim;
  UniqueValuedMap<std::string, std::string> smap;
  smap.insert( "A", "B" );
  const UniqueValuedMap<std::string, std::string> csmap = smap;

  for( int i = 0; i < max; ++i )  
  {
    imap.insert( i, i );
    lim.insert( i, 0 );
    lim.insert( i + max, 1 );
  }

  if ( !lim.contains( max / 2 ) &&
       !csmap.contains( "B" ) && 
       imap.contains( max / 2 ) )
  {
    yourMark = lim.size();
  }
  //*/
  //* 3-as
  if ( "B" == csmap[ "A" ] &&
       yourMark == imap[ yourMark ] )
  {
    yourMark = lim.size() + csmap.size();
  }
  //*/
  //* 4-es
  smap.insert( "ABC", "B" );
  yourMark = std::accumulate( smap.begin(), smap.end(), 0, StringSizeSum() );
  //*/
  //* 5-os
  UniqueValuedMap<std::string, int, StringSizeLess> a;
  a.insert( "longer", 4 );
  a.insert( "short", 5 );
  if ( 2 == a.size() )
  {
    yourMark = a.begin()->second;
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}

