#include <iostream>
#include <set>
#include <list>
#include "pattern.h"
#include <vector>
#include <string>
#include "pattern.h"
#include <cctype>
#include <functional>

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
  std::vector<char> v( msg.begin(), msg.end() );
  pattern<char> pc;
  pc.push_back( 'W' );
  pc.push_back_one_arbitrary();
  pc.push_back_one_arbitrary();
  pc.push_back( 'l' );
  const pattern<char> cpc = pc;
  pc.push_back( 's' );

  pattern<int> pi;
  pattern<int> npi;
  std::vector<int> vi;
  vi.push_back( max );
  vi.push_back( 1 );
  for( int i = 0; i < max; ++i )
  {
    vi.push_back( i );
    if ( 0 == i % 2 )
    {
      pi.push_back( i );
      npi.push_back( i );
    }
    else
    {
      pi.push_back_one_arbitrary();
    }
  }

  pattern<std::set<int> > ps;
  ps.push_back( std::set<int>() );
  ps.push_back_one_arbitrary();
  std::vector<std::set<int> > vs;
  vs.push_back( std::set<int>() );
  vs.push_back( std::set<int>() );

  if ( 0 == ps.index_of( vs ) &&
       pattern<int>::npos == npi.index_of( vi ) &&
       pattern<char>::npos == pc.index_of( v ) &&
       6 == cpc.index_of( v ) )
  {
    your_mark = pi.index_of( vi );
  }
  //*/
  //* 3-as
  pattern<char> pca;
  std::string salts = "C++ is cool";
  std::vector<char> alts( salts.begin(), salts.end() );
  pca.push_back( alts );
  pca.push_back( 'o' );

  pattern<char> a;
  a.push_back( alts );
  a.push_back( '!' );

  pattern<char> b;
  b.push_back( alts );
  b.push_back_one_arbitrary();
  b.push_back( 'i' );

  pattern<int> api;
  api.push_back( vi );
  api.push_back( 0 );

  if ( 1 == api.index_of( vi ) &&
       pattern<char>::npos == a.index_of( v ) &&
       pattern<char>::npos == b.index_of( v ) &&
       2 == b.index_of( alts ) )
  {
    your_mark = pca.index_of( v );
  }
  //*/
  //* 4-es
  std::list<int> d;
  d.push_back( max / 2 );

  pattern<char> nc;
  nc.push_back( 'e' );
  nc.push_back_many_arbitraries();
  nc.push_back( 'H' );

  pattern<char> fc;
  fc.push_back( 'o' );
  fc.push_back_many_arbitraries();
  fc.push_back( 'o' );

  pattern<char> pmc = cpc;
  pmc.push_back_many_arbitraries();
  pmc.push_back( 'd' );

  pattern<int> pmi;
  pmi.push_back( 0 );
  pmi.push_back_many_arbitraries();
  pmi.push_back( max / 3 );
  pmi.push_back_many_arbitraries();
  pmi.push_back( max / 2 );

  std::string::iterator mitp = pmc.find( msg.begin(), msg.end() );
  std::string::iterator mitn = nc.find( msg.begin(), msg.end() );
  std::list<int>::iterator lit = pmi.find( d.begin(), d.end() );
  if ( 2 == pmi.index_of( vi ) &&
       mitp != msg.end() &&
       'W' == *mitp &&
       d.end() == lit &&
       mitn == msg.end() )
  {
    your_mark = fc.index_of( v );
  }
  //*/
  //* 5-os
  pattern<char, case_insensitive> ins;
  ins.push_back( 'L' );
  ins.push_back( 'O' );
  ins.push_back_many_arbitraries();
  ins.push_back( alts );
  const pattern<char, case_insensitive> cins = ins;
  ins.push_back( '!' );

  pattern<char, case_insensitive> f;
  f.push_back( 'S' );
  f.push_back_one_arbitrary();
  f.push_back( 'C' );

  if ( v.end() == ins.find( v.begin(), v.end() ) &&
       3 == cins.index_of( v ) )
  {
    your_mark = f.index_of( alts );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
