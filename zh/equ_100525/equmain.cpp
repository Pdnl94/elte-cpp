#include <iostream>
#include "equivalence.h"
#include <algorithm>
#include <utility>
#include <string>

class Foo
{
  int i;  
public:
  Foo(int j):i(j) {}
  int get() const
  {
    return i;
  }
};

struct FooLess
{
  bool operator()( const Foo& a , 
                   const Foo& b )
  {
    return a.get() < b.get();
  }		   
};

const int max = 5;

int main()
{
  int yourMark = 1;
  //* 2-es
  Equivalence<double, int> t;
  t.add_representative(3.5);
  t.insert(3.5, 2);
  
  Equivalence<int, std::string> marks;
  for(int i = 1; i <= max; ++i)
  {
    marks.add_representative( i );
  }
  marks.insert( 2, "Java" );
  marks.insert( "Java", "C++" );
  marks.insert( 3, "Analizis" );
  
  const Equivalence<int, std::string> cmarks = marks;
  if ( cmarks.count("Analizis") == cmarks.count(3) )
  {
    yourMark = cmarks.get_representative( "C++" );    
  }
  //*/
  //* 3-as
  marks.erase( "Java" );
  marks.erase_representative( 3 );
  if (3 == cmarks.size() && 1 == marks.size())
  {
    yourMark = cmarks.get_representative( "Analizis" );
  }
  //*/
  //* 4-es
  Equivalence<std::string, std::string> phones;
  phones.add_representative( "Aniko" );
  phones.add_representative( "Bela" );
  phones.insert( "Aniko", "+36(70)555-6789" );
  phones.insert( "Aniko", "+36(30)555-9876" );  
  phones.insert( "Bela", "+36(20)666-1234" );
  phones.insert( "+36(20)666-1234", "+36(30)555-8888" );  
  phones.insert( "+36(30)555-8888", "+36(70)555-0000" );

  if ( 5 == phones.size() && 
       3 == phones.count( "+36(30)555-9876" ) )
  {
    yourMark = phones.get_representative("+36(70)555-0000").length();
  } 
  //*/
  //* 5-os
  Equivalence<Foo, int, FooLess> foos;
  foos.add_representative( Foo(3) );
  foos.add_representative( Foo(5) );
  foos.insert( Foo(3), 2 );
  foos.insert( Foo(5), 4 );
  if (2 == foos.size())
  {
    yourMark = foos.get_representative( 4 ).get();
  }  
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
