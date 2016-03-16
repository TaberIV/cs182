#include "sorting.c"

int main() {
  char* arr[5] = {"Taber", "Brendan", "Gavin", "Nick", "Cheyenne"};
  /*
  strcpy(arr[0], "Taber");
  strcpy(arr[1], "Brendan");
  strcpy(arr[2], "Gavin");
  strcpy(arr[3], "Nick");
  strcpy(arr[4], "Cheyenne");
  */
  printf("Unsorted: \n");
  for (int i = 0; i < 5; i++)
    printf("%s \n", arr[i]);

  printf("\nInsertion Sort: \n");
  insertionsort(arr, 0, 5);
  for (int i = 0; i < 5; i++)
    printf("%s \n", arr[i]);
}
