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

void insertionsort0(char* arr[], int l, int r) {
  for (int i = l + 1; i < r; i++)
    for (int j = i; j > 0 && strcmp(arr[j - 1], arr[j]) > 0; j--)
      swap(arr, j - 1, j);
}

void quicksort(char* arr[], int i, int r) {
  
}

void quicksortPlus(char* arr[], int i, int r) {

}

void compareSorts(char* arr[], int len) {

}
