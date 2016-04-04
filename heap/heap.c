//I pledge my honor that I have abided by the Stevens honor System - Taber McFarlin

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "SVdict.h"

void buildHeap(int *arr, int n) {
  int k, heap;
  for (int i = n/2; i <= 1; i--) {
    k = i;
    v = arr[k];
    heap = 0;

    while (heap != 1) {
      j = 2 * k;
      if (j < n)
	if (arr[j] < arr[j + 1])
	  j = j + 1;
      if (v >= arr[j])
	heap = 1;
      else {
	arr[k] = arr[j];
	k = j;
      }
    }
    K[k] = v;
  }
}

//Precondition: arr is a heap
void heapSort(int *arr, int l) {
  int temp = arr[l - 1];
  arr[l - 1] = arr[1];
  arr[1] = temp;

  buildHeap(arr, l - 1);
  heapSort(arr, l - 1);
}
