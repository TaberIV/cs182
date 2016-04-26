#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "graphAlgs.h"
#include "minprio.h"
#include "minprio.c"

struct vert {
  int num;
  int parent;
  double d;
};
typedef struct vert* Vert;

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


void printQueue(MinPrio qp) {
  int level = -1;
  for (int i = 1; i <= qp->numElts; i++) {
    if (log2(i) == floor(log2(i)))
      level++;
    
    for (int j = 0; j < level; j++)
      printf(" ");
    Vert v = (Vert) (qp->arr[i]->content);
    printf("%d %f %d\n", i/2, v->d, i);
  }
  printf("\n");
}


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

Graph minSpanTree(Graph g) {
  Graph edges = makeGraph(g->numVerts, 0);
  MinPrio Q = makeQueue((Comparator) compVert, g->numVerts);
  Handle hands[g->numVerts];

  Vert v;
  v = makeVert(0, -1, 0);
  hands[0] = enqueue(Q, v);
  for (int i = 1; i < g->numVerts; i++) {
    v = makeVert(i, -1, 100);
    hands[i] = enqueue(Q, v);
  }

  while(nonempty(Q)) {
    printQueue(Q);
    v = dequeueMin(Q);
    decreasedKey(Q, hands[1]);
    printf("v: %d\tpar: %d\twt: %f\n", v->num, v->parent, v->d);
    int* succ = successors(g, v->num);
    Vert u;
    for (int i = 0; succ[i] != -1; i++) {
      u = hands[succ[i]]->content;
      if (u->parent == -1 &&
	  edge(g, v->num, succ[i]) < u->d) {
	u->parent = v->num;
        u->d = edge(g, v->num, succ[i]);
	decreasedKey(Q, hands[succ[i]]);
      }
    }
  }
  
  for (int i = 1; i < g->numVerts; i++) {
    v = hands[i]->content;
    addEdge(edges, v->parent, i, v->d);
    addEdge(edges, i, v->parent, v->d);
  }
  
  return edges;
}
