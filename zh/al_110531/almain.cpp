#include "autolist.h"
#include <iostream>
#include <set>
#include <algorithm>
#include "autolist.h"
#include <vector>

class CntInteger
{
  static int obj;
  int value;
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

int CntInteger::obj = 0;

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  auto_list<int> li;
  li.push_back( new int( 3 ) );
  li.push_front( new int ( 4 ) );
  if ( 4 == li.front() )
  {
    auto_list<CntInteger> lc;
    for( int i = 0; i < max; ++i )
    {
      lc.push_back( new CntInteger( i ) );
    }
  }
  if ( 0 == CntInteger::cnt() )
  {
    yourMark = li.size();
  }
  //*/
  //* 3-as
  const auto_list<int> cl = li;
  --li.front();
  if ( 2 == cl.size() && 3 == cl.back() )
  {
    auto_list<CntInteger> lc;
    lc.push_front( new CntInteger( 0 ) );
    lc.pop_front();
  }
  if ( 4 == cl.front() && 0 == CntInteger::cnt() )
  {
    yourMark = li.front();
  }
  //*/
  //* 4-es
  ++li.back();
  if ( li.back() != cl.back() )
  {
    auto_list<CntInteger> lc;
    lc.push_back( new CntInteger( max ) );
    auto_list<CntInteger> s = lc;
    lc = s;
  }
  if ( 0 == CntInteger::cnt() )
  {
    std::vector<int*> v;
    v.push_back( new int ( max ) );
    v.push_back( new int ( max / 2 ) );
    std::set<double*> s;
    s.insert( new double( 1.3 ) );
    s.insert( new double( 4.3 ) );
    auto_list<int> a;
    a.insert( a.begin(), v.begin(), v.end() );

    auto_list<double> b;
    b.insert( b.begin(), s.begin(), s.end() );
    if ( a.front() == max && a.back() == max / 2 )
    {
      yourMark = a.size() + b.size();
    }
  }
  //*/
  //* 5-os
  auto_list<int>::iterator i = std::find( li.begin(), li.end(), max );
  if ( i == li.end() )
  {
    yourMark += std::count( li.begin(), li.end(), 4 );
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
