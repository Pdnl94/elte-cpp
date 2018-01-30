#include <iostream>
#include "pacont.h"
#include <string>
#include "pacont.h"

int max = 1000;

struct has_even_size
{

  template <class Cont>
  bool operator()( const Cont& c ) const
  {
    return c.size() % 2 == 0;
  }

};

struct has_enough_elements
{

  template <class Cont>
  bool operator()( const Cont& c ) const
  {
    return c.size() > max / 2;
  }

};

int main()
{
  int your_mark = 1;
  //* 2-es
  predicate_alternating_container<int, has_enough_elements> a;
  predicate_alternating_container<int, has_even_size> p;
  for( int i = 0 ; i < max; ++i )
  {
    a.insert( i );
    p.insert( i );
  }

  predicate_alternating_container<std::string, has_even_size> s;
  s.insert( "Hello" );
  s.insert( "World" );
  const predicate_alternating_container<std::string, has_even_size> cs = s;
  if ( max == a.size() && "Hello" == cs.at( 0 ) &&
       max - 1 == a.at( 0 ) && 1 == a.at( max / 2 ) &&
       max - 2 == p.at( 0 ) && max - 1 == p.at( max - 1 ) )
  {
    your_mark = cs.size();
  }
  //*/
  //* 3-as
  for(int i = max / 2; i > 0; --i )
  {
    p.erase( i );
  }
  s[ 0 ] = "Hi";
  if ( p.size() == max / 2 && 5 == p[ 2 ] )
  {
    your_mark = cs[ 1 ].size() - s[ 0 ].size();
  }
  //*/
  //* 4-es
  const predicate_alternating_container<int, has_even_size> ca = a;
  if ( ca.size() == a.size() &&
       max / 2 == ca[ ca.size() - 1 ] && max / 2 - 1 == ca[ 0 ] )
  {
    your_mark = ca[ 1 + 3 * max / 4 ];
  }
  //*/
  //* 5-os
  predicate_alternating_container<std::string, has_enough_elements> r;
  r.insert( "Hi" );
  r.insert( "World" );
  if ( r == s && !( p == a ) && !( p == ca ) )
  {
    your_mark = r[ 1 ].size();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
