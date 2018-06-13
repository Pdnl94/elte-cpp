#include <iostream>
#include "vcstring.h"
#include <list>
#include <set>
#include <string>
#include "vcstring.h"


const unsigned int max = 1000u;

int main()
{
  int your_mark = 1;
  //* 2-es
  version_controlled_basic_string<char> a;
  version_controlled_basic_string<wchar_t> s;
  for( unsigned int i = 0u; i < max; ++i )
  {
    s.commit();
    s.push_back( 0 == i % 2 ? L'A' : L'B' );
    s.commit();
    a.commit();
  }
  a.push_back( '?' );
  a.commit();
  a.push_back( '!' );

  version_controlled_basic_string<char> str;
  str.push_back( 'C' );
  str.commit();
  str.push_back( '+' );
  str.push_back( '+' );
  str.commit();

  str.update( 0 );
  s.update( max / 2 );

  if ( 1 == str.size() &&
       'C' == str[ 0 ] &&
       L'B' == s[ 1 ] &&
       max == s.size() * a.size() )
  {
    your_mark = a.commit();
  }
  //*/
  //* 3-as
  const version_controlled_basic_string<char> ca = a;
  const version_controlled_basic_string<wchar_t> cs = s;

  if ( &std::string::c_str != &version_controlled_basic_string<char>::c_str ||
       &std::string::size  != &version_controlled_basic_string<char>::size )
  {
    std::cout << "Use inheritance" << std::endl;
  }
  else
  {
    str.update( 1 );

    if ( 3 == ca.number_of_revisions() &&
         2 == str.number_of_revisions() &&
         1 + max == cs.number_of_revisions() &&
         '+' == str[ 1 ] )
    {
      your_mark = str.size();
    }
  }
  //*/
  //* 4-es
  version_controlled_basic_string<wchar_t> w = L"Java";
  w.commit();
  w.append( L"script" );
  w.revert();

  version_controlled_basic_string<char> msg = "Hello";
  version_controlled_basic_string<char> t = "Wor";
  t.commit();
  t.push_back( 'l' );
  t.commit();
  t.push_back( 'd' );
  t.commit();
  msg.swap( t );

  if ( 'W' == msg[ 0 ] &&
       t[ 4 ] == msg[ 1 ] &&
       0 == t.number_of_revisions() &&
       3 == msg.number_of_revisions() )
  {
    your_mark = w.size();
  }
  //*/
  //* 5-os
  std::list<char> li;
  li.push_back( 'p' );
  li.push_back( 'l' );

  std::set<char> st;
  st.insert( 'o' );
  st.insert( 'd' );
  st.insert( 'e' );

  version_controlled_basic_string<char> f( st.begin(), st.end() );
  version_controlled_basic_string<char> g( li.begin(), li.end() );

  if ( 'd' == f[ 0 ] &&
       'l' == g[ 1 ] &&
       'o' == f[ 2 ] )
  {
    your_mark = f.size() + g.size();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
