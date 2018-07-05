#include <iostream>
#include <functional>
#include <set>
#include "sethelp.h"
#include <string>
#include "sethelp.h"

struct employee
{

  std::string id;
  int salary;

  employee( const std::string& s, int i ): id( s ), salary( i ) { }

};

bool operator==( const employee& lhs, const employee& rhs )
{
  return lhs.id == rhs.id;
}

bool operator<( const employee& lhs, const employee& rhs )
{
  return lhs.salary < rhs.salary;
}

struct string_size_less
{

  bool operator()( const std::string& lhs,
                   const std::string& rhs ) const
  {
    return lhs.size() < rhs.size();
  }

};

const int max = 1000;

int main()
{
  int your_mark = 1;
  //* 2-es
  std::set<int> si;
  for( int i = 0; i < max; ++i )
  {
    si.insert( i );
  }

  std::set<std::string> m;
  m.insert( "Hallo" );
  m.insert( "World" );

  set_helper<std::string> mh( m );
  mh.update( "Hallo", "Hello" );

  set_helper<int> sih( si );
  for( int i = 0; i < max; ++i )
  {
    sih.update( i, max + i );
  }

  if ( 0 == m.count( "Hallo" ) && 1 == si.count( max ) &&
       0 == si.count( max / 2 ) && 2 == m.size() )
  {
    your_mark = m.count( "World" ) + m.count( "Hello" );
  }
  //*/
  //* 3-as
  std::set<employee> emps;
  emps.insert( employee( "jdoe", 1500 ) );
  emps.insert( employee( "dmr", 4600 ) );

  std::set<employee> memps;
  memps.insert( employee( "xy", 1000 ) );

  set_helper<employee> hemps( emps );
  hemps.update( employee( "jdoe", 0 ), employee( "jdoe", 1800 ) );
  set_helper<employee> hs( memps );
  hs.update( employee( "xy", 0 ), employee( "xy", 1200 ) );

  hemps += hs;

  if ( 1 == emps.count( employee( "null", 1800 ) ) &&
       1 == emps.count( employee( "fake", 1200 ) ) )
  {
    your_mark = emps.size();
  }
  //*/
  //* 4-es
  std::set<std::string, string_size_less> langs;
  langs.insert( "C++" );
  langs.insert( "Rust" );
  langs.insert( "D" );
  langs.insert( "Brainfuck" );

  make_set_helper( langs ).update( "Brainfuck", "C" );

  std::set<int, std::greater<int> > sg;
  sg.insert( 0 );
  sg.insert( 1 );

  make_set_helper( sg ) += sih;

  if ( 2 + max == sg.size() && 1 == sg.count( max + 1 ) &&
       0 == langs.count( "Brainfuck" ) && 1 == langs.count( "D" ) )
  {
    your_mark = langs.size() + langs.count( "C++" );
  }
  //*/
  //* 5-os
  std::set<std::string, std::greater<std::string> > scl;
  scl.insert( "Javascript" );
  scl.insert( "Python" );

  set_helper<std::string, string_size_less> sl( langs );
  make_set_helper( scl ) >> sl;

  make_set_helper( sg ) << sih;

  if ( 1U * max == si.size() && scl.empty() && 1 == langs.count( "Erlang" ) &&
       1 == sg.count( 1 ) && 1 == si.count( max + 1 ) )
  {
    your_mark = langs.size();
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
