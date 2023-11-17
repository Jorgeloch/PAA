#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char calcular_digito (char *key, int start, int end)
{
  char max = key[start];
  for (int i = start; i < end; i++)
  {
    printf("%c", key[i]);
    if (key[i] > max)
    {
      max = key[i];
    }
  }
  printf("\nmax: %c\n", max); 
  return max;
}

int main (void)
{
  char *key = (char *) calloc(14, sizeof(char));
  scanf("%s", key);
  while (strcmp(key, "FIM"))
  {
    int count = 0, digit = (int) (key[12] - '0');
    for (int i = 0; i < 3; i++)
    {
      count += (int) (calcular_digito(key, i * 3 + i, (i * 3 + i) + 3) - '0');
    }
    count %= 10;
    if (count == digit)
    {
      printf("VALIDO\n");
    }
    else
    {
      printf("INVALIDO\n");
    }
    scanf("%s", key);
  }
  free(key);
  return 0;
}
