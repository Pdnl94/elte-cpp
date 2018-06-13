#include "msetseq.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "msetseq.h"
#include <deque>
#include <functional>

struct StringSizeLess: std::binary_function<std::string, std::string, bool>
{
  bool operator()( const std::string& a, const std::string& b ) const
  {
    return a.size() < b.size();
  }
};

const int max = 1000;

class Limited
{
  int data;
public:
  int get() const
  {
    return data;
  }

  Limited( int i ): data( i ) { }
};

bool operator<( const Limited& a, const Limited& b )
{
  return a.get() < b.get();
}

int main()
{
  int yourMark = 1;
  //* 2-es
  MultisetSortedSeq<int, std::deque<int> > a;
  MultisetSortedSeq<Limited, std::vector<Limited> > b;

  MultisetSortedSeq<std::string, std::vector<std::string> > s;
  s.insert( "Test" );

  MultisetSortedSeq<char, std::deque<char> > m;
  m.insert( 'h' ).insert( 'e' ).insert( 'l' ).insert( 'l' ).insert( 'o' );
  m.insert( 'w' ).insert( 'o' ).insert( 'r' ).insert( 'l' ).insert( 'd' );
  const MultisetSortedSeq<char, std::deque<char> > cm = m;


  if ( sizeof( a ) != sizeof( b ) )
  {
    for( int i = 0; i <= max; ++i )
    {
      a.insert( i );
      b.insert( Limited( max - i ) );
    }
    const MultisetSortedSeq<int, std::deque<int> > ca = a;
    if ( max + 1 == ca.size() && ca.front() == b.front().get() && 
         10 == cm.size() && 'd' == cm.front() )
    {
      yourMark = cm.count( 'o' );
    }
  }
  //*/
  //* 3-as
  m.erase( 'l' );
  m.erase( 'o' );
  m.erase( 'd' );
  if ( 'w' == cm.back() && 'e' == m.front() && 0 == m.count( 'o' ) )
  {
    yourMark = m.size() - s.size();
  }
  //*/
  //* 4-es
  MultisetSortedSeq<int> x;
  for( int i = 0; i <= max; ++i )
  {
    x.insert( 2 * max - i );
  }

  MultisetSortedSeq<char, std::list<char> > h;
  h.insert( 'H' ).insert( 'e' ).insert( 'l' ).insert( 'l' ).insert( 'o' );

  if ( max == x.front() && 'o' == h.back() )
  {
    yourMark = h.size() - h.count( 'e' );
  }
  //*/
  //* 5-os
  MultisetSortedSeq<std::string, std::list<std::string>, StringSizeLess> ms;
  ms.insert( "Hello" ).insert( "Wo" ).insert( "rld" );
  if ( 1 == ms.count( "C++" ) )
  {
    yourMark = ms.back().size();
  }
  //*/
  std::cout << "Your mark is "
            << yourMark;
  std::endl( std::cout );
}
