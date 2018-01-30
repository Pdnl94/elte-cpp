#include <iostream>
#include <functional>
#include "pattern.h"
#include <set>
#include "pattern.h"
#include <string>
#include <list>
#include <cctype>

struct case_insensitive: std::binary_function<char, char, bool>
{

  bool operator()( char a, char b ) const
  {
    return std::tolower( a ) == std::tolower( b );
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  std::string msg = "Hello World";
  std::vector<char> vm( msg.begin(), msg.end() );
  std::set<char> alts;
  alts.insert( 'l' );
  alts.insert( 'e' );
  std::set<char> sa;
  sa.insert( 'o' );
  sa.insert( 'k' );

  pattern<char> p;
  p.push_back( alts ).push_back( alts ).push_back( alts ).push_back( sa );
  p.push_back( alts ).pop_back().push_back( sa ).pop_back();

  const pattern<char> cp = p;

  p.push_back( alts );

  pattern<std::set<char> > t;
  t.push_back( alts );
  std::vector<std::set<char> > vt;
  vt.push_back( alts );

  std::set<int> ia;
  pattern<int> pa;
  pattern<int> npa;
  std::vector<int> va;
  va.push_back( max / 2 );
  va.push_back( max / 3 );
  for( int i = 0; i < max; ++i )
  {
    va.push_back( i );
    if ( i < max / 2 )
    {
      pa.push_back( i );
      ia.insert( max / 2 + i );
      npa.push_back( max / 2 );
    }
    else
    {
      pa.push_back( ia );
    }
  }

  if ( 1 == cp.index_of( vm ) &&
       pattern<char>::npos == p.index_of( vm ) &&
       pattern<int>::npos == npa.index_of( va ) &&
       0 == t.index_of( vt ) )
  {
    your_mark = pa.index_of( va );
  }
  //*/
  //* 3-as
  p = cp;
  p.pop_back().push_back_one_arbitrary().push_back_one_arbitrary();

  pattern<int> ipa;
  for( int i = 1; i < max; ++i )
  {
    if( 1 == i % 2 )
    {
      ipa.push_back_one_arbitrary();
    }
    else
    {
      ipa.push_back( i );
    }
  }
  pattern<char> npc;
  npc.push_back_one_arbitrary().push_back( 'W' ).push_back( 'O' );

  t.pop_back().push_back_one_arbitrary();

  if ( 0 == t.index_of( vt ) &&
       pattern<char>::npos == npc.index_of( vm ) &&
       1 == p.index_of( vm ) )
  {
    your_mark = ipa.index_of( va );
  }
  //*/
  //* 4-es
  p.push_back_many_arbitraries();
  p.push_back( 'd' );
  const pattern<char> cpn = p;

  p.push_back_many_arbitraries();
  p.push_back( '!' );

  pattern<int> s;
  s.push_back( max / 250 );
  s.push_back_many_arbitraries();
  s.push_back( max / 3 );
  s.push_back_many_arbitraries();
  s.push_back( max / 2 );

  std::list<int> d( va.begin(), va.end() );

  std::list<int>::iterator li = s.find( d.begin(), d.end() );
  std::string::iterator si = cpn.find( msg.begin(), msg.end() );

  if ( si != msg.end() && 1 == si - msg.begin() &&
       msg.end() == p.find( msg.begin(), msg.end() ) &&
       li != d.end() )
  {
    your_mark = *li;
  }
  //*/
  //* 5-os
  std::set<char> a;
  a.insert( 'o' );
  a.insert( 'w' );
  a.insert( 's' );
  pattern<char, case_insensitive> in;
  in.push_back( 'L' ).push_back( 'O' );
  in.push_back_one_arbitrary();
  in.push_back( a ).push_back( a );

  pattern<char, case_insensitive> ins;
  ins.push_back( 'L' ).push_back( 'D' );

  si = in.find( msg.begin(), msg.end() );
  std::string::iterator it = ins.find( msg.begin(), msg.end() );
  if ( si != msg.end() )
  {
    your_mark = msg.end() - it + in.index_of( vm );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
