#include <iostream>
#include "drseq.h"
#include <list>
#include <set>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

const int max = 1200;

int main()
{
  int yourMark = 1;
  //* 2-es
  DirectionReversibleSequence<char> h;
  h.push_back('H').push_back('e').push_back('l').push_back('l').push_back('o');
  h.reverse_direction();
  h.push_front('W').push_front('o').push_front('r').push_front('l').push_front('d');

  DirectionReversibleSequence<std::string> strseq;
  strseq.push_front("Hello").push_back("World");  

  const DirectionReversibleSequence<char> ch = h;
  
  h.reverse_direction();
  
  DirectionReversibleSequence<int> di;
  for( int i = 0; i < max; ++i)
  {
    di.push_back(i);
    di.reverse_direction();
  }  
  
  if ( h.at(0) != ch.at(0) && 
       h.at(2) == h.at(3) && 
       h.at(5) == 'W' &&
       strseq.at(1) == "World" )
  {
    yourMark += ( di.at(0)-di.at(max-1) );
  }       
  
  //*/
  //* 3-as
  strseq.reverse_direction();
  strseq.pop_front();
  di.pop_back();
  di.reverse_direction();
  di.pop_back();
  di[0] += 4;

  if ('r' == ch[2] && 
      max == di[0] && 
      strseq[0][0] == ch[9] &&
      1 == strseq.size() )
  {
    yourMark = di[max/2];
  }
  //*/
  //* 4-es
  DirectionReversibleSequence<int, std::vector<int> > vi;
  DirectionReversibleSequence<char, std::deque<char> > dc;
  DirectionReversibleSequence<double, std::list<double> > ld;
  
  vi.push_back(3).push_back(9);
  vi.push_front(8);
  vi.reverse_direction();
  vi.push_back(5);
  vi.pop_front();
  vi[1] = 7;
  
  dc.push_back('H').push_back('e').push_back('l');
  dc.reverse_direction();
  dc.push_front('l').push_front('o').push_front('!');
  dc.pop_back();
  dc.pop_front();
  
  ld.push_front(7.5).push_front(2.3);
  ld.push_back(1.1).push_back(3.8).push_back(4.9);
  ld.pop_back();
  ld.reverse_direction();
  ld.pop_front();
  ld[0] = 6.3;

  if ( 'e' == dc[3] && 
       ld[1] > 3.2 && 
        ld[0] < ld[1] && 
	vi[0] == 3 )
  {
    yourMark = dc.size();
  }
  //*/
  //* 5-os
  std::list<int> l;
  l.push_back(3);
  l.push_back(2);
  l.push_back(8);
  
  std::set<std::string> s;
  s.insert("Hello");
  s.insert("World");
  
  const DirectionReversibleSequence<int> fli(l.begin(), l.end());
  const DirectionReversibleSequence<std::string, std::vector<std::string> > fss(s.begin(), s.end());

  if (fli[2] == 8 && fss[1] == "World")
  {
    yourMark = fli[0] + fss.size();
  }
  //*/
  std::cout << "Your mark is " << yourMark;
  std::endl( std::cout );
}
