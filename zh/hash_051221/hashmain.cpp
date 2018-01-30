#include "hashtable.h"
#include <iostream>

template <class T>
class Func {
  const int n;
public:
  Func(int i): n(i) { }
  int operator()(const T& x) const { return x%n; }
};

int main() {
  int yourMark = 1;

  //* 2-es
  const unsigned int buckets = 47;
  HashTable<int, Func<int> > hti(buckets);
  hti.insert(82);
  hti.insert(59);
  hti.insert(12);
  const HashTable<int, Func<int> > chti=hti;
  yourMark = chti.size(12);  
  //*/

  //* 3-as
  if (!chti.has(44) && hti.has(59))
    yourMark = chti.size();
  //*/

  //* 4-es
  hti.erase(59);
  yourMark+=hti.size(12);
  //*/ 

  //* 5-os
  HashTable<int, Func2<int> > ht2(buckets);
  ht2.insert(12);
  if (ht2.size(12)==hti.size(12)) 
     std::cout << "Use another hashing function!" << std::endl;
  else 
    ++yourMark;
  //*/
  std::cout << "Your mark is " << yourMark << std::endl;

  return 0;
}
