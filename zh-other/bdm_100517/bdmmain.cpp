#include <map>
#include <functional>
#include <iostream>
#include <algorithm>
#include <string>
#include "bimap.h"

struct LengthSum
{
  int length;
  
  LengthSum():length(0) {}

  void operator()(const std::pair<std::string, std::string>& p)
  {
    length += p.first.length();
    length += p.second.length();
  }  
};

const int max = 1000;

int main()
{
  int yourMark = 1;
  //* 2-es
  BidirectionalMap<int> fun;
  for( int i = 1; i <= max; ++i )
    fun.insert( i, i + max );
    
  BidirectionalMap<std::string> tel;
  tel.insert( "Aniko", "+36(70)555-8124" );
  tel.insert( "Botond", "+36(30)555-4321" );
  
  const BidirectionalMap<std::string> ctel = tel;

  if ( fun.at( 1 ) == (1 + max) &&
       ctel.at( "+36(30)555-4321" ) == "Botond" )
  {       
    yourMark = ctel.count( "Aniko" ) +
               fun.count( max * 2 ) +
	       ctel.count( "Unknown" );
  }
  //*/
  //* 3-as
  tel.erase( "+36(70)555-8124" );
  if ( 0 == tel.count( "Aniko" ) &&
       max == fun.size() )
  {
    yourMark = ctel.size() + tel.size();
  }    
  //*/
  //* 4-es
  const int l = std::for_each( ctel.begin(), ctel.end(), LengthSum() ).length;
  yourMark = l/10;
  //*/
  //* 5-os
  std::map<double, double> md;
  md[1.12] = 8.8;
  md[5.4] = 7.5;
  
  std::multimap<int, int> mmi;
  mmi.insert( std::make_pair( 1, 2 ) );
  mmi.insert( std::make_pair( 3, 6 ) );
  mmi.insert( std::make_pair( 5, 8 ) );
  
  const BidirectionalMap<int> b( mmi.begin(), mmi.end() );
  const BidirectionalMap<double> bd( md.begin(), md.end() );
  if ( b.at(8) == 5 )
  {
    yourMark = b.size() +
               bd.size() +
	       b.count( 9 ); 
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
