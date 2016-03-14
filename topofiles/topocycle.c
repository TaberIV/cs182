#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h> 
#include <assert.h>

#include "graph.h"
#include "graphio.h"
#include "dfs.c"
#include "topocycle.h"

/*************************
 * DFS facts
 * 
 * For either a digraph or even undirected graph, u is a proper ancestor of v
 * in the DFS forest iff discover[u] < discover[v] < finish[v] < finish[u].
 * 
 * A 'back edge' goes from a vertex to an ancestor of that vertex.
 * A graph is cyclic if and only if the DFS forest has a back edge.
 *
 * To topologically sort an acyclic graph, order the vertices in reverse
 * of the 'finish' order.  (Can do that during DFS by pushing finished vertices
 * onto a linked list.  Or do it later by later by sorting, but that costs more.)
 * ************************ */ 



/* whether anc is a proper ancestor of v (i.e., ancestor and anc!=v) 
 * Assume u, v are vertices of di->graph. */
int proper_ancestor(DFSinfo di, int anc, int v) {
  return anc!=v &&
        di->discover[anc] < di->discover[v] &&
        di->discover[v] < di->finish[v] &&
        di->finish[v] < di->finish[anc];
}

void topocycle(GraphInfo gi) {
  DFSinfo di = DFS(gi->graph);
  int i, j;
  //Check for cycles---------------------
  int found = 0;
  for (i = 0; i < numVerts(di->graph); i++) {
    for(j = 0; successors(di->graph, i)[j] != -1; j++) {
      if (proper_ancestor(di, successors(di->graph, di->finorder[i])[j], di->finorder[i])) {
	  found = 1;
	  break;
      }
    }
    if (found)
      break;
  }
  //-------------------------------------

  if (found == 1) {
    printf("There is a cycle: \n");
    int* cycle = (int*) malloc(numVerts(di->graph) * sizeof(int));
    int vert = di->finorder[i], index = 0, endVert = vert;
    found = 0;

    printf("%d\n", vert);
    printf("%d\n", di->parent[vert]);
    printf("%d\n", di->parent[di->parent[vert]]);
    while(found == 0) {
      cycle[index] = vert;
      index++;

      assert(vert != -1);
      if (successors(di->graph, vert)[j] == endVert)
	found = 1;
    }
    
    assert(found == 1);
    cycle[index] = i;

    for (; index >= 0; index--)
      printf("%s ", gi->vertnames[cycle[index]]);
    printf("%s ", gi->vertnames[i]);
    
  }
  else {
    for (i = 1; i <= numVerts(di->graph); i++)
      printf("%s ", gi->vertnames[di->finorder[numVerts(di->graph) - i]]);
    printf("\n");
  }
}
