#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int *change_making(int *D, int size_d, int n);

int main(void) {
  int n_denominations, n;

  printf("enter the number of denominations: ");
  scanf("%i", &n_denominations);

  int *D = (int *)malloc(n_denominations * sizeof(int));
  if (!D) {
    printf("impossible to allocate array of denominations\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n_denominations; i++) {
    printf("enter the value of the denomination %i: ", i + 1);
    scanf("%i", &D[i]);
  }

  printf("enter the ammount you wanna change: ");
  scanf("%i", &n);

  unsigned int *F = change_making(D, n_denominations, n);

  printf("to change %i, you will need %i coins\n", n, F[n]);

  printf("number of coins = |");
  for (int i = 0; i <= n; i++) {
    printf(" %i |", F[i]);
  }
  printf("\n");

  free(D);
  free(F);
  return 0;
}

unsigned int *change_making(int *D, int size_d, int n) {
  unsigned int *F = (unsigned int *)calloc((n + 1), sizeof(unsigned int));
  F[0] = 0;
  for (int i = 1; i <= n; i++) {
    unsigned int temp = INT_MAX;
    int j = 0;
    while (j < size_d && i >= D[j]) {
      int position = i - D[j];
      int coins = F[position];
      if (position >= 0 && position <= n && temp > coins) {
        temp = coins;
      }
      j++;
    }
    F[i] = temp + 1;
  }
  return F;
}
