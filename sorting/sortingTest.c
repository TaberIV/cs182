#include "sorting.c"

int main() {
  char* arr[5] = {"Taber", "Brendan", "Gavin", "Nick", "Cheyenne"};
  char* arr1[5] = {"Taber", "Brendan", "Gavin", "Nick", "Cheyenne"};
  
  printf("Unsorted: \n");
  for (int i = 0; i < 5; i++)
    printf("%s \n", arr[i]);

  printf("\nInsertion Sort: \n");
  insertionsort(arr, 0, 5);
  for (int i = 0; i < 5; i++)
    printf("%s \n", arr[i]);
  
  printf("\nQuicksort: \n");
  quicksort(arr1, 0, 5);
  for (int i = 0; i < 5; i++)
    printf("%s \n", arr1[i]);
}
