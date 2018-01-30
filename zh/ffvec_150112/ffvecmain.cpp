#include <iostream>
#include <set>
#include "ffvec.h"
#include <string>
#include "ffvec.h"
#include <functional>
#include <list>

struct ModPred : std::binary_function<int, int, bool>
{

  bool operator()( int x, int y ) const
  {
    return x % 3 == y % 3;
  }

};

const int max = 1200;

int main()
{
  int your_mark = 1;
  //* 2-es
  full_fledged_vector<std::string> vs;
  vs.push_back( "Hello" );
  vs.push_back( "World" );
  const full_fledged_vector<std::string> cvs = vs;

  full_fledged_vector<int> nf;
  nf.push_back( 404 );

  full_fledged_vector<int> vi;
  vi.push_back( 0 );
  vi.push_back( 1 );
  vi.push_back( 2 );
  vi.push_back( 5 );
  full_fledged_vector<int> ft;
  for( int i = 0; i < max; ++i )
  {
    ft.push_back( i % 3 );
  }
  ft.push_back( 5 );

  full_fledged_vector<int> f;
  f.push_back( 1 );
  f.push_back( 2 );
  f.push_back( 0 );

  if ( 5 == cvs.at( 0 ).length() &&
       2 == vi.at( 2 ) &&
       1 == ft.find( f ) &&
       full_fledged_vector<int>::npos == vi.find( nf ) &&
       max - 3 == ft.find( vi ) &&
       max + 1 == ft.size() &&
       full_fledged_vector<int>::npos == vi.find( ft ) &&
       0 == cvs.find( vs ) )
  {
    your_mark = cvs.size();
  }
  //*/
  //* 3-as
  if ( &full_fledged_vector<int>::pop_back != &std::vector<int>::pop_back ||
       &full_fledged_vector<int>::size != &std::vector<int>::size )
  {
    std::cerr << "Use inheritance";
  }
  else
  {
    const int ia[] = { 5, 3, 2 };
    const std::string sa[] = { "!" };
    vs.append( sa, sizeof( sa ) / sizeof( sa[ 0 ] ) );
    vi.append( ia, sizeof( ia ) / sizeof( ia[ 0 ] ) );
    ft.append( ia, sizeof( ia ) / sizeof( ia[ 0 ] ) );

    ft.replace( ft.begin(), ft.begin() + 1, f );

    if ( max + 6 == ft.size() &&
         your_mark == vi.back() &&
         f[ 0 ] == ft[ 0 ] &&
         f[ 1 ] == ft[ 1 ] &&
         1 == vs.back().length() )
    {
      your_mark = vs.size();
    }
  }
  //*/
  //* 4-es
  int arr[ max ];
  ft.copy( arr, max, 6 );

  std::string ta[ 2 ];
  cvs.copy( ta, cvs.size(), 0 );

  full_fledged_vector<int> ff;
  ff.push_back( 302 );

  full_fledged_vector<int> fvi;
  fvi.push_back( 8 );
  fvi.push_back( 0 );

  if ( 0 == nf.find( ff, ModPred() ) &&
       2 == vi.find( ff, ModPred() ) &&
       "Hello" == ta[ 0 ] &&
       1 == arr[ 0 ] &&
       5 == arr[ max - 3 ] )
  {
    your_mark = vi.find( fvi, ModPred() );
  }
  //*/
  //* 5-os
  ff += nf;
  vs += cvs;

  std::list<int> c;
  c.push_front( 3 );
  ft.replace( ft.end() - 2, ft.end(), c.begin(), c.end() );

  std::set<int> s;
  s.insert( 8 );
  ft.replace( ft.begin(), ft.begin() + max / 2, s.begin(), s.end() );

  if ( 2 == ff.size() &&
       8 == ft[ 0 ] &&
       max / 2 + 6 == ft.size() &&
       3 == ft.back() &&
       404 == ff[ 1 ] &&
       vs[ 4 ] == vs[ 1 ] )
  {
    your_mark = vs.size();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
