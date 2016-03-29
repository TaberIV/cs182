#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "sorting.c"

int main() {
  char* arr[6] = {"Taber", "Brendan", "Gavin", "Nick", "Cheyenne", "Alyssa"};

  printf("Unsorted:\n");
  for (int i = 0; i < 6; i++) {
    printf("%s\n", arr[i]);
  }
  
  quicksort(arr, 0, 6);

  printf("\nQuicksort:\n");
  for (int i = 0; i < 6; i++) {
    printf("%s\n", arr[i]);
  }
  
  //compareSorts(arr, 6);
}
