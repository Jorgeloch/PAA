#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int mdc(int m, int n)
{
  if (n == 0)
  {
    return m;
  }
  return mdc(n, m % n);
}

int main() {
  int *values = (int *) malloc(2 * sizeof(int));
  for (int i = 0; i < 2; i++)
  {
    scanf("%d", &values[i]);
  }
  int result = mdc(values[0], values[1]);
  free(values);
	return result;
}
