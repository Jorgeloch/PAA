#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum direction { 
  LEFT = -1,
  RIGHT = 1
} direction;

typedef struct {
  int value;
  direction d;
} element;

element* initializeList(int n);
void swap(element* array, int pos1, int pos2);
bool hasMobileElement(element* array, int size, int* position_of_element);
void JohnsonTrotter(int n, int** result);
int** permutations(int n);
unsigned long int factorial(int n);

int main (void)
{
  int n = 1;
  do
  {
    printf("n: ");
    scanf("%i", &n);
  }
  while (n <= 0);
  int** result = permutations(n);
  for (unsigned long int i = 0, s = factorial(n); i < s; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%i", result[i][j]);
    }
    printf("\n");
    free(result[i]);
  }
  free(result);
}

int** permutations(int n)
{
  unsigned long int result_size = factorial(n);
  int** list = (int**) malloc(result_size * sizeof(int*));
  if(!list)
  {
    printf("impossivel alocar array resultado\n");
    exit(EXIT_FAILURE);
  }
  for (unsigned long int i = 0; i < result_size; i++) 
  {
    list[i] = (int*) malloc(n * sizeof(int));
    if(!list[i])
    {
      printf("impossivel alocar resultado[%lu]", i);
      exit(EXIT_FAILURE);
    }
  }
  JohnsonTrotter(n, list);
  return list;
}
void JohnsonTrotter(int n, int** result)
{
  element* list = initializeList(n);
  int mobile;
  int count = 0;
  for (int i = 0; i < n; i++)
  {
    result[count][i] = list[i].value;
  }
  while (hasMobileElement(list, n, &mobile))
  {
    element mobile_element = list[mobile];
    swap(list, mobile, mobile + list[mobile].d);
    count++;
    for (int i = 0; i < n; i++)
    {
      result[count][i] = list[i].value;
    }
    for (int i = 0; i < n; i++)
    {
      if (list[i].value > mobile_element.value)
      {
        switch (list[i].d)
        {
          case LEFT:
            list[i].d = RIGHT;
            break;
          case RIGHT:
            list[i].d = LEFT;
            break;
        }
      }
    }
  }
  free(list);
}

element* initializeList(int n)
{
  element* list = (element*) malloc(n * sizeof(element));
  if (!list)
  {
    printf("impossivel alocar lista de elementos\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < n; i++)
  {
    list[i].value = i + 1;
    list[i].d = LEFT;
  }
  return list;
}

bool hasMobileElement(element* array, int size, int* position_of_element)
{
  int max_mobile_value = 0;
  for (int i = 0; i < size; i++)
  {
    int next = i + array[i].d;
    if (array[i].value > max_mobile_value && array[i].value > array[next].value)
    {
      if (!((i == 0 && array[i].d == LEFT) || (i == size - 1 && array[i].d == RIGHT)))
      {
        max_mobile_value = array[i].value;
        *position_of_element = i;
      }
    }
  }
  if (max_mobile_value == 0)
  {
    return false;
  }
  return true;
}

void swap (element* array, int pos1, int pos2)
{
  element aux = array[pos1];
  array[pos1] = array[pos2];
  array[pos2] = aux;
}

unsigned long int factorial(int n)
{
  unsigned long int result = 1;
  for (int i = n; i > 1; i--)
  {
    result *= i;
  }
  return result;
}
