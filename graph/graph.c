#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

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
  int i, j;
  
  if (rep == MATRIX) {
    g->rep = MATRIX;
    g->matrix = malloc(sizeof(float[n][n]));
    
    for(i = 0; i < n; i++)
      for(j = 0; j < n; j++)
	g->matrix[i][j] = INFINITY;
  }
  else {
    g->list = malloc(sizeof(SIdict[n]));

    for(i = 0; i < n; i++)
      g->list[i] = makeSIdict();
    
    g->rep = LIST;
  }

  return g;
}

Graph cloneGraph(Graph G, int rep) {
  Graph g = makeGraph(G->n, rep);
  int i, j;  
  
  if (G->rep == rep) {
    if (rep == MATRIX) {
      for (i = 0; i < g->n; i++)
	for (j = 0; j < g->n; j++)
	  g->matrix[i][j] = G->matrix[i][j];
    }
    else {
      //Copy linked list
      return NULL;
    }
  }
  else {
    if (rep == MATRIX) {
      //Convert Linked list to matrix
      return NULL;
    }
    else {
      //Convert Matrix to linked list
      return NULL;
    }
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
      if (G->matrix[source][target] == INFINITY)
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
      if (G->matrix[source][target] != INFINITY)
	G->matrix[source][target] = INFINITY;
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

int* successors(Graph G, int source) {
  int* targets = malloc(sizeof(int[G->n + 1]));

  int i, numVerts = 0;
  for (i = 0; i < G->n; i++) {
    if (G->matrix[source][i] != INFINITY) {
      targets[numVerts] = i;
      numVerts++;
    }
  }
}

int* predecessors(Graph G int target) {
  int* sources = malloc(sizeof(int[G->n + 1]));

  int i, numVerts = 0;
  for (i = 0; i < G->n; i++) {
    if (G->matrix[i][target] != INFINITY) {
      targets[numVerts] = i;
      numVerts++;
    }
  }
}
