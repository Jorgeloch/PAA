#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
  char* word;
  char* ordered_word;
  int size;
  bool matched;
} data;

data* init_data(void);
int compare(const void* a, const void* b);
int compare_data(const void* a, const void* b);
void free_data(data** input, int size);

int main(void)
{
  int n;
  scanf("%i", &n);
  
  data** inputs = (data**) calloc(n, sizeof(data*));
  if (!inputs)
  {
    printf("unable to allocate array of inputs\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++)
  {
    inputs[i] = init_data();
    scanf("%s", inputs[i]->word);
    strcpy(inputs[i]->ordered_word, inputs[i]->word);
    inputs[i]->size = strlen(inputs[i]->word);
    qsort(inputs[i]->ordered_word, inputs[i]->size, sizeof(char), compare);
  }

  qsort(inputs, n, sizeof(data*), compare_data);

  for (int i = 0; i < n - 1; i++)
  {
    if (!inputs[i]->matched)
    {
      inputs[i]->matched = true;
      printf("%s", inputs[i]->word);
      for (int j = i + 1; j < n; j++)
      {
        if (!inputs[j]->matched)
        {
          if (!strcmp(inputs[i]->ordered_word, inputs[j]->ordered_word))
          {
            inputs[j]->matched = true;
            printf(" %s", inputs[j]->word);
          }
        }
      }
      printf("\n");
    }
  }

  free_data(inputs, n);
  free(inputs);
  return 0;
}

data* init_data(void)
{
  data* result = (data*) calloc(1, sizeof(data));
  result->word = (char*) calloc(20, sizeof(char));
  result->ordered_word = (char*) calloc(20, sizeof(char));
  if (!result || !result->word || !result->ordered_word)
  {
    printf("unable to allocate instance of input\n");
    exit(EXIT_FAILURE);
  }
  return result;
}

int compare (const void* a, const void* b)
{
  char x = *(const char*) a;
  char y = *(const char*) b;

  if (x > y)
    return 1;
  else if (x < y)
    return -1;
  else 
    return 0;
}

int compare_data (const void* a, const void* b)
{
  return strcmp((*(const data**)a)->word, (*(const data**)b)->word);
}

void free_data(data** input, int size)
{
  for (int i = 0; i < size; i++)
  {
    free(input[i]->word);
    free(input[i]->ordered_word);
    free(input[i]);
  }
}

