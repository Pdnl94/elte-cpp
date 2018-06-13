#include <iostream>
#include <string>
#include "trimatrix.h"
#include "trimatrix.h"
#include <algorithm>
#include <list>
#include <vector>
#include <deque>

class OnlyOneContainerAllowed { };

class OneVector: public std::vector<std::string>
{

  static int instances;

  void init()
  {
    ++instances;
    if ( instances > 1 )
    {
      throw OnlyOneContainerAllowed();
    }
  }

public:

  OneVector() { init(); }

  OneVector( size_t n ): std::vector<std::string>( n ) { init(); }

  OneVector( size_t n, const std::string& s ): std::vector<std::string>( n, s ) { init(); }

  OneVector( const OneVector& rhs ): std::vector<std::string>( rhs ) { init(); }

  template<class Iterator>
  OneVector( Iterator first, Iterator last ): std::vector<std::string>( first, last ) { init(); }

};

int OneVector::instances = 0;

class Default
{

  int x;

public:

  Default( int i = 4 ): x( i ) { }


  int value() const
  {
    return x;
  }

};

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  TriangularMatrix<std::vector<int>, int> vm( 3 );
  vm.set( 1, 2, 3 ).set( 3, 2, 1 ).set( 2, 2, 2 );
  const TriangularMatrix<std::vector<int>, int> cvm = vm;

  TriangularMatrix<OneVector, std::string> one( max );
  TriangularMatrix<std::list<Default>, Default> a( max );
  for( int i = 2; i < max; ++i )
  {
    a.set( i, i, i );
    one.set( i, i, "C++" );
  }

  if ( sizeof( vm ) != sizeof( a ) &&
       2 == cvm.at( 2, 2 ) &&
       0 == cvm.at( 1, 3 ) &&
       max / 2 == a.at( max / 2, max / 2 ).value() )
  {
    yourMark = cvm.size() - cvm.at( 2, 2 ) - cvm.at( 3, 2 ) - a.at( 1, 1 ).value();
  }
  //*/
  //* 3-as
  TriangularMatrix<std::deque<double>, double> s( 2 );
  s( 1, 1 ) = s( 2, 2 ) = 4.2;

  vm( 1, 1 ) = 5;
  ++vm( 3, 3 );
  std::swap( vm( 3, 2 ), vm( 2, 2 ) );
  if ( 0 == cvm( 1, 2 ) &&
       5 == vm( 1, 1 ) &&
       17 < s.determinant() &&
       18 > s.determinant() &&
       3.4 < s( 1, 1 ) )
  {
    yourMark = cvm.determinant() + vm.determinant() - cvm( 2, 2 );
  }
  //*/
  //* 4-es
  vm( 2, 2 ) += 3;
  vm.erase( 1 );

  s.erase( 2 );

  a.erase( 1 );

  if ( 1 == vm( 2, 2 ) &&
       4 == vm.size() &&
       s.determinant() < 6.5 &&
       2 == a( 1, 1 ).value() )
  {
    yourMark = vm.determinant();
  }
  //*/
  //* 5-os
  TriangularMatrix<std::vector<std::string> > x( 4 );
  const TriangularMatrix<std::list<std::string> > y( 4 );
  const TriangularMatrix<std::list<std::string> > z( max / 2 );
  TriangularMatrix<std::deque<int> > d( 2 );
  d( 2, 2 ) = 1;
  d( 1, 1 ) = 4;
  d( 2, 1 ) = 2;

  if ( y == x &&
       z != x &&
       d != cvm &&
       d == vm )
  {
    yourMark = d.determinant() + d.size() - a( 2, 2 ).value();
  }
  //*/
  std::cout << "Your mark is "
            << yourMark
            << std::endl;
}
