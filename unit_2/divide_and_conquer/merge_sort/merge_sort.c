#include <stdio.h>
#include <stdlib.h>

int* copyArray (int* array, int start, int finish);
void mergeSort (int* array, int n);
void merge (int* left, int* right, int* array, int n);

int main (void)
{
  int n;
  printf("n: ");
  scanf("%i", &n);

  int* array = (int*) malloc(n * sizeof(int));

  for (int i = 0; i < n; i++)
  {
    scanf("%i", &(array[i]));
  }
  
  printf("array inicial = [ ");
  for (int i = 0; i < n; i++)
  {
    printf("%i ", array[i]);
  }
  printf("]\n");
  
  mergeSort(array, n);

  printf("array final = [ ");
  for (int i = 0; i < n; i++)
  {
    printf("%i ", array[i]);
  }
  printf("]\n");

  free(array);
  return 0;
}

int *copyArray (int* array, int start, int finish)
{
  int n = finish - start;
  int* result = (int*) malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
  {
    result[i] = array[i + start];
  }
  return result;
}

void mergeSort (int *array, int n)
{
  if (n > 1)
  {
    int meio = n / 2;
    
    int* left = copyArray(array, 0, meio);
    int* right = copyArray(array, meio, n);

    mergeSort(left, meio);
    mergeSort(right, n - meio);

    merge(left, right, array, n);
  }
}

void merge (int* left, int* right, int* array, int n)
{
  int meio = n / 2;
  
  int sizeLeft = meio;
  int sizeRight = n - meio;
  
  int i = 0, j = 0, k = 0;

  while (i < sizeLeft && j < sizeRight)
  {
    if (left[i] <= right[j])
    {
      array[k] = left[i++];
    }
    else 
    {
      array[k] = right[j++];
    }
    k++;
  }

  if (i == sizeLeft)
  {
    for (; j < sizeRight; j++)
    {
      array[k++] = right[j];
    }
  }
  else
  {
    for (; i < sizeLeft; i++)
    {
      array[k++] = left[i];
    }
  }

  free(left);
  free(right);
}
