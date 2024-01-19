#include <stdio.h>
#include <stdlib.h>

int findBiggerValue(int n, int* array);

int main (void)
{
  int n;
  scanf("%i", &n);

  int* array = (int*) malloc(n * sizeof(int));

  for (int i = 0; i < n; i++)
  {
    scanf("%i", &array[i]);
  }

  int biggerValue = findBiggerValue(n, array);

  printf("%i\n", biggerValue);
  free(array);
}

int findBiggerValue(int n, int* array)
{
  int start = 0;
  int finish = n - 1;
  int middle;
  while (start <= finish)
  {
    middle = (start + finish) / 2;
    int value = array[middle];
    int left = array[middle - 1];
    int right = array[middle + 1];
    if (value > left && value > right)
    {
      return value;
    }
    else if (value > left && value < right)
    {
      start = middle + 1;
    }
    else 
    {
      finish = middle - 1;
    }
  }
  return -1;
}
