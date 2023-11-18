#include <stdio.h>

int euclid (int m, int n)
{
  while (n != 0)
  {
    int r = m % n;
    m = n;
    n = r;
  }
  return m;
}

int main (void)
{
  int m, n;
  printf("m: ");
  scanf("%i", &m);
  printf("n: ");
  scanf("%i", &n);
  int result = euclid(m, n);
  printf("mdc(m,n) = %i\n", result);
}