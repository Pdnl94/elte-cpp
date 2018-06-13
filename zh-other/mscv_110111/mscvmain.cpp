#include <iostream>
#include <string>
#include <algorithm>
#include "cachevec.h"

class Limited
{
  int v;
public:
  static int cnt;  
  Limited( const int& i): v ( i ) {}
  int get() const
  {
    return v;
  }
};

int Limited::cnt = 0;

bool operator==( const Limited& l, const Limited& r )
{
  ++Limited::cnt;
  return l.get() == r.get();  
}

const int max   = 1000;
const int csize = 3;

int main()
{
  int yourMark = 1;
  //* 2-es
  CachedVector<std::string, csize> svec;
  svec.push_back( "Hello" );
  svec.push_back( "World" );
  const CachedVector<std::string, csize> csvec = svec;

  CachedVector<Limited, csize> limvec;
  CachedVector<int, csize> vec;
  for( int i = 0; i < max; ++i )
  {
    limvec.push_back( i );
    vec.push_back( max - i );
  }

  int idx = limvec.index_of( max / 2 );
  int cnt = 0;
  if ( idx == max / 2 )
  {
    if ( max / 3 == limvec.index_of( max / 3 ) )
    {
      cnt = Limited::cnt;
      if ( idx == limvec.index_of ( max / 2 ) && 
           Limited::cnt - cnt < csize )
      {
        if ( limvec.index_of( max ) == limvec.not_in_vec() )
        {
          limvec.index_of( max - 2 );
          limvec.index_of( max / 5 );
          cnt = Limited::cnt;
          limvec.index_of( max / 2 );
          if ( Limited::cnt - cnt > csize )
          {
            yourMark = csvec.size();
          }
        }        
      }
    }
  }
  //*/
  //* 3-as
  cnt = Limited::cnt;
  idx = limvec.last_index_of( max / 2 );
  svec.push_back( "Hello" );
  if ( idx == max / 2)
  {
    if ( svec.last_index_of( "Hello" ) != svec.index_of( "Hello" ) &&
         csvec[0] == "Hello" )
    {
      yourMark = svec.size();
    }
  }
  //*/
  //* 4-es
  svec[0] = "Hell";
  if ( svec.last_index_of( "Hello") == svec.index_of( "Hello" ) )
  {
    CachedVector<std::string, csize>::const_iterator it = 
      std::find( svec.begin(), svec.end(), "Hell" );
   if ( it != svec.end() )
   {
     yourMark = it->length();
   }
  }
  //*/
  //* 5-os
  CachedVector<std::string, max> v( svec );
  int ind = v.index_of( "Hello" );
  if ( ind != v.not_in_vec() )
  {
    yourMark = v[ind].length();
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}

