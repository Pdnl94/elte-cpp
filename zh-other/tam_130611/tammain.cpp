#include <iostream>
#include "tamatrix.h"
#include "tamatrix.h"
#include <algorithm>

class def
{

  int i;

public:

  def( int x = 2 ): i ( x ) { }


  int get() const
  {
    return i;
  }

  def& operator++()
  {
    ++i;
    return *this;
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  triangular_associative_matrix<std::string, double> m;
  m.add_row_column( "AA" );
  m.add_row_column( "AB" );
  m.add_row_column( "AC" );
  m.add_row_column( "AAA" );

  m.set( "AA", "AB", 5.4 );
  m.set( "AB", "AA", 2.3 );
  m.set( "AB", "AC", 1.2 );
  m.set( "AC", "AB", 4.3 );
  m.set( "AAA", "AC", 5.2 );
  m.set( "AC", "AAA", 1.1 );

  const triangular_associative_matrix<std::string, double> cm = m;

  triangular_associative_matrix<int, def> t;
  for( int i = 0; i <= max; ++i )
  {
    t.add_row_column( i );
  }
  for( int i = 0; i < max; ++i )
  {
    t.set( i + 1, i, def( i ) );
    t.set( i, i + 1, def( i ) );
  }

  if ( 0.7 > cm.at( "AC", "AAA" ) &&
       0.5 > cm.at( "AC", "AC" ) &&
       0.7 > cm.at( "AB", "AC" ) &&
       1.4 < cm.at( "AB", "AA" ) &&
       1.2 < cm.at( "AC", "AB" ) )
  {
    your_mark = t.at( max / 2, max / 3 ).get();
  }
  //*/
  //* 3-as
  m.at( "AB", "AA" ) = 6.7;
  ++t.at( 1, 1 );

  triangular_associative_matrix<int, int> a;
  triangular_associative_matrix<int, int> b;
  triangular_associative_matrix<int, int> c;
  triangular_associative_matrix<int, int> d;

  for( int i = 0; i < max; ++i )
  {
    a.add_row_column( i );
    b.add_row_column( i );
    c.add_row_column( i );
    d.add_row_column( i + 1 );
  }

  a.at( 5, 3 ) = b.at( 5, 3 ) = d.at( 5, 3 ) = 4;
  c.at( 6, 2 ) = 3;

  if ( a == b && a != d && b != c && m.at( "AB", "AA" ) > cm.at( "AB", "AA" ) )
  {
    your_mark = t.at( 1, 1 ).get();
  }
  //*/
  //* 4-es
  triangular_associative_matrix<int, bool> s;
  s.add_row_column( max );
  s( max, max ) = true;

  triangular_associative_matrix<int, int> x;
  x.add_row_column( 0 );
  x.add_row_column( 1 );
  x.add_row_column( 2 );
  x( 0, 0 ) = 3;
  x( 1, 1 ) = 5;
  x( 2, 2 ) = 6;
  const triangular_associative_matrix<int, int> cx = x;
  x.erase( 1 );

  ++t( 1, 1 );

  if ( 90 == cx.determinant( 1 ) &&
       18 == x.determinant( 1 ) &&
       s( max, max ) &&
       6 == x( 2, 2 ) )
  {
    your_mark = t.at( 1, 1 ).get();
  }
  //*/
  //* 5-os
  triangular_associative_matrix<char, int> u;
  triangular_associative_matrix<char, int> v;
  u.add_row_column( 'A' );
  u.add_row_column( 'B' );
  v.add_row_column( 'A' );
  v.add_row_column( 'C' );
  u( 'A', 'A' ) = 1;
  u( 'B', 'A' ) = 2;
  u( 'B', 'B' ) = 3;
  v( 'A', 'A' ) = 4;
  v( 'C', 'A' ) = 2;
  v( 'C', 'C' ) = 2;
  const triangular_associative_matrix<char, int> uv = u + v;

  if ( 0 == uv( 'C', 'B' ) &&
       0 == uv( 'B', 'C' ) &&
       3 == uv( 'B', 'B' ) )
  {
    your_mark = uv( 'A', 'A' );
  }

  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
