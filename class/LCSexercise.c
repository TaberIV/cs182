#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int max(int x, int y) {
    if (x >= y) return x;
    else return y;
}

/* length of the longest common subsequence of a and b,
 * assuming a and b point to arrays.
 */
int LCS(char* a, char* b) {
  int matrix[strlen(a) + 1][strlen(b) + 1]; 
  
  for (int i = 0; i <= strlen(a); i++) {
    for (int j = 0; j <= strlen(b); j++) {
      if (i == 0 || j == 0)
	matrix[i][j] = (a[i] == b[j]) ? 0 : 0;
      else if (a[i] == b[j])
	matrix[i][j] = 1 + matrix[i - 1][j - 1];
      else
	matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - 1]);
    }
  }
  
  return matrix[strlen(a)][strlen(b)]; /* TO BE IMPLEMENTED */
}


int main() {

    char* a = "AGGACAT";
    char* b = "ATTACGAT";
    printf("first test returns %i, should be 5 \n", LCS(a,b));

    a = "AAGCTTAAGAAGCCTTCAACAGG";
    b = "GGGTTTGGCATGTCCTTGACCAT";
    printf("second test returns %i, should be 14 \n", LCS(a,b));

    a = "ATCTGTGGTGGAAAGGCTAACATACC";
    b = "CAAGAAATGTTAACTCAGAGTTGT";
    printf("third test returns %i, should be 12 \n", LCS(a,b));

}


