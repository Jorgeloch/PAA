#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  double consumo_medio;
  int n_moradores;
} consumo;

int consumo_existe (double consumo_medio, consumo *consumos, int n_consumos);
double calcula_consumo (consumo *consumo_medio, int n_consumos);
void print_consumos(consumo *consumo_medio, int n_consumos);
void sort(consumo *consumo_medio, int n_consumos);

int main (void)
{
  int n_da_cidade = 1;
  
  int n;
  scanf("%i", &n);
  
  while (n != 0)
  {
    int n_consumos_medios = 0;
    
    consumo *consumos_medios = (consumo *) calloc(n, sizeof(consumo));

    for (int i = 0; i < n; i++)
    {
      double consumo;
      int moradores;

      scanf("%i %lf", &moradores, &consumo);

      double consumo_medio = floor(consumo / moradores);
      int pos = consumo_existe(consumo_medio, consumos_medios, n_consumos_medios);
      if (pos != -1)
      {
        consumos_medios[pos].n_moradores += moradores;
      }
      else
      {
        consumos_medios[n_consumos_medios].n_moradores = moradores;
        consumos_medios[n_consumos_medios].consumo_medio = consumo_medio;
        n_consumos_medios++;
      }
    }

    sort(consumos_medios, n_consumos_medios);

    printf("Cidade#%i\n", n_da_cidade);
    n++;
    print_consumos(consumos_medios, n_consumos_medios);
    printf("Consumo medio: %.2lf m3.\n\n", calcula_consumo(consumos_medios, n_consumos_medios));
    free(consumos_medios);
    scanf("%i", &n);
  }
  return 0;
}

int consumo_existe (double consumo_medio, consumo *consumos, int n_consumos)
{
  for (int i = 0; i < n_consumos; i++)
  {
    if (consumos[i].consumo_medio == consumo_medio)
    {
      return i;
    }
  }
  return -1;
}

double calcula_consumo (consumo *consumo_medio, int n_consumos)
{
  double total_consumo = 0;
  int total_moradores = 0;
  for (int i = 0; i < n_consumos; i++)
  {
    total_consumo += consumo_medio[i].consumo_medio * consumo_medio[i].n_moradores;
    total_moradores += consumo_medio[i].n_moradores;
  }
  return floor (total_consumo / total_moradores);
}

void print_consumos(consumo *consumo_medio, int n_consumos)
{
  for (int i = 0; i < n_consumos - 1; i++)
  {
    printf("%i-%i ", (int) consumo_medio[i].n_moradores, (int) consumo_medio[i].consumo_medio);
  }
  printf("%i-%i", (int) consumo_medio[n_consumos - 1].n_moradores, (int) consumo_medio[n_consumos - 1].consumo_medio);
  printf("\n");
}

void sort(consumo *consumo_medio, int n_consumos)
{
  for (int i = 0; i < n_consumos - 1; i++)
  {
    int pos = i;
    double consumo_minimo = consumo_medio[i].consumo_medio;
    for (int j = i; j < n_consumos; j++)
    {
      if (consumo_medio[j].consumo_medio < consumo_minimo)
      {
        pos = j;
        consumo_minimo = consumo_medio[j].consumo_medio;
      }
    }
    consumo aux = consumo_medio[pos];
    consumo_medio[pos] = consumo_medio[i];
    consumo_medio[i] = aux;
  }
}
