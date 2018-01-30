#include "safevect.h"
#include <algorithm>
#include <numeric>
#include "safevect.h"
#include <iostream>
#include <string>
#include <list>

class Test
{
};

class limited
{

  static int cnt;
  int x;

public:
  limited( int i = 0 ):x(i)
  {
    ++cnt;
  }

  limited& operator=( const limited& rhs )
  {
    ++cnt;
    x = rhs.x;
    return *this;
  }

  limited( const limited& rhs ): x ( rhs.x )
  {
    ++cnt;
  }

  int get() const
  {
    return x;
  }

  static int get_cnt()
  {
    return cnt;
  }
};

int limited::cnt = 0;

const int max = 1000;
const int out = -1;

int main()
{
  int yourMark = 1;
  //* 2-es
  safe_vector<Test> test;
  test.at( 3 ) = Test();

  safe_vector<int> ti;
  for( int i = 0; i < max; ++i )
  {
    ti.at( i ) = i;
  }
  ti.pop_back();
  const safe_vector<int> cti = ti;

  safe_vector<limited> lim;
  lim.at( 1 ) = limited( 4 );

  safe_vector<int> vi( 1 );
  vi.at( 3 ) = 0;

  if ( limited::get_cnt() < 16 && max - 1 == cti.size() && max / 2 == ti.at( max / 2 ) )
  {
    if ( 4 == vi.size() && 0 == vi.at( 3 ) && 1 == vi.at( 0 ) && 1 == vi.at( 1 ) )
    {
      yourMark = lim.size();
    }
  }
  //*/
  //* 3-as
  const safe_vector<int> cvi = vi;

  safe_vector<int> sv( 1, out );
  sv[ 3 ] = 2;
  const safe_vector<int> csv = sv;

  if ( cvi[ max ] == 0 && csv.at( max ) == out && 2 == csv[ 3 ] )
  {
    yourMark = csv.size() + csv[ 4 ];
  }
  //*/
  //* 4-es
  safe_vector<int> a( 1 );
  a[ 2 ] = 2;
  ++sv[ 3 ];
  safe_vector<int>::iterator it = std::find( sv.begin(), sv.end(), 3 );
  if ( it != sv.end() )
  {
    yourMark = std::accumulate( a.begin(), a.end(), 0 );
  }
  //*/
  //* 5-os
  std::string msg = "Hello";
  safe_vector<char> hello( ' ' );
  hello.insert( 3, msg.begin(), msg.end() );

  std::list<int> li;
  li.push_back( 8 );
  li.push_back( 5 );
  safe_vector<int> lv;
  lv[ 1 ] = 1;
  lv.insert( 0, li.begin(), li.end() );

  if ( 8 == hello.size() && ' ' == hello[2] && 2 == lv.size() )
  {
    yourMark = lv[ 1 ];
  }
  //*/
  std::cout << "Your mark is "
            << yourMark;
  std::endl( std::cout );
}
