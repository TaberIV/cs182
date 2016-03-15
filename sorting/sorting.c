#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void swap(char* arr[], int a, int b) {
  char* temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

void insertionsort(char* arr[], int l, int r) {
  for (int i = l + 1; i < r; i++)
    for (int j = i; strcmp(arr[j - 1], arr[j]) > 0; j--)
      swap(arr, j - 1, j);
}
