#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
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
  qp->arr = (Handle*) malloc(qp->arrsize * sizeof(struct handle));
  qp->comp = comp;

  return qp;
}

void disposeQueue(MinPrio qp) {
  while (nonempty(qp) == 1)
    free(dequeueMin(qp));
  free(qp->arr);
  free(qp);
}

Handle enqueue(MinPrio qp, void* item) {
  qp->numElts++;
  qp->arr[qp->numElts] = (Handle)  malloc(sizeof(struct handle));
  qp->arr[qp->numElts]->content = item;
  qp->arr[qp->numElts]->pos = qp->numElts;

  Handle new = qp->arr[qp->numElts];
  while (new->pos != 1 && qp->comp(new->content, qp->arr[new->pos / 2]->content) < 0) {
    qp->arr[new->pos] = qp->arr[new->pos / 2];
    qp->arr[new->pos / 2] = new;
    qp->arr[new->pos]->pos = new->pos;
    new->pos = new->pos / 2;
  }
  return new;
}

/* 1 if queue has elements, else 0 (assuming qp non-null) */
int nonempty(MinPrio qp) {
  return (qp->numElts > 0) ? 1 : 0;
}

/* dequeue and return a minimum element according to the comparator.
 * Assumes qp non-null and queue nonempty */
void* dequeueMin(MinPrio qp) {
  void* ret = qp->arr[1]->content;
  qp->arr[1] = qp->arr[qp->numElts];
  qp->arr[1]->pos = 1;
  qp->arr[qp->numElts] = NULL;
  qp->numElts--;
  
  //Doesn't check if it's null
  //If it is not greater than either, stop
  Handle h = qp->arr[1];
  while (h != NULL && qp->arr[h->pos * 2] != NULL &&
	 (qp->comp(qp->arr[h->pos * 2]->content, h->content) < 0 ||
	  (qp->arr[h->pos * 2 + 1] != NULL &&
	   qp->comp(qp->arr[h->pos * 2 + 1]->content, h->content) < 0))) {
    if (qp->arr[h->pos * 2 + 1] == NULL ||
	qp->comp(qp->arr[h->pos * 2]->content, qp->arr[h->pos * 2 + 1]->content) < 0) {
      qp->arr[h->pos] = qp->arr[h->pos * 2];
      qp->arr[h->pos * 2]->pos = h->pos;
      qp->arr[h->pos * 2] = h;
      h->pos *= 2;
    }
    else {
      qp->arr[h->pos] = qp->arr[h->pos * 2 + 1];
      qp->arr[h->pos * 2 + 1]->pos = h->pos;
      qp->arr[h->pos * 2 + 1] = h;
      h->pos = h->pos * 2 + 1;
    }
  }

  return ret;
}

/* decrease the item's key
 * Must be called whenever comparison value may have changed.
 * Must only decrease comparison value (i.e. raise priority).
 *
 * Assumes qp non-null and hand is in the queue. 
 */
void decreasedKey(MinPrio qp, Handle hand) {
  while (hand->pos != 1 && qp->comp(hand->content, qp->arr[hand->pos / 2]->content) < 0) {
    qp->arr[hand->pos] = qp->arr[hand->pos / 2];
    qp->arr[hand->pos / 2] = hand;
    qp->arr[hand->pos]->pos = hand->pos;
    hand->pos = hand->pos / 2;
  }
}
