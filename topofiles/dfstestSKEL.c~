/* some tests for dfs.c */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "graph.h"
#include "graphio.h"
#include "dfs.h"


/* Prints the information produced by DFS, using names of vertices.
Assumes di->graph == gi->graph.  */
void printDFSinfo(DFSinfo di, GraphInfo gi) {
    assert (di->graph == gi->graph);
    int numV = numVerts(di->graph);
    printf("Printing DFS info \n");
    for (int v = 0; v < numV; v++) {
        printf("Vertex %s discovered %3i finished %3i ",
               gi->vertnames[v], di->discover[v], di->finish[v]);
        if (di->parent[v] != -1)
            printf("parent %s \n", gi->vertnames[di->parent[v]]);
        else
            printf("parent %i \n", di->parent[v]);
    }
    printf("Vertices in order of finish:\n");
    for (int i = 0; i < numV; i++)
        printf("%s ", gi->vertnames[di->finorder[i]]);
    printf("\ndone printing DFS info\n");
}


int main() {
    GraphInfo gi; 
    DFSinfo di;

    printf("\n dfstest: testing empty graph\n");
    gi = readGraph("emptyGraph.txt", LIST);
    di = DFS(gi->graph);
    printDFSinfo(di,gi);
    disposeGraph(gi->graph); 
    // we won't bother to dispose the graph info or DFSinfo
    


    return 0;
}
