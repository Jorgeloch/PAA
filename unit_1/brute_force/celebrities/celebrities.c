#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int knows;
  int is_known;
} person;
int main (void)
{
  int n;
  scanf("%i", &n);

  int** matrix = (int**) malloc(n * sizeof(int*));
  for (int i = 0; i < n; i++)
  {
    matrix[i] = (int*) malloc(n * sizeof(int));
  }

  person* people = (person*) calloc(n, sizeof(person));
  
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      scanf("%i", &(matrix[i][j]));
    }
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      people[i].knows += matrix[i][j];
      people[i].is_known += matrix[j][i];
    }
  }

  for (int i = 0; i < n; i++)
  {
    if(people[i].knows == 1 && people[i].is_known == n)
    {
      printf("%i\n", i);
      for (int i = 0; i < n; i++)
      {
        free(matrix[i]);
      }
      free(matrix);
      free(people);
      return 0;
    }
  }
  printf("NAO HA CELEBRIDADE\n");
  for (int i = 0; i < n; i++)
  {
    free(matrix[i]);
  }
  free(matrix);
  free(people);
  return 0;
}

