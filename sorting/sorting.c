#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void swap(int* arr, int a, int b) {
  int temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

void insertionsort(int* arr, int l, int r) {
  for (int i = l + 1; i < r; i++)
    for (int j = i; j >= 0 && arr[j - 1] > arr[j]; j--)
      swap(arr, j - 1, j);
}

void quicksort(int* arr, int i, int r) {
  for (int i = 0; i < 5; i++)
    printf("%d \n", arr[i]);
  
  int start = i;
  int end = r;
  int pivot = arr[i];
  if (r - i > 1) {
    while (i < r-1) {
      while (i < r && arr[i] <= pivot) {
	printf("Increment i\n");
	i++;
      }
      while (r-1 > i && arr[r - 1] > pivot) {
	printf("Decrement r\n");
	r--;
      }
      printf("Swap indecies %d and %d (values %d and %d)\n", i, r - 1, arr[i], arr[r - 1]);
      swap(arr, i, r - 1);
    }
    swap(arr, start, i - 1);
    printf("Sort from %d to %d\n", start, i - 1);
    quicksort(arr, start, i - 1);
    printf("Sort from %d to %d\n", r, end);
    quicksort(arr, r, end);
  }
}

void quicksortPlus(int* arr, int i, int r) {

}

void compareSorts(int* arr, int len) {

}
