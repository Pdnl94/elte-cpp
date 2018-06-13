#include "automap.h"
#include <iostream>
#include <algorithm>

struct CntInteger
{
  int value;
  static int obj;
public:
  CntInteger( int v ): value( v )
  {
    ++obj;
  }

  CntInteger( const CntInteger& rhs ): value( rhs.value )
  {
    ++obj;
  }

  ~CntInteger()
  {
    --obj;
  }

  int val() const
  {
    return value;
  }

  static int cnt()
  {
    return obj;
  }
};

bool operator<( const CntInteger& a, const CntInteger& b )
{
  return a.val() < b.val();
}

bool operator==( const CntInteger& a, const CntInteger& b )
{
  return !( a < b ) && !( b < a );
}

bool operator!=( const CntInteger& a, const CntInteger& b )
{
  return !( a == b );
}

int CntInteger::obj = 0;

class Greater
{
  static int called;
public:
  bool operator()( const int& a, const int& b )
  {
    ++called;
    return a > b;
  }

  static int cnt()
  {
    return called;
  }
};

int Greater::called = 0;

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  auto_map<std::string, std::string> t;
  t.insert( new std::string( "A" ), new std::string( "B" ) );
  t.insert( new std::string( "B" ), new std::string( "C" ) );

  for( int i = 0; i < max; ++i )
  {
    auto_map<CntInteger, CntInteger> a;
    a.insert( new CntInteger( 1 ), new CntInteger( 1 ) );
    a.insert( new CntInteger( 3 ), new CntInteger( 6 ) );
    a.insert( new CntInteger( 3 ), new CntInteger( 2 ) );
  }
  if ( 0 == CntInteger::cnt() )
  {
    yourMark = t.size();
  }
  //*/
  //* 3-as
  auto_map<int, int> m;
  m.insert( new int( max ), new int( 2 ) );
  for( int i = 0; i < max; ++i )
  {
    auto_map<CntInteger, CntInteger> x;
    x.insert( new CntInteger( i ), new CntInteger( i ) );
    auto_map<CntInteger, CntInteger> cx = x;
  }
  if ( 2 == m.at( max ) )
  {
    const auto_map<int, int> cm = m;
    ++m.at( max );
    if ( 2 == cm.at( max ) && 0 == CntInteger::cnt() )
    {
      yourMark = m.at( max );
    }
  }
  //*/
  //* 4-es
  auto_map<int, int> map;
  for( int i = 0; i < max; ++i )
  {
    auto_map<CntInteger, CntInteger> c;
    c.insert( new CntInteger( i ), new CntInteger( max ) );
    c.insert( new CntInteger( max + i ), new CntInteger( max ) );
    auto_map<CntInteger, CntInteger>::iterator it = c.begin();
    ++it;
    c.erase( c.begin(), it );
    map.insert( new int( i % 5 ), new int( i ) );
  }
  if ( 0 == CntInteger::cnt() )
  {
    map.erase( map.begin(), ++map.begin() );
    yourMark = map.size();
  }
  //*/
  //* 5-os
  auto_map<int, int, Greater> mg;
  mg.insert( new int( 4 ), new int( 4 ) );
  mg.insert( new int( 2 ), new int( 5 ) );
  mg.insert( new int( 7 ), new int( 3 ) );
  mg.insert( new int( 4 ), new int( 7 ) );
  
  if ( Greater::cnt() > mg.size() )
  {
    yourMark = mg.at( 2 );
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
