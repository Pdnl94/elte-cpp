#include <iostream>
#include <map>
#include "invmmap.h"
#include <string>
#include <algorithm>
#include "invmmap.h"

struct string_size_less
{

  bool operator()( const std::string& a, const std::string& b ) const
  {
    return a.size() < b.size();
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  std::multimap<double, double> n;
  invertable_multimap<double, double> in( n );

  std::multimap<int, std::string> a;
  a.insert( std::make_pair( 1, "Hello" ) );

  invertable_multimap<int, std::string> t( a );
  for( int i = 0; i < max; ++i )
  {
    t.insert( 3, 0 == i % 2 ? "World" : "Hello" );
  }
  const invertable_multimap<std::string, int> cit = t.inverse();

  std::multimap<std::string, std::string> b;
  b.insert( std::make_pair( "bla", "blabla" ) );
  const invertable_multimap<std::string, std::string> cib( b );

  if ( max / 2 == cit.count( "World" ) && 0 == in.count( 1.11 ) &&
       max / 2 + 1 == cit.count( "Hello" ) && max == t.count( 3 ) &&
       cit.inverse().count( 3 ) == t.count( 3 ) )
  {
    your_mark = t.count( 1 ) + cib.count( "bla" );
  }
  //*/
  //* 3-as
  invertable_multimap<std::string, std::string> ib( b );
  ib( "bla", 0 ) = ":-)";

  std::multimap<int, int> x;
  for( int i = 0; i < max; ++i )
  {
    x.insert( std::make_pair( 1, i ) );
  }
  invertable_multimap<int, int> ix( x );
  int sum = 0;
  for( int i = 0; i < ix.count( 1 ); ++i )
  {
    sum += ix( 1, i );
  }

  if ( "bla" < cib( "bla", 0 ) && max * ( max - 1 ) / 2 == sum )
  {
    your_mark = ib( "bla", 0 ).size();
  }
  //*/
  //* 4-es
  std::multimap<std::string, std::string, string_size_less> ma;
  ma.insert( std::make_pair( "Hello", "World" ) );
  ma.insert( std::make_pair( "World", "Hello" ) );
  invertable_multimap<std::string, std::string> im ( ma );

  std::multimap<std::string, int> c;
  c.insert( std::make_pair( "PHP", 2 ) );
  c.insert( std::make_pair( "Ada", 3 ) );
  c.insert( std::make_pair( "C++", 4 ) );
  c.insert( std::make_pair( "Java", 2 ) );
  c.insert( std::make_pair( "CLU", 5 ) );
  const invertable_multimap<std::string, int, string_size_less> s( c );

  if ( 2 == s( "Ruby", 0 ) && 1 == im.count( "Hello" ) )
  {
    your_mark = s.count( ";-)" );
  }
  //*/
  //* 5-os
  std::multimap<std::string, std::string> f;
  f.insert( std::make_pair( "C++", ":-D" ) );
  const invertable_multimap<std::string, std::string,
                            string_size_less,
                            string_size_less> tf( f );
  const invertable_multimap<std::string, std::string,
                            string_size_less,
                            string_size_less> itf = ~tf;

  if ( 1 == itf.count( ":-o" ) && "C++" == itf( ":-P", 0 ) &&
       1 == (~cit).count( 1 ) && 0 == (~in).count( 7.7 ) )
  {
    your_mark = tf.count( "C++" ) + tf( ":-)", 0 ).size() + itf.count( ";-)" );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
