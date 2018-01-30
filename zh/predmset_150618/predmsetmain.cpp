#include <string>
#include <iostream>
#include "predmset.h"
#include <set>
#include "predmset.h"

class pair
{
  int id;
  std::string s;

public:

  pair( int i, const std::string& a ): id( i ), s( a ) { }

  int get_id() const
  {
    return id;
  }

  std::string get_value() const
  {
    return s;
  }
};

bool operator<( const pair& rhs, const pair& lhs )
{
  return rhs.get_id() < lhs.get_id();
}

struct pair_string_size
{
  bool operator()( const pair& p ) const
  {
    return 0 == p.get_value().size() % 3;
  }
};

struct int_pred
{
  bool operator()( int a ) const
  {
    return a > 0;
  }
};

class employee
{
  std::string name;
  int salary;

public:

  employee( const std::string& n, int s ): name( n ), salary( s ) { }

  int get_salary() const
  {
    return salary;
  }

  const std::string& get_name() const
  {
    return name;
  }
};

struct employee_comp
{
  bool operator()( const employee& lhs, const employee& rhs ) const
  {
    return lhs.get_name() < rhs.get_name();
  }
};

const int max = 1000;

struct employee_pred
{
  bool operator()( const employee& e ) const
  {
    return max / 2 > e.get_salary();
  }
};

int main()
{
  int your_mark = 1;
  //* 2-es
  predicate_multiset<int, int_pred> a;
  predicate_multiset<pair, pair_string_size> s;
  predicate_multiset<int, int_pred> pmi;
  for( int i = 0; i < max; ++i )
  {
    s.insert( pair( 0, 0 == i % 2 ? "Hello" : std::string( i, 'A' ) ) );
    s.insert( pair( i, 0 == i % 2 ? std::string( i, 'S' ) : "World" ) );
    pmi.insert( i >= max / 2 ? 1 : -1 );
  }
  const predicate_multiset<pair, pair_string_size> cs = s;
  const predicate_multiset<int, int_pred> cpmi = pmi;
  if ( cpmi.count( 1 ) == max / 2 && max + 1 == cs.count( pair( 0, "" ) ) &&
       max - 1 == cs.at( pair( 0, "" ), 0 ).get_value().size() &&
       "Hello" == cs.at( pair( 0, "" ), max ).get_value() &&
       "World" == cs.at( pair( max - 1, "" ), 0 ).get_value() )
  {
    your_mark = cpmi.at( 1, 1 ) + cpmi.at( 1, max / 3 );
  }
  //*/
  //* 3-as
  s.erase( pair( max / 2, "" ) );
  pmi.erase( -1 );
  if ( max == cpmi.size() && 2 * max == cs.size() &&
       max / 2 == pmi.size() && 0 == pmi.count( -1 ) &&
       cs.count( pair( max / 2, "" ) ) != s.count( pair( max / 2, "" ) ) )
  {
    your_mark = cs.at( pair( 3, "" ), 0 ).get_value().length() - your_mark;
  }
  //*/
  //* 4-es
  predicate_multiset<employee, employee_pred, employee_comp> es;
  es.insert( employee( "John Doe", max ) );
  es.insert( employee( "Jane Doe", max / 3 ) );
  es.insert( employee( "John Doe", 1 + max / 2 ) );
  es.insert( employee( "Jane Doe", 3 * max / 4 ) );
  if ( 2 == es.count( employee( "John Doe", 0 ) ) &&
       2 == es.count( employee( "Jane Doe", 0 ) ) &&
       max == es.at( employee( "John Doe", 0 ), 0 ).get_salary() )
  {
    your_mark = es.size();
  }
  //*/
  //* 5-os
  const std::multiset<employee, employee_comp> ms = es;
  const std::multiset<int> t = cpmi;
  if ( t.size() == max && 4 == ms.size() &&
       2 == ms.count( employee( "Jane Doe", 0 ) ) &&
       max / 2 == t.count( -1 ) )
  {
    your_mark += ( t.count( -1 ) / t.count( 1 ) );
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
