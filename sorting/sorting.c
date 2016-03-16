#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "sorting.h"

void swap(char* arr[], int a, int b) {
  char* temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

void insertionsort(char* arr[], int l, int r) {
  for (int i = l + 1; i < r; i++)
    for (int j = i; j > 0 && strcmp(arr[j - 1], arr[j]) > 0; j--)
      swap(arr, j - 1, j);
}

void quicksort(char* arr[], int i, int r) {
  
}

/*void quicksort(char* arr[], int i, int r) {
  for (int i = 0; i < 5; i++)
    printf("%s \n", arr[i]);
  
  int start = i;
  int end = r;
  char* pivot = arr[i];
  if (r - i > 1) {
    while (i < r-1) {
      while (i < r && strcmp(arr[i], pivot) <= 0) {
	printf("Increment i\n");
	i++;
      }
      while (r-1 > i && strcmp(arr[r - 1], pivot) > 0) {
	printf("Decrement r\n");
	r--;
      }
      printf("Swap indecies %d and %d (values %s and %s)\n", i, r - 1, arr[i], arr[r - 1]);
      swap(arr, i, r - 1);
    }
    swap(arr, start, i - 1);
    printf("Sort from %d to %d\n", start, i - 1);
    quicksort(arr, start, i - 1);
    printf("Sort from %d to %d\n", r, end);
    quicksort(arr, r, end);
  }
  }*/

void quicksortPlus(char* arr[], int i, int r) {

}

void compareSorts(char* arr[], int len) {

}
