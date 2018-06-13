#include <iostream>
#include <numeric>
#include <string>
#include "vcvec.h"
#include "vcvec.h"
#include <list>
#include <set>

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  version_controlled_vector<int> v;
  v.push_back( 1 );
  v.commit();

  v.push_back( 3 );
  v.commit();
  v.push_back( 9 );
  v.update( 0 );

  version_controlled_vector<std::string> a;
  version_controlled_vector<std::string> b;
  for( int i = 0; i < max; ++i )
  {
    a.commit();
    a.push_back( std::string( i, '?' ) );
    b.commit();
  }
  b.push_back( "C++" );
  a.update( max / 2 );

  if ( max / 2 == a.size() &&
       1 == b.size() &&
       max / 3 == a[ max / 3 ].size() &&
       1 == b.commit() &&
       v[ 0 ] == v.size() )
  {
    your_mark = v.commit();
  }
  //*/
  //* 3-as
  if ( &version_controlled_vector<int>::size != &std::vector<int>::size ||
       &version_controlled_vector<int>::pop_back != &std::vector<int>::pop_back )
  {
    std::cout << "Use inheritance!";
    std::endl( std::cout );
  }
  else
  {
    v.push_back( 4 );
    v.push_back( 7 );
    v.commit();
    v.push_back( 1 );
    v.revert();
    b[ 0 ] += " is cool.";
    b.commit();
    b.push_back( "8-)" );
    b.revert();

    if ( 1 == b.size() && 12 == b[ 0 ].size() )
    {
      your_mark = v.size();
    }
  }
  //*/
  //* 4-es
  std::vector<std::vector<std::string> > hista = a;
  std::vector<std::vector<int> > histv = v;

  b.swap( a );
  b.update( max / 2 );
  a.update( 1 );
  v.update( 1 );

  if ( max + 1 == hista.size() && 
       histv[ 4 ] == histv[ 3 ] &&
       histv[ 2 ] != histv[ 3 ] &&
       max / 4 == hista[ max / 4 ].size() &&
       "C++" == a[ 0 ] &&
       max / 2 == b.size() &&
       5 == histv.size() )
  {
    your_mark = std::accumulate( v.begin(), v.end(), 0 );
  }
  //*/
  //* 5-os
  std::list<int> c;
  c.push_back( 3 );
  c.push_back( 2 );

  std::set<double> s;
  s.insert( 4.1 );
  s.insert( 7.5 );
  s.insert( 1.3 );

  version_controlled_vector<int> cv( c.begin(), c.end() );
  version_controlled_vector<double> sv( s.begin(), s.end() );
  if ( sv[ 0 ] < 1.8 && sv[ 2 ] > 7.2 &&
       3 == cv[ 0 ] && 2 == cv[ 1 ] )
  {
    your_mark = cv.size() + sv.size();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
