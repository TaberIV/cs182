#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "sorting.h"

void swap(char* arr[], int a, int b) {
  char* temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

int binarySearch(char* arr[], char* item, int l, int r) {
  if (r <= l)
    return (strcmp(item, arr[l]) > 0)? (l + 1) : l;

  int mid = (l + r)/2;

  if (strcmp(item, arr[mid]) == 0)
    return mid + 1;
  if (strcmp(item, arr[mid]) > 0)
    return binarySearch(arr, item, mid + 1, r);
  return binarySearch(arr, item, l, mid - 1);
}

void insertionsort(char* arr[], int l, int r) {
  int loc, j, k;
  char* item;
  for (int i = l + 1; i < r; i++) {
    j = i - 1;
    item = arr[i];
    loc = binarySearch(arr, item, l, j);
    while (j >= loc) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = item;
  } 
}

int HoarePartition(char* arr[], int l, int r) {
  char* pivot = arr[l];
  int i = l;
  int j = r;
  do {
    do {
      i++;
    } while(strcmp(arr[i], pivot) < 0 && i < j);
    do {
      j--;
    } while(strcmp(arr[j], pivot) > 0 && j > i);
    swap(arr, i, j);
  } while (i < j);
  swap(arr, i, j);
  swap(arr, l, j);
  return j;
}

void quicksort(char* arr[], int l, int r) {
  if (l < r) {
    int s = HoarePartition(arr, l, r);
    quicksort(arr, l, s - 1);
    quicksort(arr, s + 1, r);
  }
}

/* QuicksortPlus: same specification, but use the following form of recursive quicksort:
 * 
 * If r - l <= 10, use insertionsort.
 * Otherwise, use quicksort, choosing the pivot element as the median value of 
 * arr[l], arr[r-1], and arr[(l+r)/2].
 */
void quicksortPlus(char* arr[], int l, int r) {
  if (r - l <= 10) {
    insertionsort(arr, l, r);
  }
  else if (l < r) {
    //partition--------------
    char* pivots[] = {arr[l], arr[r-1], arr[(l+r)/2]};
    insertionsort(pivots, 0, 3);
    char* pivot = pivots[1];
    int s = l;
    for (int i = l + 1; i < r; i++) {
      if (strcmp(arr[i], pivot) < 0) {
	s = s + 1;
	swap(arr, s, i);
      }
    }
    swap(arr, l, s);
    //-----------------------
    quicksort(arr, l, s - 1);
    quicksort(arr, s + 1, r);
  }
}

/* Assume arr has length at least len.
 * For each of the three sort functions, run it 20 times on arr, and print the total time.
 */ 
void compareSorts(char* arr[], int len) {
  char* copy[len];

  clock_t begin, end;
  double time_spent;
  begin = clock();

  for (int j = 0; j < 20; j++) {
    for (int i = 0; i < len; i++)
      copy[i] = arr[i];
    insertionsort(copy, 0, len);
   }

  /* stop timing and print duration */
  end = clock();
  time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;
  printf("Time spent on insertion sort: %fs\n", time_spent);

  begin = clock();

  for (int j = 0; j < 20; j++) {
    for (int i = 0; i < len; i++)
      copy[i] = arr[i];
    quicksort(copy, 0, len);
   }

  /* stop timing and print duration */
  end = clock();
  time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;
  printf("Time spent on quicksort: %fs\n", time_spent);

  begin = clock();

  for (int j = 0; j < 20; j++) {
    for (int i = 0; i < len; i++)
      copy[i] = arr[i];
    quicksortPlus(copy, 0, len);
   }

  /* stop timing and print duration */
  end = clock();
  time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;
  printf("Time spent on quicksortPlus: %fs\n", time_spent);
}
