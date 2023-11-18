#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct factor {
  int value;
  int times;
} factor;

int *sieve (int n, int *size);
int min (int x, int y);
int compare_factors (factor *factors_of_m, factor *factors_of_n, int size_m, int size_n);
factor *check_primes (int n, int size_of_primes, int *primes);

int main (void)
{
  int m, n;

  printf("m: ");
  scanf("%i", &m);

  printf("n: ");
  scanf("%i", &n);
  
  // find the primes of m
  int size_m = 0;
  int *primes_to_m = sieve(m, &size_m);
  
  printf("size_m: %i\n", size_m);
  printf("primes_to_m: ");
  for (int i = 0; i < size_m; i++)
  {
    printf("%i ", primes_to_m[i]);
  }
  printf("\n");
  
  // find the primes of n
  int size_n = 0;
  int *primes_to_n = sieve(n, &size_n);
  
  printf("size_n: %i\n",size_n);
  printf("primes_to_n: ");
  for (int i = 0; i < size_n; i++)
  {
    printf("%i ", primes_to_n[i]);
  }
  printf("\n");
  
  // check the prime factors of m
  factor *factors_of_m = check_primes(m, size_m, primes_to_m);
  printf("m = ");
  for (int i = 0; i < size_m; i++)
  {
    printf("%i^%i x ", factors_of_m[i].value, factors_of_m[i].times);
  }
  printf("\b \b \n");
  // check the prime factors of n
  factor *factors_of_n = check_primes(n, size_n, primes_to_n);
  printf("n = ");
  for (int i = 0; i < size_n; i++)
  {
    printf("%i^%i x ", factors_of_n[i].value, factors_of_n[i].times);
  }
  printf("\b \b \n");
  // compare the prime factors of both
  int mdc = compare_factors(factors_of_m, factors_of_n, size_m, size_n);
  printf("mdc(%i, %i) = %i\n", m, n, mdc);
  // compute mdc
  free(primes_to_m);
  free(primes_to_n);
}

int *sieve (int n, int *size)
{
  int array[n - 1];

  for (int i = 2; i <= n; i++)
  {
    array[i - 2] = i;
  }

  for (int i = 2; i <= floor(sqrt((double) n)); i++)
  {
    if (array[i - 2] != 0)
    {
      int j = i * i;
      while (j <= n)
      {
        array[j - 2] = 0;
        j += i;
      }
    }
  }

  for (int i = 0; i < n - 1; i++)
  {
    if (array[i] != 0)
    {
      (*size)++;
    }
  }

  int i = 0;
  
  int *primes = (int *) malloc((*size) * sizeof(int));
  
  for (int j = 0; j < n - 1; j++)
  {
    if (array[j] != 0)
    {
      primes[i] = array[j];
      i++;
    }
  }
  
  return primes;
}

factor *check_primes (int n, int size_of_primes, int *primes)
{
  factor *factors = (factor *) malloc(size_of_primes * sizeof(factor));

  for (int i = 0; i < size_of_primes; i++) 
  {
    factors[i].value = primes[i];
    int count = 0;
    while (n >= primes[i] && n % primes[i] == 0)
    {
      n /= primes[i];
      count++;
    }
    factors[i].times = count;
  }
  return factors;
}

int compare_factors (factor *factors_of_m, factor *factors_of_n, int size_m, int size_n)
{
  int smaller = min(size_m, size_n);
  int result = 1;
  for (int i = 0; i < smaller; i++)
  {
    if (factors_of_m[i].times != 0 && factors_of_n[i].times != 0)
    {
      int expoent = min(factors_of_m[i].times, factors_of_n[i].times);
      result *= (int) powf((float) factors_of_n[i].value, (float) expoent);
    }
  }
  return result;
}

int min (int x, int y)
{
  if (x > y)
  {
    return y;
  }
  return x;
}
