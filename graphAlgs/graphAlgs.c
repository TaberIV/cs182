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

struct vert {
  int num;
  int parent;
  double d;
};
typedef struct vert* Vert

Vert makeVert(int num, int parent, double d) {
  Vert v = (Vert) malloc(sizeof(struct vert));
  v->num = num;
  v->parent = parent;
  v->d = d;

  return v;
}

double compVert(Vert v, Vert u) {
  return v->d - u->d;
}

Graph minSpanTree(Graph g) {
  Graph edges = makeGraph(g->numVerts, 0);
  MinPrio Q = makeQueue(g->numVerts);
  double link[g->numVerts];
  Handle hands[g->numVerts];

  Vert v;
  for (int i = 0; i < g->numVerts; i++) {
    v = makeVert(i, -1, INFINITY);
    hands[i] = enqueue(Q, v);
  }
  hands[0]->content->d = 0;
  hands[0]->content->parent = 0;
  decreasedKey(hands[0]);
  
  while(nonempty(Q)) {
    v = dequeueMin(Q);
    
    for (int i = 0; succesors(G, v->num)[i] != -1; i++) {
      if (hands[succesors(G, v->num)[i]]->parent == -1 &&
	  edge(g, v->num, succesors(G, v->num)[i]) < hands[succesors(G, v->num)[i]]->d) {
	hands[succesors(G, v->num)[i]]->parent = v->num;
	hands[succesors(G, v->num)[i]]->d = edge(g, v->num, succesors(G, v->num)[i]);
	decreasedKey(hands[succesors(G, v->num)[i]]);
      }
    }
  }

  
  return edges;
}
