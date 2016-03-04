#include <stdlib.h>
#include <stdio.h>
#include "dfs.h"

#define white 0
#define gray 1
#define black 2

int count;
int* color;
DFSinfo info;

void dfsvisit(int i) {
  color[i] = gray;
  count++;
  info->discover[i] = count;

  int j;
  for(j = 0; j < sizeof(successors(info->graph, i)) / sizeof(int); j++)
    if (color[j] == white) {
      info->parent[j] = i;
      dfsvisit(j);
    }
  color[i] = black;
  count++;
  info->finish[i] = count;
}

DFSinfo DFS(Graph G) {
  info = (DFSinfo) malloc(sizeof(struct dfsinfo));
  info->graph = G;
  info->discover = (int*) malloc(numVerts(G) * sizeof(int));
  info->finish = (int*) malloc(numVerts(G) * sizeof(int));
  info->parent = (int*) malloc(numVerts(G) * sizeof(int));
  color = (int*) malloc(numVerts(G) * sizeof(int));
  count = 0;
  
  int i;
  for (i = 0; i < numVerts(G); i++)
    if (color[i] == white)
      dfsvisit(i);

  return info;
}
