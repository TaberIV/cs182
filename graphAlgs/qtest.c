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
}

int main() {
  MinPrio q = makeQueue((Comparator) strcmp, 12);
  enqueue(q, "BAD");
  enqueue(q, "GOOD");
  enqueue(q, "EASY");
  enqueue(q, "HARD");
  enqueue(q, "FUN");
  enqueue(q, "ALEX");
  enqueue(q, "TABER");
  enqueue(q, "KRISTEN");
  enqueue(q, "BRENDAN");
  enqueue(q, "BEN");
  enqueue(q, "GAVIN");
  enqueue(q, "NAUMANN");
  printQueue(q);
  return 0;
}
