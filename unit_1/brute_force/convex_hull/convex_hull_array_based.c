#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  double x;
  double y;
} vertice;

typedef struct {
  vertice v1;
  vertice v2;
} edge;
 
int compare (vertice v1, vertice v2);
void sort (vertice* vertices, int size);
bool exists (vertice* vertices, int size, vertice v);
vertice* convex_hull (vertice* vertices, int size, int* result_size);

int main (void)
{
  int n;
  scanf("%i", &n);
  
  vertice* vertices = (vertice*) malloc(n * sizeof(vertice));

  for (int i = 0; i < n; i++)
  {
    scanf("%lf %lf", &(vertices[i].x), &(vertices[i].y));
  }

  int result_size = 0;
  vertice* result = convex_hull(vertices, n, &result_size);

  sort(result, result_size);

  for (int i = 0; i < result_size; i++)
  {
    printf("%.4lf %.4lf\n", result[i].x, result[i].y);
  }

  free(vertices);
  free(result);
}

int compare(vertice v1, vertice v2)
{
  if (v1.x > v2.x)
  {
    return 1;
  }
  else if (v1.x < v2.x)
  {
    return -1;
  }
  else
  {
    if (v1.y > v2.y)
    {
      return 1;
    }
    else if (v1.y < v2.y)
    {
      return -1;
    }
    else 
    {
      return 0;
    }
  }
}

void sort(vertice* vertices, int size)
{
  for (int i = 0; i < size - 1; i++)
  {
    int min = i;
    for (int j = i + 1; j < size; j++)
    {
      if (compare(vertices[min], vertices[j]) > 0)
      {
        min = j;
      }
    }
    
    vertice aux = vertices[i];
    vertices[i] = vertices[min];
    vertices[min] = aux;
  }
}

bool exists (vertice* vertices, int size, vertice v)
{
  for (int i = 0; i < size; i++)
  {
    if (compare(vertices[i], v) == 0)
    {
      return true;
    }
  }
  return false;
}

vertice* convex_hull (vertice* vertices, int size, int* result_size)
{
  vertice* result = (vertice*) malloc(size * sizeof(edge));
  for (int i = 0; i < size - 1; i++)
  {
    for (int j = i + 1; j < size; j++)
    {
      edge e;
      e.v1 = vertices[i];
      e.v2 = vertices[j];

      double a = e.v2.y - e.v1.y;
      double b = e.v1.x - e.v2.x;
      double c = (e.v1.x * e.v2.y) - (e.v1.y * e.v2.x);
      
      int positive = 0;
      int negative = 0;
      for (int k = 0; k < size; k++)
      {
        if (k != i && k != j)
        {
          double value = (a * vertices[k].x) + (b * vertices[k].y) - c;
          if (value > 0)
          {
            positive += 1;
          }
          else if (value < 0)
          {
            negative += 1;
          }
        }
      }
      if (negative == 0 || positive == 0)
      {
        if (!exists(result, *result_size, e.v1))
        {
          result[*result_size] = e.v1;
          (*result_size)++;
        }
        if (!exists(result, *result_size, e.v2))
        {
          result[*result_size] = e.v2;
          (*result_size)++;
        }
      }
    }
  }
  return result;
}

