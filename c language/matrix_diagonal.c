#include <stdio.h>
#include <stdlib.h>

int main (void)
{
  int n;
  printf("n: ");
  scanf("%i", &n);

  // dynamically allocating matrix
  float *matrix[n];
  for (int i = 0; i < n; i++)
  {
    matrix[i] = (float *)  malloc(n * sizeof(float));
  }

  // populating the matrix
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      scanf("%f", &matrix[i][j]);
      printf("matrix[%i][%i] = %f\n", i, j, matrix[i][j]);
    }
  }

  printf("tr(A) = ");
  
  float result = 0;
  for (int i = 0; i < n; i++)
  {
    result += matrix[i][i];
    printf("(%.2f) + ", matrix[i][i]);
  }
  result += matrix[n - 1][n - 1];
  printf("(%.2f) = %.2f\n", matrix[n - 1][n - 1], result);
  
  for (int i = 0; i < n; i++)
  {
    free(matrix[i]);
  }
}
