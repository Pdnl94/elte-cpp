#include <iostream>
#include <deque>
#include "prqueue.h"
#include <string>
#include <queue>
#include <vector>
#include "prqueue.h"

struct string_size_less
{

  bool operator()( const std::string& a,
                   const std::string& b ) const
  {
    return a.size() < b.size();
  }

};

const int max = 1024;

int main()
{
  int your_mark = 1;
  //* 2-es
  priority_queue<int, int> maxy;
  for( int i = 1; i <= max; ++i )
  {
    maxy.push( i, 2 * i );
  }

  priority_queue<int, int> pqii;
  pqii.push( 3, 7 );
  pqii.push( 2, 1 );
  const priority_queue<int, int> cpqii = pqii;

  pqii.push( 4, 4 );
  pqii.update_priority( 3, 7, 5 );

  priority_queue<double, std::string> pqds;
  pqds.push( 2.7, "C" );
  pqds.push( 2.9, "C#" );
  pqds.push( 2.8, "C++" );
  pqds.update_priority( 2.9, "C#", 2.2 );

  if ( "C++" == pqds.top() && 7 == cpqii.top() && 2 * max == maxy.top() )
  {
    your_mark += (7 == pqii.top());
  }
  //*/
  //* 3-as
  pqds.top() += " <3";
  pqds.update_priority( 2.5, "C#", 7.5 );
  pqii.pop();

  if ( "C++ <3" == pqds.top() && 2 == cpqii.size() && 2 == pqii.size() &&
       4 == pqii.top() )
  {
    your_mark = pqds.size();
  }
  //*/
  //* 4-es
  std::priority_queue<int> pqi;
  pqi.push( 4 );
  const priority_queue<int, int> d( pqi );

  std::priority_queue<std::string> str;
  str.push( "C++" );
  str.push( "Ada" );
  str.push( "JavaScript" );
  str.push( "Scala" );

  priority_queue<std::string, std::string> lpqss( str );
  lpqss.pop();

  lpqss.update_priority( "C++", "C++", "Top language" );

  if ( "C++" == lpqss.top() && 3 == lpqss.size() && 1 == d.size() &&
       1 == pqi.size() && 4 == str.size() )
  {
    your_mark = d.top();
  }
  //*/
  //* 5-os
  std::priority_queue<std::string, std::deque<std::string> > t;
  t.push( "Closure" );
  t.push( "Scala" );
  priority_queue<std::string, std::string, string_size_less> pt ( t );

  std::priority_queue<int, std::vector<int>, std::greater<int> > s;
  s.push( 5 );
  s.push( 2 );
  priority_queue<int, int> ps( s );

  if ( 2 == ps.size() && 2 == t.size() &&
       "Closure" == pt.top() && "Scala" == t.top() )
  {
    your_mark = ps.top();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
