#include <stdio.h>
#include <stdlib.h>

void quickSort(int* array, int left, int right);
void swap(int* array, int x1, int x2);
int partition(int* array, int left, int right);

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
  
  quickSort(array, 0, n - 1);

  printf("array final = [ ");
  for (int i = 0; i < n; i++)
  {
    printf("%i ", array[i]);
  }
  printf("]\n");

  free(array);
  return 0;
}

void quickSort(int* array, int left, int right)
{
  if (left < right)
  {
    int position = partition(array, left, right);
    quickSort(array, left, position - 1);
    quickSort(array, position + 1, right);
  }
}

int partition(int* array, int left, int right)
{
  int pivot = array[left];
  int i = left, j = right + 1;
  do 
  {
    do
    {
      i++;
    }
    while (i < right && array[i] < pivot);
    do
    {
      j--;
    }
    while (j > left && array[j] > pivot);
    swap(array, i, j);
  }
  while (i < j);
  swap(array, i, j);
  swap(array, left, j);
  return j;
}

void swap(int* array, int x1, int x2)
{
  int aux = array[x1];
  array[x1] = array[x2];
  array[x2] = aux;
}
