#include <iostream>
#include "smatrix.h"
#include "smatrix.h"
#include <vector>
#include <list>
#include <deque>
#include <algorithm>

class Default
{

  int i;

public:

  Default( int x = 6 ): i ( x ) { }

  int value() const
  {
    return i;
  }
};

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  SymmetricMatrix<std::vector<int>, int> mvi( 3 );
  mvi.set( 1, 2 , 3 ).set( 3, 2, 1 );

  SymmetricMatrix<std::list<Default>, Default> t( max );

  SymmetricMatrix<std::deque<int>, int> mdi( max );
  for( int i = 1; i <= max; ++i )
  {
    mdi.set( i, 1, i );
  }
  const SymmetricMatrix<std::deque<int>, int> cmdi = mdi;

  if ( 2 == cmdi.at( 1, 2 ) &&
       3 == cmdi.at( 3, 1 ) &&
       0 == cmdi.at( max / 2, max / 2 ) &&
       sizeof( mvi ) != sizeof( t ) &&
       sizeof( mvi ) != sizeof( cmdi ) &&
       max * max == cmdi.size() &&
       9 == mvi.size() )
  {
    yourMark = t.at( 1, 1 ).value() - mvi.at( 2, 1 ) - mvi.at( 3, 2 );
  }
  //*/
  //* 3-as
  SymmetricMatrix<std::list<double>, double> s( max );
  s( 5, 3 ) = s( 2, 4 ) = 4.31;
  s( 2, 2 ) = 2.4;
  ++mdi( 1, 2 );

  if ( 2.5 < s( 3, 5 ) &&
       2 == cmdi( 2, 1 ) &&
       2.2 < s( 2, 2 ) &&
       3 == mdi.at( 1, 2 ) )
  {
    yourMark = mdi( 1, 2 );
  }
  //*/
  //* 4-es
  SymmetricMatrix<std::deque<int> > a( 3 );
  SymmetricMatrix<std::list<int> > b( 3 );
  SymmetricMatrix<std::vector<int> > c( 4 );
  SymmetricMatrix<std::list<int> > d( 3 );

  a( 1, 1 ) = b( 1, 1 ) = c( 1, 1 ) = d( 1, 1 ) = 7;
  a( 1, 2 ) = b( 2, 1 ) = c( 1, 2 ) = d( 2, 2 ) = 3;

  if ( a == b &&
       !( c == a ) &&
       !( d == a ) )
  {
    yourMark = c( 1, 1 ) - b( 1, 2 );
  }
  //*/
  //* 5-os
  SymmetricMatrix<std::vector<bool> > mb( max );
  mb( 1, 1 ) = mb( 1, 2 ) = true;

  SymmetricMatrix<std::vector<double> > x ( 3 );
  x( 1, 2 ) = x( 3, 3 ) = 4.3;
  SymmetricMatrix<std::list<double> > y( 4 );
  y( 2, 1 ) = y( 2, 2 ) = y( 4, 3 ) = 5.4;

  const SymmetricMatrix<std::vector<double> > z = x + y;

  if ( 16 == z.size() &&
       mb( 2, 1 ) &&
       !mb( 3, 3 ) &&
       9.2 < z( 1, 2 ) &&
       9.9 > z( 1, 2 ) &&
       5.2 < z( 2, 2 ) &&
       5.7 > z( 2, 2 ) &&
       0.2 > z( 4, 4 ) )
  {
    yourMark = d( 1, 1 ) - mb( 1, 2 ) - mb( 1, 1 );
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
