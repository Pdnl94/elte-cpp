#include <iostream>
#include <vector>
#include "assocvec.h"
#include <string>
#include <functional>
#include <algorithm>
#include "assocvec.h"

struct string_size_less: std::binary_function<std::string, std::string, bool>
{

  bool operator()( const std::string& a, const std::string& b ) const
  {
    return a.size() < b.size();
  }

};

const int max = 1024;

int main()
{
  int your_mark = 1;
  //* 2-es
  std::vector<int> m;
  m.reserve( max );
  for( int i = 0; i < max; ++i )
  {
    m.push_back( i );
  }
  associate_vector_view<int, int> ami( m );
  ami.associate( 0, max / 2 );

  std::vector<int> vi;
  vi.push_back( 7 );
  vi.push_back( 1 );
  vi.push_back( 3 );
  vi.push_back( 8 );

  associate_vector_view<std::string, int> avs( vi );
  avs.associate( "Eight", 8 );
  avs.associate( "One", 1 );
  avs.associate( "Seven", 7 );

  std::vector<std::string> langs;
  langs.push_back( "JavaScript" );
  langs.push_back( "Python" );
  langs.push_back( "C++" );

  associate_vector_view<int, std::string> avi( langs );
  avi.associate( 1, "Python" );
  avi.associate( 5, "C++" );

  if ( &avs.get( "One" ) == &vi[ 1 ] && "C++" == avi.get( 5 ) &&
       max / 2 == ami.get( 0 ) && &avi.get( 1 ) == &langs[ 1 ] )
  {
    your_mark = avs.get( "Eight" ) + avs.get( "One" ) - avs.get( "Seven" );
  }
  //*/
  //* 3-as
  avs[ "Nine" ] = 9;
  avs[ "Ten" ] = 10;
  avs.erase( "Five" );

  ami.erase( 0 );
  ami.erase( max );
  ami[ 0 ] = -1;

  avi[ 0 ] = "Cobol";
  avi.erase( 1 );

  if ( 0 == std::count( langs.begin(), langs.end(), "Python" ) &&
       9 == avs.get( "Nine" ) && 10 == avs[ "Ten" ] &&
       6 == vi.size() && 1U * max == m.size() && -1 == ami[ 0 ] )
  {
    your_mark = langs.size();
  }
  //*/
  //* 4-es
  std::vector<int> al;
  associate_vector_view<std::string, int, string_size_less> alv( al );

  alv[ "C" ] = 2;
  alv[ "C++" ] = your_mark;
  alv[ "Go" ] = 2;
  alv[ "Brainfuck" ] = max;
  alv.erase( "C#" );
  ++alv[ "SQL" ];
  std::vector<int>::iterator it  = alv.find( "Ada" );
  std::vector<int>::iterator eit = alv.find( "Java" );
  std::vector<std::string>::iterator sit = avi.find( 0 );

  if ( max == alv[ "Smalltalk" ] && 3 == al.size() &&
       1 == std::count( al.begin(), al.end(), 2 ) &&
       eit == al.end() && it != al.end() && 5 == sit->size() )
  {
    your_mark = *it;
  }
  //*/
  //* 5-os
  avi.update_key( 0, 1 );
  alv.update_key( "C", "Fortran" );
  std::map<std::string, int, std::greater<std::string> > mal = alv;

  std::map<std::string, int> mvs = avs;

  if ( 1 == mvs.count( "Eight" ) && 10 == mvs[ "Ten" ] &&
       2 == alv[ "Haskell" ] && 0 == mal.count( "C" ) &&
       max == mal[ "Brainfuck" ] && "Cobol" == avi[ 1 ] )
  {
    your_mark = mal.count( "Fortran" ) + mal[ "C++" ];
  }
  //*/
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}