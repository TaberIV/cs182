/* Assume the file exists and has the format described in dfstest.c.
   Read the file and run depth-first search.
   Based on the DFS info, check whether the graph has a cycle.  
   If so, print the vertices of a cycle.  (Just one cycle, even if there are several.)
   If not, print all the vertices, topologically sorted.
*/
void topocycle(char * filepath);
