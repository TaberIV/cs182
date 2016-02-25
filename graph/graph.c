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
    g->matrix = malloc(n * sizeof(float *));
    
    for(i = 0; i < n; i++) {
      g->matrix[i] = malloc(n * sizeof(float));
      for(j = 0; j < n; j++)
	g->matrix[i][j] = INFINITY;
    }
  }
  else {
        g->rep = LIST;
    g->list = malloc(n * sizeof(SIdict));

    for(i = 0; i < n; i++) {
      g->list[i] = makeSIdict();
    }
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
  if (source < G->n && target < G->n && source >= 0 && target >= 0) {
    if (G->rep == MATRIX) {
      if (G->matrix[source][target] == INFINITY) {
	G->matrix[source][target] = w;
	return OK;
      }
    }
    else
      return ERROR;
  }
  return ERROR;
}

int delEdge(Graph G, int source, int target) {
  if (source < G->n && target < G->n && source >= 0 && target >= 0) {
    if (G->rep == MATRIX) {
      if (G->matrix[source][target] != INFINITY) {
	G->matrix[source][target] = INFINITY;
	return OK;
      }
    }
    else
      return ERROR;
  }

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
  int* targets = malloc((G->n + 1) * sizeof(int));

  if (G->rep == MATRIX) {
    int i, numVerts = 0;
    for (i = 0; i < G->n; i++) {
      if (G->matrix[source][i] != INFINITY) {
	targets[numVerts] = i;
	numVerts++;
      }
    }
    targets[numVerts] = -1;
  }
  else {
    return NULL;
  }

  return targets;
}

int* predecessors(Graph G, int target) {
  int* sources = malloc((G->n + 1) * sizeof(int));

  if (G->rep == MATRIX) {
    int i, numVerts = 0;
    for (i = 0; i < G->n; i++) {
      if (G->matrix[i][target] != INFINITY) {
	sources[numVerts] = i;
	numVerts++;
      }
    }
    sources[numVerts] = -1;
  }
  else {
    return NULL;
  }

  return sources;
}

void printGraph(Graph g) {
  if (g->rep == MATRIX) {
    int i, j;
    for (i = 0; i < g->n; i++) {
      for (j = 0; j < g->n; j++)
	printf("%.3f\t", g->matrix[j][i]);
      printf("\n");
    }
    printf("\n");
  }
}

int main() {
  /*Graph g = makeGraph(5, MATRIX), G;
  
  printf("%d\n", addEdge(g, 0, 3, .7));
  printf("%d\n", addEdge(g, 0, 3, 3));
  printf("%d\n", addEdge(g, 1, 2, 3));
  printf("%d\n", delEdge(g, 1, 2));
  printf("%d\n", delEdge(g, 1, 2));

  G = cloneGraph(g, MATRIX);
  addEdge(G, 0, 1, 15.5);
  disposeGraph(G);
  
  printf("%d\n", numVerts(g));
  printf("%d\n", addEdge(g, 2, 3, 3));
  printf("%d\n", addEdge(g, 4, 2, 8));
  printf("%d\n", addEdge(g, 1, 1, 1));
  printf("%d\n", addEdge(g, 3, 3, 123));
  printf("%d\n", addEdge(g, 4, 4, .01));

  printGraph(g);
  int* p;
  int* s;
  int i, j, index = 3;
  
  p = predecessors(g, index);
  printf("Predecessors: \n");
  for(i = 0; p[i] != -1; ++i) {
    printf("%d\t", p[i]);
  }

  s = successors(g, index);
  printf("\nSuccessors: \n");
  for(i = 0; s[i] != -1; ++i) {
    printf("%d\t", s[i]);
  }
  printf("\n");*/

  Graph g = makeGraph(5, LIST), G;
}
