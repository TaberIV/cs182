#include "sorting.c"

int main() {
  int* arr = malloc(5 * sizeof(int));

  arr[0] = 3;
  arr[1] = 9;
  arr[2] = 1;
  arr[3] = 18;
  arr[4] = -2;

  /*char* arr[5];
  
  strcpy(arr[0], "Taber");
  strcpy(arr[1], "Brendan");
  strcpy(arr[2], "Gavin");
  strcpy(arr[3], "Nick");
  strcpy(arr[4], "Cheyenne");*/
  
  quicksort(arr, 0, 5);

  for (int i = 0; i < 5; i++)
    printf("%d \n", arr[i]);
}
