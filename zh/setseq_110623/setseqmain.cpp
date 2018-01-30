#include <iostream>
#include <complex>
#include "setseq.h"
#include <algorithm>
#include <list>
#include <numeric>
#include <vector>
#include "setseq.h"
#include <deque>
#include <string>

const int max = 1000;

typedef std::complex<int> Complex;

int main()
{
  int yourMark = 1;
  //* 2-es
  SetSequence<std::list<int>, int> listset;
  SetSequence<std::deque<std::string>, std::string> deqset;
  
  SetSequence<std::vector<Complex>, Complex> vecset;
  vecset.push_back( Complex( 1, 2 ) );
  
  SetSequence<std::vector<Complex>, Complex> s;
  s.push_back( Complex( 3, 1 ) );
  s.push_back( Complex( 1, 2 ) );
  vecset.set_union( s );
  
  deqset.push_back( "Hello" );
  deqset.push_front( "World" );
  deqset.push_front( "Hello" );
  
  for( int i = 0; i < max; ++i )
  {
    listset.push_front( i + 1 );
    listset.push_front( i );
  }

  const SetSequence<std::list<int>, int> clistset = listset;
  const SetSequence<std::deque<std::string>, std::string> cdeqset = deqset;

  if ( sizeof( deqset ) != sizeof( listset ) &&
       1 + max == clistset.size() &&
       1 == clistset.back() &&
       "World" == cdeqset.front() )
  {
    yourMark = vecset.size();
  }
  //*/
  //* 3-as
  for( int i = 0; i < max; ++i )
  {
    listset.erase( i );
  }
  
  if ( 0 == listset.count( max / 2 ) && 1 == listset.count( max ) )
  {
    yourMark = listset.size() + cdeqset.size();
  }
  //*/
  //* 4-es
  SetSequence< std::vector<int> > vset;
  vset.push_back( 1 );
  vset.push_back( 3 );
  vset.push_back( 3 );
  SetSequence< std::vector<int> >::const_iterator i =
    std::find( vset.begin(), vset.end(), max );
  if ( i == vset.end() )
  {
    yourMark = std::accumulate( vset.begin(), vset.end(), 0 );
  }
  //*/
  //* 5-os
  SetSequence< std::list<Complex> > lcompset;
  SetSequence< std::deque<Complex> > dcompset;
  lcompset.push_front( Complex( 1, 2 ) );
  lcompset.push_front( Complex( 3, 1 ) );
  dcompset.push_back( Complex( 3, 1 ) );
  dcompset.push_back( Complex( 2, 4 ) );
  
  if ( lcompset == vecset && lcompset != dcompset )
  {
    yourMark = lcompset.size() + dcompset.size() + listset.size();
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
