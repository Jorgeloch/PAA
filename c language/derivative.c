#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
  int coeficiente;
  char variable;
  int expoente;
} monomio;

void derivada (int *coeficiente, int *expoente)
{
  *coeficiente *= *expoente;
  (*expoente)--;
}

int main (void)
{
  int numberOfMonomios;
  scanf("%d", &numberOfMonomios);
  while (numberOfMonomios > 0)
  {
    monomio *monomios = (monomio *) calloc(numberOfMonomios, sizeof(monomio));

    for (int i = 0; i < numberOfMonomios; i++)
    {
      int coeficiente, expoente;
      char variable;
      scanf("%d %c %d", &coeficiente, &variable, &expoente);

      derivada(&coeficiente, &expoente);

      monomios[i].coeficiente = coeficiente;
      monomios[i].variable = variable;
      monomios[i].expoente = expoente;
    }

    printf("f'(%c)=", monomios[0].variable);
    
    int printed = 0;
    
    for (int i = 0; i < numberOfMonomios; i++)
    {
      if (monomios[i].variable != '0')
      {
        if (monomios[i].coeficiente > 0)
        {
          printf("+");
        }
        if (monomios[i].expoente != 0)
        {
          printf("%d%c^%d", monomios[i].coeficiente, monomios[i].variable, monomios[i].expoente);
        }
        else
        {
          printf("%d", monomios[i].coeficiente);
        }
        printed++;
      }
    }

    if (printed == 0)
    {
      printf("0");
    }

    printf("\n");

    scanf("%d", &numberOfMonomios);
  }
}
