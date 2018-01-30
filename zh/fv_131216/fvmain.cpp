#include <iostream>
#include "filtvec.h"
#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>
#include "filtvec.h"

const int max = 1000;

struct is_odd: std::unary_function<int, bool>
{
  bool operator()( int i ) const
  {
    return 1 == i % 2;
  }
};

struct long_enough: std::unary_function<std::string, bool>
{
  bool operator()( const std::string& s ) const
  {
   return s.length() > 2;
  }
};

struct is_true: std::unary_function<bool, bool>
{
  bool operator()( bool b ) const
  {
    return b;
  }
};

int main()
{
  int your_mark = 1;
  //* 2-es
  filterable_vector<int, is_odd> fvi;
  for( int i = 0; i < max; ++i )
  {
    fvi.push_back( i );
  }
  fvi.set_filter_on();

  filterable_vector<std::string, long_enough> fvs;
  fvs.push_back( "C++" );
  fvs.push_back( "C" );
  fvs.push_back( "Java" );
  fvs.set_filter_on();

  const filterable_vector<std::string, long_enough> cfvs = fvs;

  filterable_vector<int, is_odd> cfvi = fvi;
  if ( "Java" == fvs.at( 1 ) &&
       "C" == cfvs.at( 1 ) &&
       max / 2 == fvi.size() &&
       fvi.at( 1 ) == cfvs.size() &&
       cfvi.at( max / 3 ) != fvi.at( max / 3 ) )
  {
    your_mark = fvs.size();
  }
  //*/
  //* 3-as
  fvs[1] += "script";
  fvs.set_filter_off();
  fvs[1] += "obol";
  fvs.set_filter_on();
  fvi[0] = 8;

  if ( 3 == fvi[0] &&
       max == cfvi.size() &&
       "Cobol" == fvs[1] &&
       "C" == cfvs[1] &&
       "Javascript" == fvs[2] )
  {
    your_mark = fvs.size();
  }
  //*/
  //* 4-es
  filterable_vector<bool, is_true> fvb;
  fvb.push_back( true );
  fvb.push_back( false );
  fvb.push_back( true );
  fvb[ 0 ] = false;
  fvb.set_filter_on();

  std::vector<int> vi = fvi;
  std::vector<std::string> vs = fvs;

  if ( 1 == fvb.size() &&
       3 == vs.size() &&
       "Cobol" == vs[1] &&
       max / 2 - 1 == vi.size() )
  {
    your_mark = vi[4] - vi[2];
  }
  //*/
  //* 5-os
  filterable_vector<int, is_odd>::const_iterator i =
    std::find( fvi.begin(), fvi.end(), max / 2 );
  filterable_vector<int, is_odd>::const_iterator it =
    std::find( fvi.begin(), fvi.end(), 5 );
  filterable_vector<std::string, long_enough>::const_iterator ci =
    std::find( cfvs.begin(), cfvs.end(), "C" );

  int s = std::accumulate( fvi.begin(), fvi.end(), 1 );
  if ( i == fvi.end() && ci != cfvs.end() && 250000 == s )
  {
    your_mark = *it;
  }
  //*/
  std::cout << "Your mark is "
            << your_mark;
  std::endl( std::cout );
}
