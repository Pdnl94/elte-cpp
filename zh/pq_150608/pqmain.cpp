#include <iostream>
#include <string>
#include "prqueue.h"
#include <queue>
#include "prqueue.h"

struct has_even_size
{

  template <class T, class Pred>
  bool operator()( const predicate_queue<T, Pred>& q, const T& ) const
  {
    return 0 == q.size() % 2;
  }

};

struct int_mod_pred
{

  template <class Pred>
  bool operator()( const predicate_queue<int, Pred>& q, int i ) const
  {
    return i % 2  == q.size() % 2;
  }

};

struct if_found
{

  template<class T, class Pred>
  bool operator()( const predicate_queue<T, Pred>& q, const T& t ) const
  {
    for( int i = 0; i < q.size(); ++i )
    {
      if ( t == q[ i ] )
      {
        return true;
      }
    }
    return false;
  }

};

class param_pred
{

  int x;

public:

  param_pred( int i ): x( i ) { }

  template <class T, class Pred>
  bool operator()( const predicate_queue<T, Pred>& q, const T& ) const
  {
    return q.size() == x;
  }

};

const int max = 1000;

struct max_pred
{

  template <class T, class Pred>
  bool operator()( const predicate_queue<T, Pred>& q, const T& ) const
  {
    return q.size() < max / 2;
  }

};

int main()
{
  int your_mark = 1;
  //* 2-es
  predicate_queue<int, int_mod_pred> a;
  predicate_queue<int, int_mod_pred> b;
  predicate_queue<int, has_even_size> c;
  for( int i = 0; i < max; ++i )
  {
    a.push( 2 * i );
    b.push( i );
    c.push( i );
  }
  const predicate_queue<int, int_mod_pred> ca = a;
  const predicate_queue<int, int_mod_pred> cb = b;
  const predicate_queue<int, has_even_size> cc = c;

  predicate_queue<std::string, has_even_size> s;
  s.push( "World" );
  s.push( "Hello" );

  if ( ca.size() == b.size() && cc.size() == a.size() && 2 == s.size() &&
      max == cb.size() && 0 == cb.front() && 0 == a.front() && 0 == cb.at( 0 ) &&
      "World" == s.front() && max / 2 == cb.at( max / 2 )&&  0 == cc.at( max / 2 ) )
  {
    your_mark = ca.at( 0 ) / cc.at( 0 );
  }
  //*/
  //* 3-as
  predicate_queue<int, if_found> f;
  for( int i = 0; i < max / 2; ++i )
  {
    a.pop();
    b.pop();
    c.pop();
    c.pop();
    if ( 0 == i % 2 )
    {
      f.push( i );
    }
    else
    {
      f.push( 0 );
    }
  }
  ++f.front();
  if ( 0 == c.size() && max / 2 == a.size() && b.front() == b.size() &&
       max / 2 - 2 == f[ 0 ] && max == a[ max / 4 ] && 3 * max / 4 == b[ max / 4 ] )
  {
    your_mark += f.front();
  }
  //*/
  //* 4-es
  param_pred pp( your_mark );
  predicate_queue<int, param_pred> p( pp );
  for( int i = 0; i < max; ++i )
  {
    p.push( i );
  }
  if ( max - 1 == p[ 0 ] && 0 == p[ max - 2 ] )
  {
    your_mark = p[ max - 1 ] + p[ max - 3 ];
  }
  //*/
  //* 5-os
  std::queue<int> qc = cc;
  std::queue<int> qa = a;
  qc.pop();

  if ( max / 2 == qa.size() && max - 1 == qc.size() &&
       max == qa.front() )
  {
    your_mark += qc.front();
  }
  //*/
  std::cout << "Your mark is "
            << your_mark;
  std::endl( std::cout );
}