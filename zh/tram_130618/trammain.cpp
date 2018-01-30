#include <iostream>
#include <algorithm>
#include "tamatrix.h"
#include "tamatrix.h"

class def
{

  int i;

public:

  def( int j = 2 ): i ( j ) { }


  int value() const
  {
    return i;
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  tridiagonal_associative_matrix<std::string, double> a;
  a.add_row_column( "XY" );
  a.add_row_column( "AB" );
  a.add_row_column( "AC" );
  a.add_row_column( "DE" );

  a.set( "XY", "AC", 5.6 );
  a.set( "XY", "AB", 1.6 );
  a.set( "AB", "XY", 4.2 );
  const tridiagonal_associative_matrix<std::string, double> ca = a;

  tridiagonal_associative_matrix<int, def> s;
  for( int i = 0; i <= max; ++i )
  {
    s.add_row_column( i );
    s.set( i, i, def( i ) );
  }

  if ( ca.at( "XY", "AC" ) < 7.2 &&
       ca.at( "XY", "AB" ) < 1.9 &&
       ca.at( "AB", "XY" ) > 2.5 &&
       max / 2 == s.at( max / 2, max / 2 ).value() )
  {
    your_mark = s.at( max - 1, max ).value();
  }
  //*/
  //* 3-as
  const tridiagonal_associative_matrix<std::string, double> o = ca;
  const tridiagonal_associative_matrix<int, def> cs = s;
  a.at( "AC", "DE" ) = a.at( "AB", "XY" ) = 7.5;
  ++a.at( "XY", "AB" );
  if ( ca == o &&
       ! ( a == ca ) &&
       6.3 < a.at( "AC", "DE" ) &&
       2.4 < a.at( "XY", "AB" ) )
  {
    your_mark = cs.at( max / 2, 0 ).value() + cs.at( 1, 1 ).value();
  }
  //*/
  //* 4-es
  a( "AC", "DE" ) = 7.5;
  ++a( "XY", "AB" );
  a.transpose();

  tridiagonal_associative_matrix<int, bool> b;
  b.add_row_column( 1 );
  b.add_row_column( 2 );
  b( 1, 2 ) = b( 2, 1 ) = true;

  if ( b( 1, 2 ) &&
       7.2 < a( "DE", "AC" ) &&
       0.7 < ca( "XY", "AB" ) &&
       1.2 > a( "AC", "DE" ) )
  {
    your_mark = cs( max / 2, max / 3 ).value() * cs( max / 4, max / 5 ).value();
  }
  //*/
  //* 5-os
  a.erase( "AB" );
  a.set( "XY", "AC", 5.6 );
  tridiagonal_associative_matrix<int, int> x;
  x.add_row_column( 1 );
  x.add_row_column( 3 );
  x.add_row_column( 4 );
  x( 1, 1 ) = 7;
  x( 1, 3 ) = x( 3, 1 )= 3;
  x( 3, 3 ) = 8;

  tridiagonal_associative_matrix<int, int> y;
  y.add_row_column( 1 );
  y.add_row_column( 2 );
  y.add_row_column( 3 );
  y( 1, 1 ) = y( 3,3 ) = 2;

  const tridiagonal_associative_matrix<int, int> z = x - y;

  if ( 5.4 < a( "XY", "AC" ) &&
       x != y &&
       6 == z( 3, 3 ) )
  {
    your_mark = z( 1, 1 );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
