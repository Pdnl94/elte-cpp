#include <iostream>
#include "graph.h"

int main()
{
  int yourMark = 1;
  //* 2-es
  Graph<int, false> undir_graph;
  Graph<int, true> dir_graph;
  
  undir_graph.add(3);
  undir_graph.add(7);
  undir_graph.add(6);
  
  undir_graph.add(3, 7);
  undir_graph.add(6, 3);
  
  dir_graph.add(1);
  dir_graph.add(2);
  dir_graph.add(3);
  dir_graph.add(4);
  dir_graph.add(5);
  dir_graph.add(1,3);
  dir_graph.add(3,2);
  dir_graph.add(4,2);
  dir_graph.add(5,1);
  dir_graph.add(5,5);
  dir_graph.add(4,4);
  
  const Graph<int, false> cug = undir_graph;
  
  yourMark += (cug.is_directed() + dir_graph.is_directed());
  //*/
  
  //* 3-as
  undir_graph.remove(3, 6);
  
  if (cug.has(7,3) && 
      !dir_graph.has(3,1))
  {
    yourMark = cug.countNodes(); 
  }
  //*/
  
  //* 4-es
  dir_graph.remove(3);
  yourMark = dir_graph.countEdges();
  //*/
  
  //* 5-os
  Graph<int, false> a;
  Graph<int, false> b;
  a.add(2);
  a.add(4);
  a.add(5);
  a.add(2,4);
  a.add(5,4);
  b.add(2);
  b.add(4);
  b.add(7);
  b.add(6);
  b.add(4,2);
  b.add(7,6);
  Graph<int, false> c = a + b;
  
  Graph<int, true> d;
  d.add(3);
  d.add(5);
  d.add(3,5);
  Graph<int, true> e;
  e.add(7);
  e.add(3);
  e.add(3,7);
  Graph<int, true> f = d + e;

  if (3 == f.countNodes() && 2 == f.countEdges())
    yourMark = c.countNodes();
  //*/
  std::cout << "Your mark is " << yourMark << std::endl;
  return 0;
}
