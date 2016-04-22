#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "minprio.c"

void printQueue(MinPrio qp) {
  int level = -1;
  for (int i = 1; i <= qp->numElts; i++) {
    if (log2(i) == floor(log2(i)))
      level++;
    
    for (int j = 0; j < level; j++)
      printf(" ");
    printf("%d %s %d\n", i/2, qp->arr[i]->content, i);
  }
  printf("\n");
}

int main() {
  MinPrio q = makeQueue((Comparator) strcmp, 12);
  enqueue(q, "BAD");
  enqueue(q, "GOOD");
  enqueue(q, "EASY");
  enqueue(q, "HARD");
  enqueue(q, "FUN");
  enqueue(q, "ALEX");
  Handle me = enqueue(q, "TABER");
  enqueue(q, "KRISTEN");
  enqueue(q, "BRENDAN");
  enqueue(q, "BEN");
  enqueue(q, "GAVIN");
  Handle n = enqueue(q, "NAUMANN");
  printQueue(q);

  /* Test for decreasedKey
  n->content = "DAVE";
  decreasedKey(q, n);
  printQueue(q);*/
  
  /* Tests for dequeue
  int n = 12;
  for(int i = 0; i < n; i++) {
    printf("\nAfter %d dequeue(s):\n", i + 1);
    dequeueMin(q);
    printQueue(q);
    }*/
  
  return 0;
}
