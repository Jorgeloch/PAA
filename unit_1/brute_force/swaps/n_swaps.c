#include <stdio.h>
#include <stdlib.h>

void swap (int* array, int x, int y)
{
  int aux = array[x];
  array[x] = array[y];
  array[y] = aux;
}

int bubble_sort (int *array, int n)
{
  int swaps = 0;
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (array[j] > array[j + 1])
      {
        swap(array, j, j + 1);
        swaps++;
      }
    }
  }
  return swaps;
}

int main (void)
{
  int n;
  scanf("%i", &n);
  int* array = (int*) malloc(n * sizeof(int));
  if (array == NULL)
  {
    printf("unable to allocate array of size %i/n", n);
  }
  for (int i = 0; i < n; i++)
  {
    scanf("%i", &array[i]);
  }
  int swaps = bubble_sort(array, n);
  printf("%i\n", swaps);
}
