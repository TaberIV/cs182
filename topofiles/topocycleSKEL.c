#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h> 
#include <assert.h>

#include "graph.h"
#include "graphio.h"
#include "dfs.h"
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

**************** NOT PROVIDED

}
