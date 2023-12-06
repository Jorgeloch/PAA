#include <stdio.h>
#include <stdlib.h>
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
  double min_distance = 1500;
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      unsigned int dx = abs(points[i].x - points[j].x);
      unsigned int dy = abs(points[i].y - points[j].y);
      double distance = sqrt((double) ((dx * dx) + (dy * dy)));
      if (distance < min_distance)
      {
        min_distance = distance;
      }
    }
  }
  printf("%.4lf\n", min_distance);
  free(points);
}
