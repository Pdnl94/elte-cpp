#include <iostream>
#include <set>
#include <deque>
#include "arrdecor.h"
#include <list>
#include <string>
#include <functional>
#include "arrdecor.h"
#include <vector>


struct string_size_less
{

  bool operator()( const std::string& lhs, const std::string& rhs ) const
  {
    return lhs.size() < rhs.size();
  }

};

class filter_pred: public std::unary_function<int, bool>
{

  int i;

public:

  filter_pred( int f ): i( f ) { }

  bool operator()( int x ) const
  {
    return x < i;
  }
};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  int a[] = { 3, 5, 6, 6, 4 };
  array_decorator<std::list<int>, int> d( a, sizeof( a ) / sizeof( a[ 0 ] ) );
  const std::list<int> cc = d.sort().reverse().get();

  double da[] = { 3.87, 1.11, 9.21 };
  array_decorator<std::deque<double>, double> dda( da, sizeof( da ) / sizeof( da[ 0 ] ) );
  const std::deque<double> dd = dda.reverse().get();

  std::string sa[] = { "bla", "bla", "bla" };
  const array_decorator<std::vector<std::string>, std::string> vsa( sa, sizeof( sa ) / sizeof( sa[ 0 ] ) );
  const std::vector<std::string> t = vsa.get();

  int v[ max ];
  for( int i = 0; i < max; ++i )
  {
    v[ i ] = i % 2;
  }
  array_decorator<std::vector<int>, int> via( v, max );
  std::vector<int> vx = via.sort().reverse().get();

  if ( t[ 0 ] == t[ 1 ] && 8.3 < dd[ 0 ] && 1.5 > dd[ 1 ] && max * 1u == vx.size() &&
       3 == t.size() && vx[ 0 ] > vx[ max / 2 + 1] && cc.size() > dd.size() )
  {
    your_mark = cc.front() / cc.back();
  }
  //*/
  //* 3-as
  array_decorator<std::list<std::string>, std::string> lsa( sa, sizeof( sa ) / sizeof( sa[ 0 ] ) );
  const std::list<std::string> lt = lsa.sort().unique().get();

  array_decorator<std::list<int>, int> vda( v, max );
  vda.swap( d );
  std::list<int> cd = vda.unique().get();
  std::list<int> c =  d.get();

  vx = via.unique().get();

  if ( 1 == lt.size() && max * 1u == c.size() && 0 == c.front() &&
       4 == cd.size() && 6 == cd.front() )
  {
    your_mark = lt.front().size();
  }
  //*/
  //* 4-es
  array_decorator<std::multiset<int>, int> md( v, max );
  array_decorator<std::vector<int>, int> xd( v, max );

  md.filter( filter_pred( 1 ) );
  xd.filter( filter_pred( max ) );

  xd.swap( md );

  std::multiset<int> ms = md.get();
  std::vector<int> vxd = xd.get();

  cd = vda.filter( filter_pred( max ) ).get();

  if( 1u * max == ms.size() && ms.count( 0 ) == vxd.size() )
  {
    your_mark = cd.size();
  }
  //*/
  //* 5-os
  std::string langs[] = { "C++", "C", "Python" };
  array_decorator<std::vector<std::string> > dla( langs, sizeof( langs ) / sizeof( langs[ 0 ] ) );
  std::vector<std::string> dlv = dla.sort( string_size_less() ).get();

  if ( "C++" == dlv[ 1 ] )
  {
    your_mark = dlv[ 2 ].size() - dlv[ 0 ].size();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
