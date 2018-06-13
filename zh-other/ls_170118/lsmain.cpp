#include <iostream>
#include <list>
#include "listsort.h"
#include <string>
#include <iterator>
#include <algorithm>
#include "listsort.h"
#include <numeric>

struct string_size_less: std::binary_function<std::string, std::string, bool>
{

  bool operator()( const std::string& lhs, const std::string& rhs ) const
  {
    return lhs.size() < rhs.size();
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  std::list<int> la;
  for( int i = 0; i < max; ++i )
  {
    la.push_front( i );
  }
  std::list<int> lb;
  lb.push_back( max / 2 );
  lb.push_back( 4 );

  std::list<int> lc;
  lc.push_back( 0 );
  lc.push_back( max / 2 );

  list_sorter<int> si( la );
  si.add( lb ).add( lc );

  std::list<std::string> ld;
  ld.push_back( "C++" );
  ld.push_back( "Ada" );
  ld.push_back( "C" );

  std::list<std::string> le;
  le.push_back( "Python" );
  list_sorter<std::string> s( ld );
  s.add( le );

  if ( lc.empty() && lb.empty() && 4 + max == la.size() && 4 == ld.size() &&
       0 == la.front() && "Python" == ld.back() && max - 1 == la.back() &&
       3 == std::count( la.begin(), la.end(), max / 2 ) )
  {
    your_mark = std::count( la.begin(), la.end(), 0 );
  }
  //*/
  //* 3-as
  std::list<double> lf;
  lf.push_back( 5.4 );
  lf.push_back( 3.3 );
  const list_sorter<double> sd( lf );

  s.remove( "C" );
  si.remove( max - 1 ).remove( 8 );

  if ( max - 2 == la.back() && 0 == std::count( ld.begin(), ld.end(), "C" ) &&
       4.1 > lf.front() && 1 == sd.list_count() && max + 2 == la.size() &&
       0 == std::count( la.begin(), la.end(), 8 ) )
  {
    your_mark = si.list_count();
  }
  //*/
  //* 4-es
  std::list<std::string> lg;
  lg.push_back( "Scala" );
  lg.push_back( "Haskell" );
  lg.push_back( "Simula" );
  lg.push_back( "C++" );
  lg.push_back( "Clean" );
  lg.push_back( "Assembly" );
  list_sorter<std::string, string_size_less> sl( lg );
  sl.remove( "Clean" );

  if ( "C++" == lg.front() && 8 == lg.back().size() &&
       0 == std::count( lg.begin(), lg.end(), "Scala" ) )
  {
    your_mark = lg.size();
  }
  //*/
  //* 5-os
  std::list<std::string> lgs;
  lgs.push_back( "Prolog" );
  lgs.push_back( "Javascript" );
  list_sorter<std::string> slg( lgs );

  sl += slg;

  if ( lgs.empty() && 6 == lg.size() && 0xA == lg.back().size() )
  {
    your_mark += std::count( lg.begin(), lg.end(), "Prolog" );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}