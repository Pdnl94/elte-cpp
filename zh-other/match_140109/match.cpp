#include <iostream>
#include "pattern.h"
#include <vector>
#include <string>
#include <complex>
#include <cctype>
#include <list>
#include "pattern.h"

struct case_insensitive
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
  pattern<char> regex;
  regex.push_back( 'e' );
  regex.push_back_one_arbitrary();
  regex.push_back_one_arbitrary();
  regex.push_back( 'o' );

  std::string msg = "Hello World";
  std::vector<char> vm( msg.begin(), msg.end() );
  const pattern<char> cregex = regex;

  std::vector<int> n;
  pattern<int> t;
  std::vector<int> vi;
  vi.push_back( 3 );
  vi.push_back( 7 );
  for( int i = 0; i < max; ++i )
  {
    vi.push_back( i );
    n.push_back ( 2 * i );
    if ( i % 2 == 0 )
    {
      t.push_back_one_arbitrary();
    }
    else
    {
      t.push_back( i );
    }
  }

  pattern<std::complex<int> > cp;
  cp.push_back( std::complex<int>( 2, 2 ) );
  cp.push_back_one_arbitrary();

  std::vector<std::complex<int> > v;
  v.push_back( std::complex<int>( 2, 2 ) );
  v.push_back( std::complex<int>() );

  if ( 1 == cregex.index_of( vm ) &&
       pattern<int>::npos == t.index_of( n ) && 
       0 == cp.index_of( v ) )
  {
    your_mark = t.index_of( vi );
  }
  //*/
  //* 3-as
  pattern<int> a;
  a.push_back( max / 4 );
  a.push_back_many_arbitraries();
  a.push_back( max / 3 );
  a.push_back( 1 + max / 3 );

  pattern<int> b = a;
  b.push_back( max / 2 );

  pattern<int> s;
  s.push_back( 1 );
  s.push_back_many_arbitraries();
  s.push_back( max / 2 );

  pattern<char> r;
  r.push_back( 'e' );
  r.push_back_many_arbitraries();
  r.push_back( 'r' );

  pattern<char> h;
  h.push_back( 'H' );
  h.push_back_many_arbitraries();

  pattern<char> hh = h;
  hh.push_back( 'l' );
  hh.push_back( 'd' );

  if ( 2 + max / 4 == a.index_of( vi ) &&
       pattern<int>::npos == b.index_of( vi ) &&
       0 == h.index_of( vm ) &&
       0 == hh.index_of( vm ) &&
       1 == r.index_of( vm ) )
  {
    your_mark = s.index_of( vi );
  }
  //*/
  //* 4-es
  std::string name = "Bjarne Stroupstrup";
  std::list<char> ln( name.begin(), name.end() );
  std::list<char>::iterator it = r.find( ln.begin(), ln.end() );
  pattern<char> nr;
  nr.push_back( 'j' );
  nr.push_back_one_arbitrary();
  nr.push_back_many_arbitraries();
  nr.push_back( 'e' );
  nr.push_back_many_arbitraries();
  nr.push_back( 'o' );
  nr.push_back_many_arbitraries();
  nr.push_back( 'u' );
  std::string::iterator sit = nr.find( name.begin(), name.end() );
  std::list<char>::iterator cit = cregex.find( ln.begin(), ln.end() );
  pattern<char> m;
  m.push_back( 'n' );
  std::string::iterator nit = m.find( name.begin(), name.end() );

  if ( it != ln.end() && 'e' == *it && 
       sit != name.end() && 'j' == *sit &&
       cit == ln.end() && nit != name.end() )
  {
    your_mark = nit - name.begin();
  }
  //*/
  //* 5-os
  pattern<char, case_insensitive> ir;
  ir.push_back( 'E' );
  ir.push_back_many_arbitraries();
  ir.push_back( 's' );
  ir.push_back( 't' );
  ir.push_back_many_arbitraries();
  ir.push_back( 'p' );

  nit = ir.find( name.begin(), name.end() );
  if ( nit != name.end() )
  {
    your_mark = nit - name.begin();
  }
  //*/
  std::cout << "Your mark is "
            << your_mark;
  std::endl( std::cout );
}
