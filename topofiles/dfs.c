#include "dfs.h"

#define white 0
#define gray 1
#define black 2

int count;
int* color;
DFSinfo info;

DFSinfo DFS(Graph G) {
  info = (DFSinfo) malloc(sizeof(struct dfsinfo));
  info->graph = G;
  info->discover = malloc(numVerts(G) * sizeof(int));
  info->finish = malloc(nnumVerts(G) * sizeof(int));
  info->parent = malloc(nnumVerts(G) * sizeof(int));

  color = (int*) malloc(numVerts(G) * sizeof(int));

  int i;
  for (i = 0; i < numVerts(G); i++)
    if (color[i] == white)
      dfsvisit(i);
}

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
}
