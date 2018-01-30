#include <iostream>
#include <string>
#include "vcvec.h"
#include "vcvec.h"
#include <vector>

class test
{

  int i;

public:

  test( int s = 3 ): i( s ) { }


  int get() const
  {
    return i;
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  /* 2-es
  version_controlled_vector<int> a;
  a.commit( "Empty initial vector" );
  a.push_back( 8 );
  a.commit( "One element added" );

  a.pop_back();
  a.push_back( 4 );
  a.commit( "Modified element" );

  version_controlled_vector<std::string> s;
  s.push_back( "Hello" );
  s.push_back( "World" );
  s.commit( "Initial vector" );
  s.pop_back();
  s.update( 0 );
  const version_controlled_vector<int> ca = a;

  version_controlled_vector<int> t;
  for( int i = 0; i < max; ++i )
  {
    t.push_back( i );
    t.commit( "Element added" );
    t.commit( "Ignored" );
  }
  t.update( max / 2 - 1 );

  if ( 1 == a.size() &&
       'H' == s[ 0 ][ 0 ] &&
       t.get_commit_message( 0 ) == t.get_commit_message( 1 ) &&
       17 == ca.get_commit_message( 1 ).length() &&
       1 == ca.size() &&
       max / 2 == t.size() &&
       4 == a[ 0 ] )
  {
    your_mark = s.size();
  }
  */
  /* 3-as
  if ( &version_controlled_vector<int>::size != &std::vector<int>::size ||
       &version_controlled_vector<int>::pop_back != &std::vector<int>::pop_back )
  {
    std::cout << "Use inheritance" << std::endl;
  }
  else
  {
    s.revert();
    t.revert();
    t.pop_back();
    t.commit();
    if ( max - 1 == t.size() &&
         2 == s.size() &&
         t.get_commit_message( max ).empty() )
    {
      your_mark += "World" == s[ 1 ];
    }
  }
  */
  /* 4-es
  std::vector<std::string> v = ca.diff( 1, 2 );

  version_controlled_vector<int> p( 3, 1 );
  version_controlled_vector<int> q( 2 );
  version_controlled_vector<test> r( 1 );

  if ( 3 == r[ 0 ].get() &&
       2 == v.size() &&
       2 == q.size() &&
       0 == q[ 1 ] &&
       1 == p[ 1 ] &&
       16 == v[ 1 ].length() )
  {
    your_mark += 'O'  == v[ 0 ][ 0 ];
  }
  */
  /* 5-os
  t.swap( a );
  std::vector<std::string> vt = t.diff( 0, 2 );
  std::vector<std::string> va = a.diff( 0, 3 );

  if ( 0 == ca.get_latest_revision_number( "initial" ) &&
       2 == ca.get_latest_revision_number( "element" ) &&
       max - 1 == a.get_latest_revision_number( "added" ) &&
       4 == t[ 0 ] &&
       vt[ 0 ] != vt[ 1 ] &&
       va[ 0 ] == va[ 1 ] )
  {
    your_mark += 'E' == vt[ 0 ][ 0 ];
  }
  */
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
