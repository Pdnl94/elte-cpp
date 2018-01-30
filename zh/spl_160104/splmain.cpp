#include <iostream>
#include <deque>
#include <string>
#include "splicer.h"
#include <list>
#include "splicer.h"
#include <vector>
#include <set>

const int max = 1000;

struct string_size_less
{

  bool operator()( const std::string& a, const std::string& b ) const
  {
    return a.size() < b.size();
  }

};

int main()
{
  int your_mark = 1;
  //* 2-es
  std::list<int> ci;
  for( int i = 0; i < max; ++i )
  {
    ci.push_back( i );
  }
  splicer<int> spi( ci );
  const splicer<int> cspi ( spi );

  std::list<std::string> cs;
  cs.push_back( "Hello" );
  splicer<std::string> sps( cs );
  cs.push_back( "World" );
  sps.append( cs );

  if ( cs.empty() && ci.empty() && 0 == spi.size() &&
       max / 2 == cspi.get( max / 2 ) && max / 3 == cspi.get( max / 3 ) &&
       5 == sps.get( 0 ).size() )
  {
    your_mark = sps.size();
  }
  //*/
  //* 3-as
  for( int i = 0; i < max; ++i )
  {
    ci.push_back( i );
  }
  splicer<int> t ( ci );
  for( int i = 0; i < t.size(); ++i )
  {
    if ( 0 == i % 2 )
    {
      t.get( i ) = max + 1;
    }
  }
  t += ci;
  t -= ( max + 1 );

  cs.push_back( "?" );
  cs.push_back( "!" );
  sps += cs;
  sps -= "?";
  if ( cs.empty() && "!" == sps.get( 2 ) && max / 2 == t.size() &&
       ci.empty() && 3 == t.get( 1 ) )
  {
    your_mark = sps.size();
  }
  //*/
  //* 4-es
  std::deque<double> s;
  s.push_back( 1.47 );

  std::deque<double> d = s;
  std::set<double> sd( s.begin(), s.end() );

  splicer<double> ts( sd );
  ts += d;

  std::multiset<std::string, string_size_less> m;
  m.insert( "Assembly" );
  m.insert( "C++" );
  std::vector<std::string> vs;
  vs.push_back( "Ada" );
  splicer<std::string> ms( m );
  ms += vs;

  if ( d.empty() && 3 == ms.size() && m.empty() && vs.empty() &&
       "C++" == ms.get( 0 ) && "Ada" == ms.get( 2 ) )
  {
    your_mark = ms.get( 1 ).size() / ts.size();
  }
  //*/
  //* 5-os
  std::deque<int> di;
  std::list<int> li;
  for( int i = 0; i < max; ++i )
  {
    di.push_back( i );
    li.push_back( i );
  }
  splicer<int> spt( li );
  spt.splice( di, di.begin() + 2, di.end() - 3 );

  m.insert( "Ada" );
  m.insert( "Java");
  ms.splice( m, m.begin(), m.end() );

  if ( 2 == spt.get( max ) && max < spt.size() &&
       m.empty() && "Ada" == ms.get( 3 ) )
  {
    your_mark = di.size();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
