#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "minprio.c"
#include "graphAlgs.h"

Graph transClose(Graph g) {
  Graph R[g->numVerts + 1];
  R[0] = g;
  for (int k = 1; k < g->numVerts + 1; k++) {
    R[k] = makeGraph(g->numVerts, 1);
    for (int i = 0; i < g->numVerts; i++)
      for (int j = 0; j < g->numVerts; j++) {
	if(!isinf(edge(R[k-1], i, j)) ||
	   (!isinf(edge(R[k-1], i, k - 1)) && !isinf(edge(R[k-1], k - 1, j))))
	  addEdge(R[k], i, j, 0);
      }
  }
  return R[g->numVerts];
}

double compDouble(double d, double z) {
  return d - z;
}

Graph minSpanTree(Graph g) {
  Graph edges = makeGraph(g->numVerts, 1);
  MinPrio V = makeQueue((Comparator) compDouble, g->numVerts);
  Handle* hands[g->numVerts];
  
  double minWeight = INFINITY;
  int src, dest;
  Handle hand;
  for (int v = 1; v < g->numVerts; v++) {
    enqueue(V, INFINITY);
  }

  
  return edges;
}
