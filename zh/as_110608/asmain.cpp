#include "autoset.h"
#include <algorithm>
#include <iostream>
#include <string>
#include "autoset.h"

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
  auto_set<std::string> is;
  is.insert( new std::string( "Hello" ) );
  is.insert( new std::string( "World" ) );
  is.insert( new std::string( "Hello" ) );
  for( int i = 0; i < max; ++i )
  {
    auto_set<CntInteger> a;
    a.insert( new CntInteger( i ) );
    a.insert( new CntInteger( i ) );
  }
  if ( CntInteger::cnt() == 0 )
  {
    yourMark = is.size();
  }
  //*/
  //* 3-as
  const auto_set<std::string> cis = is;
  is.erase( "Hello" );

  for( int i = 0; i < max; ++i )
  {
    auto_set<CntInteger> a;
    a.insert( new CntInteger( i ) );
    auto_set<CntInteger> b = a;
    a.insert( new CntInteger( i + 1) );
    a.erase( i );
    if ( a.size() == b.size() )
    {
      is.erase( "World" );
      is.insert( new std::string( "A" ) );
    }
  }
  if ( 0 == CntInteger::cnt() )
  {
    yourMark = is.size() + cis.size();
  }
  //*/
  //* 4-es
  if ( 2 == cis.size() )
  {
    auto_set<CntInteger> a;
    for( int i = 0; i < max; ++i )
    {
      a.insert( new CntInteger( i ) );
    }
    a.erase( a.begin(), a.end() );
    if ( 0 == a.size() )
    {
      is.insert( new std::string( "B" ) );
      is.insert( new std::string( "C" ) );
      is.insert( new std::string( "D" ) );
    }
  }
  if ( 0 == CntInteger::cnt() )
  {
    yourMark = is.size();
  }
  //*/
  //* 5-os
  auto_set<int, Greater> p;
  p.insert( new int( 3 ) );
  p.insert( new int( 8 ) );
  p.insert( new int( 7 ) );
  p.insert( new int( 9 ) );
  p.insert( new int( 9 ) );
  p.insert( new int( 1 ) );
  if ( Greater::cnt() > p.size() )
  {
    yourMark = p.size();
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
