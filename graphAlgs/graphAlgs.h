#ifndef GRAPHALGS_H
#define GRAPHALGS_H
 
#include "graph.h"


/* Construct a graph that is the transitive closure of g.
 * Ignore the weights of g.  The weights of the new graph
 * should all be 0. There is an edge u->v in the new graph
 * if and only if there is a path from u to v in g.
 * 
 * Implement this using Warshall's algorithm and matrix 
 * representation for the result graph.
 */
Graph transClose(Graph g);


/* Assume g is a symmetric graph, so it can be 
 * considered as an undirected graph.  
 * (In particular, the weight u->v must equal weight v->u
 * for every u,v.)
 * Assume the weights are not INFINITY.
 *
 * Construct a minimum spanning tree, as a new graph.
 * (So it will have the same number of vertices, 
 * but only some of the edges.)
 * 
 * Implement this using Prim's algorithm.
 */
Graph minSpanTree(Graph g);

#endif
