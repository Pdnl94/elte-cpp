#include "dirseq.h"
#include <iostream>
#include <algorithm>
#include "dirseq.h"
#include <string>

struct IsEven
{
  bool operator()( int i ) const
  {
    return i % 2 == 0;
  }
};

const int max = 1024;

int main()
{
  int yourMark = 1;
  //* 2-es
  DirectionSequence<int> di;
  di.push_back( 1 );
  di.push_back( 2 );
  di.push_back( 5 );
  const DirectionSequence<int> cdi = di;
  di.change_direction();
  di.push_back( 3 );
  di.push_back( 7 );
  DirectionSequence<std::string> ds;
  ds.push_back( "Test" );
  DirectionSequence<double> x;
  for( int i = 0; i < max; ++i )
  {
    x.push_back( i / 10.0 );
    x.change_direction();
  }
  if( 1 == cdi.at( 0 ) &&
      5 == di.at( 0 ) &&
      100.5 < x.at( 1 ) &&
      4 == ds.at( 0 ).length() )
  {
    yourMark = di.size() - cdi.size();
  }
  //*/
  //* 3-as
  x.at( 1 ) = 8.88;
  di.push_front( 9 );
  di.change_direction();
  di.push_back( 4 );
  di.change_direction();
  di[ 4 ] = 12;
  if ( 9.99 > x[ 1 ] &&
       12 == di[ 4 ] &&
       9 == di[ 1 ] )
  {
    yourMark = cdi[ 0 ] + cdi[ 1 ];
  }
  //*/
  //* 4-es
  di[ 1 ] = 8;
  di.change_direction();
  DirectionSequence<int>::iterator i = 
    std::find( di.begin(), di.end(), 8 );
  if ( i != di.end() )
  {
    yourMark = std::count_if( di.begin(), di.end(), IsEven() );
  }
  //*/
  //* 5-os
  DirectionSequence<int>::iterator j = di.begin();
  for( int i = 0; i < 5; ++i )
  {
    ++j;
  }
  int tmp = std::count_if( di.begin(), j, std::bind2nd( std::less<int>(), 10 ) );
  di.change_direction();
  yourMark = tmp + std::count_if( j, di.end(), std::bind1st( std::less<int>(), 10 ) );
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
