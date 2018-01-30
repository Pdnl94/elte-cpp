#include <iostream>
#include "invablemap.h"
#include <string>
#include <map>
#include "invablemap.h"

struct string_size_less
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
  invertable_map<double, double> m;
  m.insert( 1.4, 2.3 );
  invertable_map<int, int> a;
  a.insert( 1, 2 );
  invertable_map<int, std::string> t;
  for( int i = 1; i <= max; ++i )
  {
    t.insert( i, std::string( i, 'a' ) );
  }
  const invertable_map<int, std::string> ct = t;
  const invertable_map<std::string, int> it = t.inverse();
  if ( ct.size() == max && 1 == ct.count( max / 2 ) &&
       0 == ct.count( max + 1 ) && max == it.inverse().size() &&
       1 == it.count( "aaa" ) && 1 == m.size() &&
       a.size() == a.inverse().count( 2 ) )
  {
    your_mark = it.count( "b" ) + it.count( "a" ) + it.count( "aaaa" );
  }
  //*/
  //* 3-as
  ++a[ 1 ];
  t[ 4 ] = ":-)";
  if ( ct[ 4 ] != t[ 4 ] && 1 == a.size() && 3 == t[ 4 ].size() &&
       1 == it[ "a" ] && 0 == a.inverse().count( 2 ) )
  {
    your_mark = a[ 1 ];
  }
  //*/
  //* 4-es
  invertable_map<std::string, int, string_size_less> s;
  invertable_map<std::string, std::string, string_size_less> b;
  s.insert( "C++", 4 );
  b.insert( "Java", "Ada" );
  const invertable_map<int, std::string> iit = -it;

  if ( 0 != s.count( "Ada" ) && 1 == (-b).count( "Ada" ) &&
       0 == (-b).count( "C++" ) && "aa" == iit[ 2 ] )
  {
    your_mark = s[ ":-)" ];
  }
  //*/
  //* 5-os
  invertable_map<std::string, std::string, string_size_less, string_size_less> r;
  r.insert( ":-)", ":-D" );
  invertable_map<std::string, std::string, string_size_less, string_size_less> ir = -r;
  const std::map<std::string, int, string_size_less> ms = s;
  const std::map<double, double> mm = m;
  std::map<int, std::string> mt = t;
  if ( 1 == mm.size() && max * 1U == mt.size() && 1 == ir.count( ";-)" ) &&
       1 == mt.count( max / 3 ) && 1 == ms.count( "PHP" ) )
  {
    your_mark = ms.size() + ms.begin()->second;
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}


