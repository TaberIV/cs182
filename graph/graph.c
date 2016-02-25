#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "graph.h"

//Define linked list-----------------------------
typedef struct node* Node;
struct node {
  float weight;
  int target;
  Node next;
};

typedef struct si_dict* SIdict;
struct si_dict {
  Node front;
};

Node makeNode(int target, float weight, Node next) {
  Node n = malloc(sizeof(struct node));
  n->target = target;
  n->weight = weight;
  n->next = next;

  return n;
}

SIdict makeSIdict() {
  SIdict d = (SIdict) malloc(sizeof(struct si_dict));
    d->front = NULL;
    return d;
}

int hasTarget(SIdict d, int target) {
  Node current;
  for(current = d->front; current != NULL; current = current->next)
    if (current->target == target)
      return 1;

  return 0;
}
//-----------------------------------------------

//typedef struct graph* Graph;
struct graph {
  float** matrix;
  SIdict* list;
  
  int n;
  int rep;
};

//This algoritm runs at O(n^2) time where n is the number vertecies
//for matrix graphs, and O(n) for list graphs. This is because the
//matrix graphs have a nested second nested loop and the list ones do not.
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


//This function runs at O(n^2) because every case involves two loops, one
//nested in the other and both loop through all n verticies.
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
      Node current1, current2;
      for (i = 0; i < g->n; i++) {
	current1 = G->list[i]->front;
	while (current1 != NULL) {
	  current2 = g->list[i]->front;
	  g->list[i]->front = makeNode(current1->target, current1->weight, current2);
	  current1 = current1->next;
	}
      }
	
    }
  }
  else {
    if (rep == MATRIX) {
      Node current;
      for (i = 0; i < g->n; i++) {
	current = G->list[i]->front;
	while (current != NULL) {
	  g->matrix[i][current->target] = current->weight;
	  current = current->next;
	}
      }
    }
    else {
      Node current;
      for (i = 0; i < g->n; i++)
	for (j = 0; j < g->n; j++) {
	  current = g->list[i]->front;
	  if (G->matrix[i][j] != INFINITY)
	    g->list[i]->front = makeNode(j, G->matrix[i][j], current);
	}
    }
  }

  return g;
}

//O(1), there's literally one thing
void disposeGraph(Graph G) {
  free(G);
}

//O(1), just one command
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
    else {
      if (!hasTarget(G->list[source], target)) {
	Node current = G->list[source]->front;
	G->list[source]->front = makeNode(target, w, current);
	return OK;
      }
    }
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
    else {
      Node current, previous = NULL;
      for(current = G->list[source]->front; current != NULL; current = current->next) {
	if (current->target == target) {
	  if (previous == NULL)
	    G->list[source]->front = G->list[source]->front->next;
	  else
	    previous->next = current->next;
	  
	  return OK;
	}
      }
    }
  }

  return ERROR;
}

//This function runs at O(1) for matricies because it can directly
//access whatever data it is looking for, while for linked lists
//It runs at O(n) (worst case) where n is the number of verticies
//the source has edges to for lists because it has to search through
//the whole list to find the right edge.
float edge(Graph G, int source, int target) {
  if (source < G->n && target < G->n && source >= 0 && target >= 0) {
    if (G->rep == MATRIX) {
      return G->matrix[source][target];
    }
    else {
      Node current;
      for(current = G->list[source]->front; current != NULL; current = current->next)
	if (current->target == target)
	  return current->weight;
      return INFINITY;
    }
  }

  return -1;
}

//This function runs at O(n) for both data structures
int* successors(Graph G, int source) {
  int* targets = malloc((G->n + 1) * sizeof(int));
  int numVerts = 0;

  if (G->rep == MATRIX) {
    int i;
    for (i = 0; i < G->n; i++) {
      if (G->matrix[source][i] != INFINITY) {
	targets[numVerts] = i;
	numVerts++;
      }
    }
  }
  else {
    Node current;
    for(current = G->list[source]->front; current != NULL; current = current->next) {
      targets[numVerts] = current->target;
      numVerts++;
    }
  }
  targets[numVerts] = -1;

  return targets;
}

//This function runs at O(n) for for matricies and O(n^2) for lists
//because lists have to search through all of their targets
int* predecessors(Graph G, int target) {
  int* sources = malloc((G->n + 1) * sizeof(int));
  int i, numVerts = 0;

  if (G->rep == MATRIX) {
    for (i = 0; i < G->n; i++) {
      if (G->matrix[i][target] != INFINITY) {
	sources[numVerts] = i;
	numVerts++;
      }
    }
  }
  else {
    Node current;
    for (i = 0; i < G->n; i++) {
      for(current = G->list[i]->front; current != NULL; current = current->next) {
	if (current->target == target) {
	  sources[numVerts] = i;
	  numVerts++;
	}
      }
    }
  }
  sources[numVerts] = -1;

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
  else {
    int i;
    Node current;
    for (i = 0; i < g->n; i++) {
      current = g->list[i]->front;
      printf("%d:\t", i);
      while (current != NULL) {
	printf("[%d, %.3f]\t", current->target, current->weight);
	current = current->next;
      }
      printf("\n");
    }
  }
}

int main() {}
