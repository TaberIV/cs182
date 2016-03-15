#include "sorting.c"

int main() {
  char* arr[5];
  
  strcpy(arr[0], "Taber");
  strcpy(arr[1], "Brendan");
  strcpy(arr[2], "Gavin");
  strcpy(arr[3], "Nick");
  strcpy(arr[4], "Cheyenne");
  
  insertionsort(arr, 0, 5);

  for (int i = 0; i < 5; i++)
    printf("%s \t", arr[i]);
}
