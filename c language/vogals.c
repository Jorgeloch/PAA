#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N_VOGALS 5

typedef enum vogals {a, e, i, o , u} vogals;

int main (void)
{
  int *counter = (int *) calloc(N_VOGALS, sizeof(int));
  char *str = (char *) calloc(200, sizeof(char));
  char *curr = str;
  fgets(str, 200, stdin);
  while (*curr != '\0')
  {
    switch (*curr)
    {
      case 'a':
        counter[a]++;
        break;
      case 'e':
        counter[e]++;
        break;
      case 'i':
        counter[i]++;
        break;
      case 'o':
        counter[o]++;
        break;
      case 'u':
        counter[u]++;
        break;
    }
    curr++;
  }
  char vogals[N_VOGALS] = {'a', 'e', 'i', 'o', 'u'};
  for (int i = 0; i < N_VOGALS; i++)
  {
    printf("%c %i\n", vogals[i], counter[i]);
  }
  free(counter);
  free(str);
}
