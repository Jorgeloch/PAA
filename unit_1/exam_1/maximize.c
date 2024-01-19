#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int* maximize (int* votos, int n, int* resultSize)
{
  int* result = (int*) calloc(n, sizeof(int));
  int* visitado = (int*) calloc(n, sizeof(int));
  int* possiveis_ciclos = (int*) calloc(n, sizeof(int));
  int n_possiveis_ciclos = 0;
  int visitados = 0;
  int i = 0;

  while (visitados < n)
  {
    if (!visitado[i])
    {
      visitado[i] = 1;
      i = votos[i] - 1;
      if (visitado[i])
      {
        possiveis_ciclos[n_possiveis_ciclos++] = i;
      }
      visitados++;
    }
    else
    {
      i = (i + 1) % n;
    }
  }
  
  int maior_ciclo = 0;
  int index_maior_ciclo = 0;

  for (int i = 0; i < n_possiveis_ciclos; i++)
  {
    int count = 1;
    for (int j = votos[possiveis_ciclos[i]] - 1; votos[j] != votos[possiveis_ciclos[i]];)
    {
      count++;
      j = votos[j] - 1;
    }
    if (count > maior_ciclo)
    {
      index_maior_ciclo = possiveis_ciclos[i];
    }
  }

  result[(*resultSize)++] = votos[index_maior_ciclo];
  
  for (int j = votos[index_maior_ciclo] - 1; votos[j] != votos[index_maior_ciclo];)
  {
    result[(*resultSize)++] = votos[j];
    j = votos[j] - 1;
  }

  qsort(result, *resultSize, sizeof(int), cmp);
  free(possiveis_ciclos);
  free(visitado);
  return result;
}

int main (void)
{
  int n;
  scanf("%i", &n);

  int* votos = (int*) malloc(n * sizeof(int));

  for (int i = 0; i < n; i++)
  {
    scanf("%i", &votos[i]);
  }

  int resultSize = 0;

  int* result = maximize(votos, n, &resultSize);
  for (int i = 0; i < resultSize; i++)
  {
    printf("%i\n", result[i]);
  }
  free(result);
  free(votos);
}
