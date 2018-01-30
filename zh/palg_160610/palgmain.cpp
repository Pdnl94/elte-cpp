#include <iostream>
#include "palalg.h"
#include <deque>
#include <list>
#include <iterator>
#include <vector>
#include <algorithm>
#include "palalg.h"
#include <cctype>
#include <string>

struct cont: std::list<double>
{

  const double& operator()( int idx ) const
  {
    std::list<double>::const_iterator i = begin();
    std::advance( i, idx );
    return *i;
  }

};

const int max = 1000;

struct too_many_copies
{
};

struct limited
{

  static int copies;

  limited() { }


  limited( const limited& rhs )
  {
    copy( rhs );
  }

  limited& operator=( const limited& rhs )
  {
    copy( rhs );
    return *this;
  }

private:

  void copy( const limited& )
  {
    ++copies;
    if ( copies > max * 1.2 )
    {
      throw too_many_copies();
    }
  }

};

bool operator==( const limited&, const limited& )
{
  return true;
}

int limited::copies = 0;

struct case_insensitive: std::binary_function<char, char, bool>
{

  bool operator()( char a, char b ) const
  {
    return std::tolower( a ) == std::tolower( b );
  }

};


int main()
{
  int your_mark = 1;
  //* 2-es
  std::deque<limited> d;
  for( int i = 0; i < max; ++i )
  {
    d.push_back( limited() );
  }

  std::string s = ":)";
  if ( !is_palindrome( s.begin(), s.end() ) )
  {
    make_palindrome( s.begin(), s.end() );
  }

  cont c;
  c.push_back( 3.7 );
  c.push_back( 1.9 );
  c.push_back( 6.5 );
  if ( !is_palindrome( c.begin(), c.end() ) )
  {
    make_palindrome( c.begin(), c.end() );
  }
  if ( "::" == s && is_palindrome( s.begin(), s.end() ) &&
       is_palindrome( d.begin(), d.end() ) &&
       is_palindrome( c.begin(), c.end() ) && c( 2 ) < 4.8 )
  {
    limited::copies -= max;
    make_palindrome( d.begin(), d.end() );
    your_mark = s.size();
  }
  //*/
  //* 3-as
  const bool duplication = true;
  s = "tekerek icip";
  std::string ps;
  copy_palindrome( s.begin(), s.end(), std::back_inserter( ps ), !duplication );

  c.back() = 6.5;
  std::vector<double> v( 6 );
  copy_palindrome( c.begin(), c.end(), v.begin(), duplication );

  if ( is_palindrome( ps.begin(), ps.end() ) && 23 == ps.size() &&
       3.5 < v[ 0 ] && 6.1 < v[ 3 ] && 3.8 > v[ 5 ] && 't' == ps[ 22 ] )
  {
    your_mark =
      std::count( ps.begin(), ps.end(), 'i' ) - std::count( ps.begin(), ps.end(), 'p' );
  }
  //*/
  //* 4-es
  std::string sa = "Ada";
  ps[ 0 ] = 'T';

  if ( !is_palindrome( ps.begin(), ps.end() ) &&
       is_palindrome( sa.begin(), sa.end(), case_insensitive() ) )
  {
    your_mark += is_palindrome( ps.begin(), ps.end(), case_insensitive() );
  }
  //*/
  //* 5-os
  std::string x = "xazax";
  shift_palindrome( x.begin(), x.end() );
  shift_palindrome( v.begin(), v.end() );

  if ( "zxaxz" == x && 5.9 < v[ 0 ] && 3.9 > v[ 2 ] + v[ 3 ] && 3.8 > v[ 4 ] )
  {
    your_mark += is_palindrome( v.begin(), v.end() );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
