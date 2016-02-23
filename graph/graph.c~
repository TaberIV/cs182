#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h"
#include "SIdict.c"

//typedef struct graph* Graph;
struct graph {
  float** matrix;
  SIdict* list;
  
  int n;
  int rep;
};

Graph makeGraph(int n, int rep) {
  Graph g = (Graph) malloc(sizeof(struct graph));
  g->n = n;
  
  if (rep == MATRIX) {
    g->matrix = malloc(sizeof(float[n][n]));
    g->rep = MATRIX;
  }
  else {
    g->list = malloc(sizeof(SIdict[n]));

    int i;
    for(i = 0; i < n; i++) {
      g->list[i] = makeSIdict();
    }
    
    g->rep = LIST;
  }

  return g;
}

Graph cloneGraph(Graph G, int rep) {
  Graph g = malloc(sizeof(struct graph));
  
  if(G->rep == rep) {
    g->matrix = NULL;
  }

  return g;
}

void disposeGraph(Graph G) {
  free(G);
}

int numVerts(Graph G) {
  return G->n;
}

int addEdge(Graph G, int source, int target, float w) {
  if (source > G->n && target > G->n) {
    if (G->rep == MATRIX) {
      if (G->matrix[source][target] == 0)
	G->matrix[source][target] = w;
      else
	return ERROR;
    }
    else
      return ERROR;

    return OK;
  }
  else
    return ERROR;
}

int delEdge(Graph G, int source, int target) {
  if (source > G->n && target > G->n) {
    if (G->rep == MATRIX) {
      if (G->matrix[source][target] != 0)
	G->matrix[source][target] = 0;
      else
	return ERROR;
    }
    else
      return ERROR;
    
    return OK;
  }
  else
    return ERROR;
}

float edge(Graph G, int source, int target) {
  if (source > G->n && target > G->n) {
    if (G->rep == MATRIX) {
      return G->matrix[source][target];
    }
    else
      return -2;
  }
  else
    return -1;
}

