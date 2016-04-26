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

int dubcmp(double a, double b) {
  return a - b;
}

int main() {
  MinPrio Q = makeQueue((Comparator) dubcmp, 100);
}
