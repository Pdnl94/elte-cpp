#include <iostream>
#include <list>
#include "predcont.h"
#include <vector>
#include "predcont.h"

struct has_even_size
{

  template <class Cont, class T, class Pred>
  bool operator()( const predicate_container<Cont, T, Pred>& p ) const
  {
    return 0 == p.size() % 2;
  }
};

const int max = 1000;

struct is_long_enough
{

  template <class Cont, class T, class Pred>
  bool operator()( const predicate_container<Cont, T, Pred>& p ) const
  {
    return p.size() >= max /2;
  }

};

int main()
{
  int your_mark = 1;
  //* 2-es
  predicate_container<std::list<std::string>, is_long_enough, std::string> a;
  a.insert( "Some text" );
  predicate_container<std::list<char>, is_long_enough, char> h;
  h.insert( 'H' ).insert( 'e' ).insert( 'l' ).insert( 'l' ).insert( 'o' );
  h.insert( 'W' ).insert( 'o' ).insert( 'r' ).insert( 'l' ).insert( 'd' );
  const predicate_container<std::list<char>, is_long_enough, char> ch = h;

  predicate_container<std::vector<int>, has_even_size, int> v;
  for( int i = 0; i < max; ++i )
  {
    v.insert( i );
    v.insert( -1 );
  }

  if ( 10 == ch.size() && 2 * max == v.size() && 1 == a.size() &&
       max - 1 == v.at( 0 ) && v.at( 2 * max - 1 ) == v.at( 2 * max - 2 ) &&
       max == &( v.at( max ) ) - &( v.at( 0 ) ) &&
       sizeof( v ) != sizeof( h ) && max / 2 - 1 == v[ max / 2 ] &&
       &( ch.at( 1 ) ) + 1 != &( ch.at( 2 ) ) )
  {
    your_mark = h.at( 7 ) - h.at ( 4 ) - ( h.at( 1 ) - h.at( 9 ) );
  }
  //*/
  //* 3-as
  v.erase( -1 );
  h.erase( 'l' );
  if ( max == v.size() && 'H' == ch[ 0 ] &&
       9 == a[ 0 ].size() &&
       'o' == h[ 2 ]  && max - 1 == v[ 0 ] )
  {
    your_mark = ch.size() - h.size();
  }
  //*/
  //* 4-es
  predicate_container<std::vector<int> > s;
  for( int i = 0; i < max; ++i )
  {
    s.insert( i );
    s.insert( -1 );
  }
  s.erase( -1 );
  if ( max == s.size() && max / 2 == s[ max / 2 ] &&
       max / 7 == s[ max / 7 ] )
  {
    your_mark += s.size() / v.size();
  }
  //*/
  //* 5-os
  std::string msg = "blabla";
  predicate_container<std::list<char>, has_even_size> b( msg.begin(), msg.end() );

  std::list<int> c;
  c.push_front( 0 );
  predicate_container<std::vector<int> > vp( c.begin(), c.end() );

  if ( 0 == vp[ 0 ] && msg.size() == b.size() &&
       b[ 0 ] == b[ 3 ] )
  {
    your_mark = b.size() - vp.size();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
