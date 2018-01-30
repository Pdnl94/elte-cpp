#include <iostream>
#include <algorithm>
#include "mmapview.h"
#include <map>
#include <numeric>
#include <string>
#include "mmapview.h"

struct string_size_less
{

  bool operator()( const std::string& lhs, const std::string& rhs ) const
  {
    return lhs.size() < rhs.size();
  }

};

struct nice
{

  bool operator()( const std::pair<const std::string, std::string>& p ) const
  {
    return p.first == "Ada" || p.first == "C++";
  }

};

struct love
{

  bool operator()( const std::pair<const std::string, std::string>& p ) const
  {
    return p.second == "<3";
  }

};

struct sum
{

  double operator()( double d, const std::pair<const int, double>& p ) const
  {
    return d + p.second;
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  multimap_view<int, double> mvid;

  std::map<int, double> m;
  mvid.add( m );

  for( int i = 0; i < max; ++i )
  {
    m[ i ] = 1.23;
  }

  std::map<int, double> mm;
  mvid.add( mm );

  for( int i = 0; i < max; ++i )
  {
    mm[ i ] = 3.21;
  }

  multimap_view<std::string, std::string> mvss;
  std::map<std::string, std::string> la;
  mvss.add( la );

  la[ "C++" ] = ":-)";
  la[ "Ada" ] = ":-/";
  la[ "Fortran" ] = "OMG";

  std::map<std::string, std::string> lb;
  mvss.add( lb );

  lb[ "C++" ] = "<3";
  lb[ "Haskell" ] = ":-o";

  std::map<std::string, std::string> lc;
  mvss.add( lc );

  lc[ "C++" ] = ":-D";
  lc[ "Java" ] = ":-|";
  lc[ "Fortran" ] = ":'(";

  const multimap_view<std::string, std::string> cmvss = mvss;

  if ( 1 == cmvss.count( "Java" ) && 3 == cmvss.count( "C++" ) &&
       mvid.count( 0 ) == mvss.count( "Fortran" ) && 1 == lc.count( "C++" ) &&
       3U == la.size() && max * 1U == m.size() )
  {
    your_mark = mvid.count( max / 2 );
  }
  //*/
  //* 3-as
  int cf = mvss.erase( "Fortran" );
  int ca = mvss.erase( "Agda" );

  mvss.remove( lb );

  mvid.remove( mm );
  int cz = mvid.erase( 0 );

  if ( 0 == lc.count( "Fortran" ) && max * 1U  == mm.size() &&
       m.count( 0 ) != mm.count( 0 ) && mm.size() != m.size() &&
       2 == cf && 0 == ca && 1 == cz)
  {
    your_mark = mvss.size() - mvid.count( max / 2 );
  }
  //*/
  //* 4-es
  mvid.add( mm );
  mvss.add( lb );
  std::multimap<std::string, std::string, string_size_less> a = mvss;
  std::multimap<int, double, std::greater<int> > b = mvid;

  if ( max - 1 == b.begin() -> first && 6 == a.size() && 1 == b.count( 0 ) &&
       1 == a.count( "Fortran" ) && 0 == a.count( "Brainfuck" ) )
  {
    your_mark = a.count( "SQL" );
  }
  //*/
  //* 5-os
  double s = std::accumulate( mvid.begin(), mvid.end(), 0., sum() );

  if ( s > 4400.2 && s < 4510.2 )
  {
    your_mark = std::count_if( mvss.begin(), mvss.end(), nice() ) +
                std::count_if( mvss.begin(), mvss.end(), love() );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
