#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct coordinates {
  int x;
  int y;
} coordinates;

int main (void)
{
  int n;
  scanf("%i", &n);
  coordinates* points = (coordinates*) malloc(n * sizeof(coordinates));
  for (int i = 0; i < n; i++)
  {
    scanf("%i %i", &(points[i].x), &(points[i].y)); 
  }
  long int min_distance = LONG_MAX;
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      int dx = points[i].x - points[j].x;
      int dy = points[i].y - points[j].y;
      long int distance = (dx * dx) + (dy * dy);
      if (distance < min_distance)
      {
        min_distance = distance;
      }
    }
  }
  double result = sqrt((double) min_distance);
  printf("%.4lf\n", result);
  free(points);
}
