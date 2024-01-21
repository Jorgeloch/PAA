#include <stdio.h>
#include <stdlib.h>

int n; // tamanho das funções. i.e, o programa gerará funções de [0..n-1] em [0..n-1]


//Calcula m^n
int pot(int m, int n) {
  int res = 1;
  for (int i = 0; i<n; i++) {
    res *= m;
  }
  return res;
}

int** todasFuncoes(int n_) { 
  int size = n;
  if (n_ == 1)
  {
    int** result = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
    {
      result[i] = (int*) malloc(sizeof(int));
      result[i][0] = i;
    }
    return result; 
  }

  int** recursiveAnswer = todasFuncoes(n_ - 1);
  int** mainAnswer = (int**) malloc(pot(size, n_) * sizeof(int*));

  for (int i = 0, curSize = pot(size, n_); i < curSize; i++)
  {
    mainAnswer[i] = (int*) malloc(n_ * sizeof(int));
  }

  int count = 0;

  for (int i = 0; i < size; i++)
  {
    if (i % 2 == 0)
    {
      for (int j = 0, previousSize = pot(size, n_ - 1); j < previousSize; j++)
      {
        int* array = recursiveAnswer[j];
        mainAnswer[count][0] = i;
        for (int k = 0; k < n_ - 1; k++)
        {
          mainAnswer[count][k + 1] = array[k];
        }
        count++;
      }
    }
    else
    {
      for (int j = pot(size, n_ - 1) - 1; j >= 0; j--)
      {
        int* array = recursiveAnswer[j];
        mainAnswer[count][0] = i;
        for (int k = 0; k < n_ - 1; k++)
        {
          mainAnswer[count][k + 1] = array[k];
        }
        count++;
      }
      
    }
  }
  for (int i = 0, prevoiusSize = pot(size, n_ - 1); i < prevoiusSize; i++)
  {
    free(recursiveAnswer[i]);
  }
  free(recursiveAnswer);
  return mainAnswer;
}

//comparação de funções para ordenação lexicográfica
int cmp(int* f1, int* f2) {
  int i;
  for (i = 0; i<n && f1[i]==f2[i]; i++){}
  if (i == n)
    return 0;
  if (f1[i] > f2[i])
    return 1 ;
  return -1; 
}

//comparação de funções para uso do qsort
int compare(const void* a_, const void* b_) {
  int *const *a = a_; 
  int *const *b = b_;
  return cmp(*a, *b);
}

//próxima função seguindo a ordem lexicográfica
void proximaFuncao(int* f, int n) {
  int i;
  for (i=n-1; f[i]==n-1; i--)
    f[i] = 0;
  f[i]++;
}

//quantidade de elementos em que as funções f1 e f2 diferem.
int difs(int* f1, int* f2, int n) {
  int d = 0;
  for (int i=0; i<n; i++)
    if (f1[i] != f2[i])
      d++;
  return d;
}

int main() {
  scanf("%d", &n);
  int** funs = todasFuncoes(n);

  //verificação de mudança mínima
  int tam = pot(n, n);

  for (int i = 1; i<tam; i++)
    if ( difs(funs[i-1],funs[i], n) !=1 ) {
      printf("No minimal change\n");
      exit(0);
    }

  //ordenação das funções na ordem lexicográfica
  qsort(funs, tam, sizeof(int*), compare);

  //criação da função zero.
  int* f = (int*) malloc(n * sizeof(int));
  for (int i = 0; i<n; i++)
    f[i] = 0;

  //verificação da geração de todas as funções
  for (int i = 0; i<tam; i++ ) {
    if (difs(f, funs[i], n) != 0) {
      printf("Talvez não esteja gerando todas as funções?");
      exit(0);
    }
    proximaFuncao(f, n);
  }

  printf("SIM");
}
