#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
  int cpf;
  int nota;
} candidato;

bool search (candidato* arr, int size, int value, int* pos);

int main (void)
{
  int n_candidatos, n_consultas;
  scanf("%i", &n_candidatos);
  
  candidato* candidatos = (candidato*) malloc(n_candidatos * sizeof(candidato));
  if (!candidatos)
  {
    printf("impossivel alocar array de candidatos\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n_candidatos; i++)
  {
    scanf("%i", &(candidatos[i].cpf));
  }
  for (int i = 0; i < n_candidatos; i++)
  {
    scanf("%i", &(candidatos[i].nota));
  }

  scanf("%i", &n_consultas);

  for (int i = 0; i < n_consultas; i++)
  {
    int cpf;
    scanf("%i", &cpf);
    int pos;
    if (search(candidatos, n_candidatos, cpf, &pos))
    {
      printf("%i\n", candidatos[pos].nota);
    }
    else
    {
      printf("NAO SE APRESENTOU\n");
    }
  }
  free(candidatos);
}

bool search (candidato* arr, int size, int value, int* pos)
{
  int inicio = 0;
  int fim = size;
  while (inicio < fim)
  {
    int meio = inicio + ((fim - inicio) / 2);
    if (arr[meio].cpf > value)
    {
      fim = meio;
    }
    else if (arr[meio].cpf < value)
    {
      inicio = meio + 1;
    }
    else
    {
      *pos = meio;
      return true;
    }
  }
  return false;
}

