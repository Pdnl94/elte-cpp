#include <iostream>
#include <iterator>
#include <numeric>
#include <algorithm>
#include "msetvec.h"
#include <vector>
#include <string>
#include "msetvec.h"

struct string_size_less
{

  bool operator()( const std::string& a,
                   const std::string& b ) const
  {
    return a.size() < b.size();
  }

};

struct employee
{
  std::string name;
  std::string userid;
  int salary;

  employee( const std::string& n, const std::string& u, int s )
    : name( n ), userid( u ), salary( s ) { }
};

struct employee_name_comp
{

  bool operator()( const employee& a, const employee& b ) const
  {
    return a.name < b.name;
  }

};


struct employee_salary_less
{

  bool operator()( const employee& a, const employee& b ) const
  {
    return a.salary < b.salary;
  }

};


struct employee_salary_greater
{

  bool operator()( const employee& a, const employee& b ) const
  {
    return a.salary > b.salary;
  }

};


struct employee_userid_less
{

  bool operator()( const employee& a, const employee& b ) const
  {
    return a.userid < b.userid;
  }

};


const int max = 1024;

int main()
{
  int your_mark = 1;
  //* 2-es
  std::vector<int> v;
  v.reserve( max );
  for( int i = 0; i < max; ++i )
  {
    v.push_back( 0 == i % 2 ? max - i : 2 * i );
  }
  multiset_vector<int, std::greater<int> > m( v );

  std::vector<employee> emps;
  emps.push_back( employee( "John Doe", "john.doe", 600 ) );
  emps.push_back( employee( "John Doe", "doej", 700 ) );
  emps.push_back( employee( "John Doe", "jdoe", 800 ) );
  emps.push_back( employee( "Maximus Dickus", "max", 490 ) );
  emps.push_back( employee( "Jane Doe", "jane.doe", 750 ) );

  const multiset_vector<employee, employee_name_comp> emps_ms( emps );
  const employee c( "John Doe", "", 0 );

  if ( 'M' == emps[ 4 ].name[ 0 ] && 'n' == emps[ 0 ].userid[ 2 ] &&
       3 == emps_ms.count( c ) && 2 * ( max - 1 ) == v[ 0 ] &&
       2  == v[ max - 1 ] && v[ 0 ] != v[ 1 ] )
  {
    your_mark = m.count( 2 );
  }
  //*/
  //* 3-as
  std::vector<int> nv;
  nv.push_back( 5 );
  nv.push_back( 2 );
  nv.push_back( 1 );
  nv.push_back( 7 );
  m.use( nv );


  const employee cm( "Maximus Dickus", "", 0 );
  const employee nf( "Bjarne Stroustrup", "bs", 1000 );
  std::vector<employee>::const_iterator cim = emps_ms.find( cm );
  std::vector<employee>::const_iterator cib = emps_ms.find( nf );
  if ( cib == emps.end() && 'M' == cim->name[ 0 ] )
  {
    your_mark = nv[ 2 ] + nv[ 3 ] + m.count( 6 );
  }
  //*/
  //* 4-es
  std::vector<employee> veu = emps;
  std::vector<employee> ves = emps;
  std::vector<employee> vesg = emps;
  multiset_vector<employee, employee_name_comp> a( veu );
  multiset_vector<employee, employee_name_comp> b( ves );
  multiset_vector<employee, employee_name_comp> s( vesg );
  a.secondary_ordering( employee_userid_less() );
  b.secondary_ordering( employee_salary_less() );
  s.secondary_ordering( employee_salary_greater() );

  if ( veu[ 0 ].name == ves[ 0 ].name && veu[ 4 ].name == vesg[ 4 ].name &&
       800 == vesg[ 1 ].salary && 600 == ves[ 1 ].salary &&
       "doej" == veu[ 1 ].userid && "jdoe" == veu[ 2 ].userid )
  {
    your_mark = a.count( c ) + b.count( cm );
  }
  //*/
  //* 5-os
  const std::vector<employee> ce = emps;

  sorted_iterator<employee, employee_salary_less> its =
    sorted_iterator_begin( ce, employee_salary_less() );
  sorted_iterator<employee, employee_userid_less> itu =
    sorted_iterator_begin( ce, employee_userid_less() );

  sorted_iterator<int, std::less<int> > iti =
    sorted_iterator_begin( v, std::less<int>() );

  int x = std::accumulate( iti,
                           sorted_iterator_end( v, std::less<int>() ),
                           0 );


  if ( 490 == its->salary && &(*its) == &(ce[ 4 ] ) && 700 == itu->salary &&
       x == std::accumulate( v.begin(), v.end(), 0 ) && 2 == *iti )
  {
    sorted_iterator<int, std::less<int> > i =
      std::find( sorted_iterator_begin( nv, std::less<int>() ),
                 sorted_iterator_end( nv, std::less<int>() ),
                 5 );
    your_mark = *i;
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
