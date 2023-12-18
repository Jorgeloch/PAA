#include <stdio.h>
#include <stdlib.h>

void InsertionSort(int* array, int size)
{
  for (int i = 1; i < size; i++)
  {
    int value = array[i];
    int j = i - 1;
    while (j >= 0 && array[j] > value)
    {
      array[j + 1] = array[j];
      j--;
    }
    array[j + 1] = value;
  }
}

void RecursiveInsertionSort(int* array, int size)
{
  if (size <= 1)
  {
    return;
  }
  RecursiveInsertionSort(array, size - 1);
  int value = array[size - 1];
  int j = size - 2;
  while (j >= 0 && array[j] < value)
  {
    array[j + 1] = array[j];
    j--;
  }
  array[j] = value;
}
