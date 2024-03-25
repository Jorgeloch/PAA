#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **collect(int rows, int columns, int **T);
int **allocate_matrix(int rows, int columns);
void print_table(int rows, int columns, int **T);

int main(void) {
  srand(time(NULL));

  int rows, columns;

  printf("rows: ");
  scanf("%i", &rows);
  printf("columns: ");
  scanf("%i", &columns);

  int **T = allocate_matrix(rows, columns);

  for (int i = 0; i < columns; i++) {
    for (int j = 0; j < rows; j++) {
      T[i][j] = rand() % 2;
    }
  }
  printf("T:\n");

  print_table(rows, columns, T);

  int **F = collect(rows, columns, T);

  printf("F:\n");

  print_table(rows, columns, F);

  for (int i = 0; i < columns; i++) {
    free(T[i]);
  }
  free(T);

  for (int i = 0; i < columns; i++) {
    free(F[i]);
  }
  free(F);
}

void print_table(int rows, int columns, int **T) {
  for (int i = 0; i < columns; i++) {
    for (int j = 0; j < rows; j++) {
      printf("----");
    }
    printf("-\n");
    printf("|");
    for (int j = 0; j < rows; j++) {
      printf(" %i |", T[i][j]);
    }
    printf("\n");
  }

  for (int j = 0; j < rows; j++) {
    printf("----");
  }
  printf("-\n\n");
}

int **allocate_matrix(int rows, int columns) {
  int **T = (int **)calloc(columns, sizeof(int *));
  if (!T) {
    printf("impossivel allocar matriz\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < columns; i++) {
    T[i] = (int *)calloc(rows, sizeof(int));
    if (!T[i]) {
      printf("impossivel allocar matriz\n");
      exit(EXIT_FAILURE);
    }
  }
  return T;
}

int **collect(int rows, int columns, int **T) {
  int **F = allocate_matrix(rows, columns);

  F[0][0] = T[0][0];

  for (int i = 1; i < columns; i++) {
    F[i][0] += F[i - 1][0] + T[i][0];
  }

  for (int i = 1; i < rows; i++) {
    F[0][i] += F[0][i - 1] + T[0][i];
  }

  for (int i = 1; i < rows; i++) {
    for (int j = 1; j < columns; j++) {
      int top = F[i][j - 1];
      int left = F[i - 1][j];
      if (top > left) {
        F[i][j] += top + T[i][j];
      } else {
        F[i][j] += left + T[i][j];
      }
    }
  }

  return F;
}
