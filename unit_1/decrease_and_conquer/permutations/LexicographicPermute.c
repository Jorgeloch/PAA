#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool hasConsecutiveIncreasingOrderElements(int* array, int n);
int** permute(int n);
int searchPivot(int* array, int n);
int searchSwapPosition(int* array, int from, int n);
unsigned long int factorial(int n);
void lexicographicPermute(int n, int** resultArray);
void swap(int* array, int pos1, int pos2);
void copyToResult(int* source, int** destination, int indexOfResult, int size);
void reverseFrom(int* array, int from, int n);

int main(void)
{
  int n;
  printf("n: ");
  scanf("%i", &n);

  unsigned long int result_size = factorial(n);
  printf("factorial: %lu\n", result_size);

  int** result = permute(n);

  for (unsigned long int i = 0; i < result_size; i++)
  {
    for (int j = 0; j < n; j++)   
    {
      printf("%i ", result[i][j]);
    }
    printf("\n");
  }

  for (unsigned long int i = 0; i < result_size; i++)
  {
    free(result[i]);
  }
  free(result);
}

int** permute(int n)
{
  printf("starting permutation\n");
  unsigned long int result_size = factorial(n);
  int** result = (int**) malloc(result_size * sizeof(int*));
  if (!result)
  {
    printf("impossivel alocar array de resultado\n");
    exit(EXIT_FAILURE);
  }
  for (unsigned long int i = 0; i < result_size; i++)
  {
    result[i] = (int*) malloc(n * sizeof(int));
    if(!result[i])
    {
      printf("impossivel alocar resultado na posicao %lu\n", i);
      for (unsigned long int j = 0; j < i; j++)
      {
        free(result[j]);
      }
      free(result);
      exit(EXIT_FAILURE);
    }
  }
  lexicographicPermute(n, result);
  return result;
}

void lexicographicPermute(int n, int** resultArray)
{
  int* array = (int*) malloc(n * sizeof(int));
  if (!array)
  {
    printf("impossivel alocar array\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < n; i++)
  {
    array[i] = i + 1;
  }
  int index = 0;
  copyToResult(array, resultArray, index, n);
  while (hasConsecutiveIncreasingOrderElements(array, n))
  {
    index++;
    int i = searchPivot(array, n);
    int j = searchSwapPosition(array, i, n);
    swap(array, i, j);
    reverseFrom(array, i + 1, n);
    copyToResult(array, resultArray, index, n);
  }
  free(array);
}

void swap(int* array, int pos1, int pos2)
{
  int aux = array[pos1];
  array[pos1] = array[pos2];
  array[pos2] = aux;
}
 
unsigned long int factorial(int n)
{
  unsigned long int result = n;
  for (int i = n - 1; i > 1; i--)
  {
    result *= i;
  }
  return result;
}

void copyToResult(int* source, int** destination, int indexOfResult, int size)
{
  for (int i = 0; i < size; i++)
  {
    destination[indexOfResult][i] = source[i];
  }
}

int searchPivot(int* array, int size)
{
  int pos = 0;
  for (int i = 0; i < size - 1; i++)
  {
    if (array[i] < array[i + 1])
    {
      pos = i;
    }
  }
  return pos;
}

int searchSwapPosition(int* array, int from, int size)
{
  int pos = from + 1;
  int reference = array[from];

  while (array[pos + 1] > reference && pos < size - 1)
  {
    pos++;  
  }

  return pos;
}

void reverseFrom(int* array, int from, int n)
{
  n = n - 1;
  while (from < n)
  {
    swap(array, from, n);
    from++;
    n--;
  }
}

bool hasConsecutiveIncreasingOrderElements(int* array, int n)
{
  for (int i = 0; i < n -1; i++)
  {
    if (array[i] < array[i + 1])
    {
      return true;
    }
  }
  return false;
}

