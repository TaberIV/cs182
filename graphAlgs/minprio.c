#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "graph.c"
#include "minprio.h"

struct minprio {
    int arrsize; 
    int numElts;
    Handle* arr;
    Comparator comp;
};

MinPrio makeQueue(Comparator comp, int maxsize) {
  MinPrio qp = malloc(sizeof(struct minprio));
  qp->arrsize = maxsize + 1;
  qp->numElts = 0;
  qp->arr = malloc(qp->arrsize * sizeof(struct handle));
  qp->comp = comp;

  return qp;
}

void disposeQueue(MinPrio qp) { //NOT DONE
  free(qp->arr);
  free(qp);
}

Handle enqueue(MinPrio qp, void* item) {
  
}

/* 1 if queue has elements, else 0 (assuming qp non-null) */
int nonempty(MinPrio qp) {
  return (qp->numElts > 0) ? 1 : 0;
}

/* dequeue and return a minimum element according to the comparator.
 * Assumes qp non-null and queue nonempty */
void* dequeueMin(MinPrio qp) {

}

/* decrease the item's key
 * Must be called whenever comparison value may have changed.
 * Must only decrease comparison value (i.e. raise priority).
 *
 * Assumes qp non-null and hand is in the queue. 
 */
void decreasedKey(MinPrio qp, Handle hand) {

}
