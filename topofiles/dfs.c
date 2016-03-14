#include <stdlib.h>
#include <stdio.h>
#include "dfs.h"

#define white 0
#define gray 1
#define black 2

int count;
int fincount;
int* color;
DFSinfo info;

void dfsvisit(int i) {
  
  color[i] = gray;
  count++;
  info->discover[i] = count;

  int j;
  for(j = 0; successors(info->graph, i)[j] != -1; j++) {
    if (color[successors(info->graph, i)[j]] == white) {
      info->parent[j] = i;
      dfsvisit(successors(info->graph, i)[j]);
    }
  }
  color[i] = black;
  info->finorder[fincount] = i;
  count++;
  fincount++;
  info->finish[i] = count;
}

DFSinfo DFS(Graph G) {
  info = (DFSinfo) malloc(sizeof(struct dfsinfo));
  info->graph = G;
  info->discover = (int*) malloc(numVerts(G) * sizeof(int));
  info->finish = (int*) malloc(numVerts(G) * sizeof(int));
  info->parent = (int*) malloc(numVerts(G) * sizeof(int));
  info->finorder = (int*) malloc(numVerts(G) * sizeof(int));
  color = (int*) malloc(numVerts(G) * sizeof(int));
  int i;
  for (i = 0; i < numVerts(G); i++) {
    info->parent[i] = -1;
    info->discover[i] = -1;
    info->finish[i] = -1;
    info->parent[i] = -1;
    info->finorder[i] = -1;
    color[i] = white;
  }
  
  count = 0;
  fincount = 0;
  
  for (i = 0; i < numVerts(G); i++)
    if (color[i] == white) {
      dfsvisit(i);
    }

  return info;
}
