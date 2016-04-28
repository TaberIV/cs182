#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "graph.c"
#include "minprio.c"
#include "graphio.c"
#include "dijkstra.c"

void testDij(char* path) {
  GraphInfo gi; 
  printf("Testing %s \n", path); 
  /* load and print the graph */
  gi = readGraphMakeSymm(path, LIST);
  writeGraph(gi);
  /* compute the MST and print that */
  Graph orig = gi->graph;
  shortestPaths(gi, 0);
}

int main() {
  printf("Testing Dijistrats\n");

  testDij("sixMST.txt");
}
