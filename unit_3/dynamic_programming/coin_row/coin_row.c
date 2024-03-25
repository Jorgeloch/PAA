#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *coins;
  int *F;
} table;

table init_table(int n);
void coin_row(table t, int n);
int max(int x1, int x2);

int main(void) {
  int n;
  printf("digite a quantidade de moedas: ");
  scanf("%i", &n);

  table t = init_table(n);

  for (int i = 1; i <= n; i++) {
    printf("digite o valor da moeda %i: ", i);
    scanf("%i", &t.coins[i]);
  }

  coin_row(t, n);

  printf("\ncoins: |   |");
  for (int i = 1; i <= n; i++) {
    printf(" %i |", t.coins[i]);
  }
  printf("\n");

  printf("F: |");
  for (int i = 0; i <= n; i++) {
    printf(" %i |", t.F[i]);
  }
  printf("\n\n");

  for (int i = n; i >= 1;) {
    if (t.F[i] == t.coins[i] + t.F[i - 2]) {
      printf("coins[%i] é parte da solucao otima!\n", i);
      i -= 2;
    } else {
      i -= 1;
    }
  }
}

table init_table(int n) {
  table result;
  result.coins = (int *)malloc((n + 1) * sizeof(int));
  result.F = (int *)malloc((n + 1) * sizeof(int));
  return result;
}

void coin_row(table t, int n) {
  t.F[0] = 0;
  t.F[1] = t.coins[1];
  for (int i = 2; i <= n; i++) {
    t.F[i] = max((t.coins[i] + t.F[i - 2]), t.F[i - 1]);
  }
}

int max(int x1, int x2) {
  if (x1 > x2) {
    return x1;
  }
  return x2;
}
