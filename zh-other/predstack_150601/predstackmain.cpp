#include <iostream>
#include "prstack.h"
#include <stack>
#include <string>
#include "prstack.h"

struct has_even_size
{

  template <class T, class Pred>
  bool operator()( const predicate_stack<T, Pred>& s ) const
  {
    return 0 == s.size() % 2;
  }

};

template <int limit>
struct has_more_elements
{

  template <class T, class Pred>
  bool operator()( const predicate_stack<T, Pred>& s ) const
  {
    return s.size() > limit;
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  predicate_stack<int, has_even_size> sa;
  predicate_stack<int, has_more_elements< max / 4> > sl;

  for( int i = 0; i < max; ++i )
  {
    sa.push( i );
    sl.push( i );
  }
  predicate_stack<std::string, has_even_size> strst;
  strst.push( "Hello" );
  strst.push( "World" );
  const predicate_stack<std::string, has_even_size> cs = strst;
  if ( "World" == cs.top() && sa.top() == sl.top() &&
       "Hello" == cs.at( 0 ) && max - 1 == sa.at( max - 1 ) &&
       max - 2 == sl.at( 1 ) && 2 == cs.size() && sl.size() == sa.size() )
  {
    your_mark = sa.at( 0 ) / sl.at( max / 2 );
  }
  //*/
  //* 3-as
  strst.pop();
  strst.push( "!" );
  strst.push( "Hello" );
  strst.top() = "Hi";
  for( int i = 0; i < max / 10; ++i )
  {
    sa.pop();
    sl.pop();
  }
  if ( sa.top() == sl.top() && ( max * 9 ) / 10 - 1 == sl[ 0 ] &&
       sa.size() == sl.size() && 1 == sa[ sa.size() / 2 ] )
  {
    your_mark = strst[ 0 ].size() + strst[ 2 ].size();
  }
  //*/
  //* 4-es
  predicate_stack<double> sd;
  sd.push( 4.7 );
  sd.push( 6.1 );
  sd.push( 1.1 );
  sd.pop();

  predicate_stack<std::string> ns;
  for( int i = 0; i <= max; ++i )
  {
    ns.push( "Hello" );
  }
  ns.push( "World" );
  for( int i = 0; i < max; ++i )
  {
    ns.pop();
  }
  if ( 6.0 < sd.top() && 4.8 > sd[ 0 ] && ns[ 1 ] == ns[ 0 ] &&
       "Hello" == ns.top() )
  {
    your_mark = ns.size() + sd.size();
  }
  //*/
  //* 5-os
  std::stack<int> csa = sa;
  std::stack<int> csl = sl;
  std::stack<std::string> ccs = cs;
  for( int i = 0; i < max / 4; ++i )
  {
    csa.pop();
    csl.pop();
  }
  if ( "World" == ccs.top() && csa.top() == csl.top() &&
       1 == csa.size() - csa.top() )
  {
    ccs.pop();
    your_mark = ccs.top().size();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
