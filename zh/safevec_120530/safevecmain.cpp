#include "safevec.h"
#include <iostream>
#include <string>
#include "safevec.h"
#include <algorithm>

struct Count
{
  int cnt;
  char ch;

  Count( char c ): cnt( 0 ), ch( c ) { }

  void operator()( const std::string& str )
  {
    cnt += std::count( str.begin(), str.end(), ch );
  }
};

const int max = 1024;
const int fill = -1;

int main()
{
  int yourMark = 1;
  //* 2-es
  safe_vector<int> vi;
  vi.at( 1, fill ) = 12;
  safe_vector<std::string> vstr;
  vstr.at( 2, "" ) =  "C++";
  const safe_vector<int> cvi = vi;

  for( int i = 2; i < max; ++i )
  {
    vi.at( i, fill )++;
  }
  if ( fill == cvi.front() &&
       12 == vi.at( 1, fill ) &&
       vi.size() == max &&
       vstr.at( 0, "A" ) == vstr.at( 1, "B" ) )
  {
    yourMark = cvi.size();
  }
  //*/
  //* 3-as
  vstr.front() = "C++";
  vstr[ 1 ] = "C";
  for( int i = 0; i < max / 2; ++i )
  {
    vi.pop_back();
  }
  if ( max / 2 == vi.size() )
  {
    vi[ max ] = fill;
    if ( max + 1 == vi.size() &&
         vstr.at( 1, "" ) == "C" &&
         vstr[ 0 ] == vstr[ 2 ] &&
         0 == vi[ max - 1 ] )
    {
      yourMark = vstr[ 0 ].length();
    }
  }
  //*/
  //* 4-es
  safe_vector<int>::iterator it =
    std::find( vi.begin(), vi.end(), 12 );
  if ( it != vi.end() )
  {
    yourMark = std::for_each( vstr.begin(), vstr.end(), Count( '+' ) ).cnt;
  }
  //*/
  //* 5-os
  safe_vector<bool> vb;
  vb.at( 4, true ) = false;
  if ( sizeof( vb ) != sizeof( vstr ) && vb[ 1 ] )
  {
    yourMark = vb.size();
  }
  //*/
  std::cout << "Your mark is "
            << yourMark << std::endl;
}
