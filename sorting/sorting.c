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

}

void quicksortPlus(int* arr, int i, int r) {

}

void compareSorts(int* arr, int len) {

}
