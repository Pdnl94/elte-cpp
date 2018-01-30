#include <iostream>
#include <algorithm>
#include "filtmmap.h"
#include <numeric>
#include <string>
#include <functional>
#include "filtmmap.h"

struct is_even: std::unary_function<int, bool>
{

  bool operator()( int i ) const
  {
    return 0 == i % 2;
  }
};


struct is_odd: std::unary_function<int, bool>
{

  bool operator()( int i ) const
  {
    return 1 == i % 2;
  }
};

template<int N>
struct shorter_than: std::unary_function<std::string, bool>
{

  bool operator()( const std::string& s ) const
  {
    return s.size() < N;
  }

};

template <class T>
struct Sum
{
  int operator()( int x,
                  const std::pair<T, int>& p ) const
  {
    return x + p.second;
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  filterable_multimap<int, int, is_even, is_odd> t;
  for( int i = 0; i < max; ++i )
  {
    t.insert( i, i );
    t.insert( i, i + 1 );
    t.set_value_filter_on();
    t.set_value_filter_off();
  }
  t.set_value_filter_on();

  filterable_multimap<int, std::string, is_odd, shorter_than<3> > m;
  m.insert( 3, "Hello" );
  m.insert( 3, "World" );
  m.insert( 4, "Hi" );
  m.set_value_filter_on();

  filterable_multimap<std::string, int, shorter_than<3>, is_odd> im;
  im.insert( "Hello", 3 );
  im.insert( "World", 3 );
  im.insert( "Hi", 4 );
  im.set_value_filter_on();


  if ( 0 == m.count( 4 ) && 1 == t.count( max / 2 ) &&
       0 == im.count( "World" ) && 1 == im.count( "Hi" ) )
  {
    your_mark = m.count( 3 );
  }
  //*/
  //* 3-as
  im.set_value_filter_off();
  t.set_key_filter_on();
  if ( 2 == m.size() && max / 2 == t.size() && 0 == t.count( max / 2 ) )
  {
    your_mark = im.size();
  }
  //*/
  //* 4-es
  t.set_value_filter_off();
  t.set_key_filter_off();
  const filterable_multimap<int, int, is_even, is_odd> ct = t;

  m.set_key_filter_off();
  m.set_value_filter_off();
  for( int i = 0; i < m.count( 3 ); ++i )
  {
    m( 3, i ) = "C++";
  }
  m.set_value_filter_on();
  int s = 0;
  for( int i = 0; i < m.count( 3 ); ++i )
  {
    s += m( 3, i ).size();
  }

  if ( 2 * max == ct.size() && 6 == s && 1 == ct( 0, 0 ) + ct( 0, 1 ) )
  {
    your_mark = s - m.count( 3 );
  }
  //*/
  //* 5-os
  im.set_value_filter_off();
  im.set_key_filter_on();
  t.set_value_filter_off();
  t.set_key_filter_off();
  int a = std::accumulate( im.begin(), im.end(), 0, Sum<std::string>() );
  int b = std::accumulate( t.begin(), t.end(), 0, Sum<int>() );

  if ( 6 == a && max * max == b )
  {
    your_mark = m.begin() -> second.size() + m.count( 3 );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
