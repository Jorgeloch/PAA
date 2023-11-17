#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tamstr (char *str)
{
  char *curr = str;
  while (*curr != '\0')
  {
    curr++;
  }
  int size = curr - str;
  return size;
}

int main (void)
{
  char *input = (char *) malloc(10 * sizeof(char));
  
  while (1)
  {
    scanf("%s", input);
    if (!strcmp(input, "FIM"))
    {
      break;
    }
    printf("%i\n", tamstr(input));
  }

  free(input);
}

