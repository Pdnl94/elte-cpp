#include <iostream>
#include "filtdata.h"
#include <algorithm>
#include <string>
#include <functional>
#include "filtdata.h"
#include <cctype>

struct is_lower: std::unary_function<char, bool>
{
  bool operator()( char ch ) const
  {
    return std::islower( ch );
  }
};

struct long_string: std::unary_function<std::string, bool>
{
  bool operator()( const std::string& s ) const
  {
    return s.length() > 3;
  }
};

template <int N>
struct mod_pred: std::unary_function<int, bool>
{
  bool operator()( int x ) const
  {
    return 0 == x % N;
  }
};

const int max = 1000;

struct too_big: std::unary_function<int, bool>
{
  bool operator()( int x ) const
  {
    return x > max / 4;
  }
};

int main()
{
  int your_mark = 1;
  //* 2-es
  filterable_data<char, is_lower> s;
  s.push_back( 'H' );
  s.push_back( 'e' );
  s.push_back( 'l' );
  s.push_back( 'l' );
  s.push_back( 'o' );
  s.push_back( 'W' );
  s.push_back( 'o' );
  s.push_back( 'r' );
  s.push_back( 'l' );
  s.push_back( 'd' );
  const filterable_data<char, is_lower> cs = s;
  s.set_filter_on();

  filterable_data<int, mod_pred<2> > t;
  for( int i = 0; i < max; ++i )
  {
    t.push_back( i );
  }
  t.set_filter_on();

  filterable_data<std::string, long_string> langs;
  langs.push_back( "C" );
  langs.push_back( "C++" );
  langs.push_back( "Java" );
  langs.push_back( "Ada" );
  langs.set_filter_on();

  if ( 1 == cs.index_of( 'e' ) &&
       "C++" == langs.max() &&
       10 == cs.size() &&
       max / 2 == t.size() &&
       max / 2 - 1 == t.index_of( max - 1 ) &&
       'r' == cs.max() )
  {
    your_mark = s.size();
  }
  //*/
  //* 3-as
  t.set_filter_off();
  langs.set_filter_off();

  if ( 2 == langs.index_of_max() &&
       max - 1 == t.index_of_max() &&
       7 == cs.index_of_max() &&
       max / 2 - 1 == t.average() )
  {
    your_mark = langs.index_of( "Ada" );
  }
  //*/
  //* 4-es
  t.set_filter_on();
  filterable_data<int, too_big> b = t;
  b.set_filter_on();
  filterable_data<int, mod_pred<3> > x = b;
  x.set_filter_on();
  filterable_data<int, mod_pred<5> > y = x;
  y.set_filter_on();
  filterable_data<int, mod_pred<7> > z = y;
  z.set_filter_on();
  filterable_data<int, mod_pred<13> > w = z;
  w.set_filter_on();
  filterable_data<int, mod_pred<11> > primes = w;
  primes.set_filter_on();
  if ( 100 == primes.size() + w.size() &&
       241 == primes.max() &&
       12 == primes.index_of( 61 ) )
  {
    your_mark = primes.index_of( 29 );
  }
  //*/
  //* 5-os
  primes.set_filter_off();
  const filterable_data<int, mod_pred<11> > cp = primes;
  primes.set_filter_on();

  filterable_data<int, mod_pred<11> >::const_iterator it0 =
    std::find( cp.begin(), cp.end(), 121 );
  filterable_data<int, mod_pred<11> >::const_iterator it1 =
    std::find( primes.begin(), primes.end(), 121 );

  if ( primes.end() != it0 &&
       121 == *it0 &&
       primes.end() == it1 )
  {
    your_mark = std::count_if( cp.begin(), cp.end(), mod_pred<11>() ) +
                *cp.begin();
  }
  //*/
  std::cout << "Your mark is "
            << your_mark
            << std::endl;
}
