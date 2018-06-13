#include "contmap.h"
#include <iostream>
#include <utility>
#include <map>
#include <functional>
#include <string>
#include <vector>
#include "contmap.h"

struct StringSizeLess: std::binary_function<std::string, std::string, bool>
{
  static int cnt;

  bool operator()( const std::string& a,
                   const std::string& b ) const
  {
    ++cnt;
    return a.size() < b.size();
  }
};

int StringSizeLess::cnt = 0;

const int max = 1000;
const int control = 3;

int main()
{
  int yourMark = 1;
  //* 2-es
  ControlledMap<std::string, int> index( control );
  index.insert( "C++", 2 );
  index.insert( "Java", 4 );
  index.insert( "Ada", 5 );

  ControlledMap<int, std::string> t( control );
  for( int i = max; i >= 0; --i )
  {
    t.insert( i, "TESTING" );
  }

  const ControlledMap<int, std::string> c = t;
  if ( index.contains_key( "C++" ) && !t.contains_key( max / 2 ) &&
       t.contains_key( 1 ) && c.size() == 3 )
  {
    yourMark = t.size();
  }
  //*/
  //* 3-as
  index.erase( "Ada" );
  ++index[ "C++" ];
  for( int i = 0; i < max; ++i )
  {
    t[ 0 ] = "Testing";
  }
  if ( !index.contains_key( "Ada" ) && 1 == t.size() )
  {
    yourMark = index[ "C++" ];
  }
  //*/
  //* 4-es
  ControlledMap<std::string, int, StringSizeLess> s( control );
  s.insert( "C++", 4 );
  s.insert( "Java", 5 );
  if ( StringSizeLess::cnt > 0 )
  {
    yourMark = s[ "C++" ];
  }
  //*/
  //* 5-os
  std::map<std::string, int> m;
  m[ "C++" ] = 5;
  m[ "Java" ] = 5;

  std::vector<std::pair<int, int> > v;
  for( int i = 0; i < max; ++i )
  {
    v.push_back( std::make_pair( i, i ) );
  }

  ControlledMap<int, int> ids( control, v.begin(), v.end() );
  ControlledMap<std::string, int> cm( control, m.begin(), m.end() );
  if ( ids.size() == max &&
       ids.contains_key( max / 2 ) &&
       cm.contains_key( "Java" ) )
  {
    yourMark = cm[ "C++" ];
  }
  //*/
  std::cout << "Your mark is "
            << yourMark;
  std::endl( std::cout );
}
