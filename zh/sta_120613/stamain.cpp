#include "stat.h"
#include <iostream>
#include <deque>
#include "stat.h"
#include <string>

struct StringSizeLess
{
  bool operator()( const std::string& a,
                   const std::string& b ) const
  {
    return a.size() < b.size();
  }
};

const int max = 1024;

int main()
{
  int yourMark = 1;
  //* 2-es
  Statistics<std::string> sts;
  sts.add( "Hello" );
  sts.add( "World" );
  sts.add( "Hello" );
  sts.erase( "Hello" );
  const Statistics<std::string> csts = sts;

  Statistics<int> sti;
  sti.add( 1 );
  sti.add( 9 );
  sti.add( 3 );
  sti.add( 3 );
  const Statistics<int> csti = sti;

  Statistics<double> st;
  st.add( 1.89 );
  st.add( 14.42 );
  st.add( 29.23 );
  st.add( 4.26 );

  Statistics<int> s;
  for( int i = 0; i < max; ++i )
  {
    s.add( i + 1 );
  }

  if ( 3 == csti.truncatedMean() &&
       9.8 > st.truncatedMean() &&
       max / 2 == s.truncatedMean() )
  {
    yourMark = csts.size();
  }
  //*/
  //* 3-as
  sts.add( "World" );
  for( int i = 0; i < 3; ++i )
  {
    sti.add( max );
  }
  if ( "World" == sts.mostFrequentElement() &&
       3 == csti.mostFrequentElement() &&
       max == sti.mostFrequentElement() &&
       9 == sti.median() )
  {
    yourMark = csti.median();
  }
  //*/
  //* 4-es
  sts.add( "Goodbye" );
  if ( "Goodbye" == sts.max( StringSizeLess() ) &&
       "World" == csts.max() &&
       max == s.max() )
  {
    yourMark = sts.size();
  }
  //*/
  //* 5-os
  std::string msgstr = "HelloWorld";
  const Statistics<char> msg( msgstr.begin(), msgstr.end() );
  std::deque<std::string> lang;
  lang.push_back( "Java" );
  lang.push_back( "ALGOL" );
  lang.push_back( "C++" );
  lang.push_back( "ALGOL" );
  const Statistics<std::string> ds( lang.begin(), lang.end() );
  if ( 'l' == msg.mostFrequentElement() &&
       "C++" == ds.min( StringSizeLess() ) )
  {
    yourMark = ds.mostFrequentElement().length();
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
