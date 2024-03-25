#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

typedef struct {
  long double x;
  long double y;
} point;

int compareByX (const void* a, const void* b);
int compareByY (const void* a, const void* b);
long double min(long double num1, long double num2);
long double closestPair(point* points, int n);
long double efficientClosestPair(point* points_x, point* points_y, int n);

int main (void)
{
  int n;
  scanf("%i", &n);
  while (n != 0) 
  {
    point* points_x = (point*) malloc(n * sizeof(point));
    point* points_y = (point*) malloc(n * sizeof(point));

    for (int i = 0; i < n; i++)
    {
      scanf("%Lf %Lf", &(points_x[i].x), &(points_x[i].y));
    }
    for (int i = 0; i < n; i++)
    {
      points_y[i] = points_x[i];
    }

    qsort(points_x, n, sizeof(point), compareByX);
    qsort(points_y, n, sizeof(point), compareByY);

    long double result = efficientClosestPair(points_x, points_y, n);
    if (result > 1000) printf("INFINITY\n");
    else printf("%.4Lf\n", result);

    free(points_y);
    free(points_x);
    scanf("%i", &n);
  }
  return 0;
}

int compareByX (const void* a, const void* b)
{
  point arg1 = *(const point*)a;
  point arg2 = *(const point*)b;

  if (arg1.x > arg2.x) return 1;
  else if (arg1.x < arg2.x) return -1;
  else
  {
    if (arg1.y > arg2.y) return 1;
    else if (arg1.y < arg2.y) return -1;
    else return 0;
  }
}

int compareByY (const void* a, const void* b)
{
  point arg1 = *(const point*)a;
  point arg2 = *(const point*)b;

  if (arg1.y > arg2.y) return 1;
  else if (arg1.y < arg2.y) return -1;
  else
  {
    if (arg1.x > arg2.x) return 1;
    else if (arg1.x < arg2.x) return -1;
    else return 0;
  }
}

long double min(long double num1, long double num2)
{
  if (num1 <= num2) return num1;
  else return num2;
}

long double closestPair(point* points, int n)
{
  long double dmin = LDBL_MAX;
  for (int i = 0; i < n - 1; i++) 
  {
    for (int j = i + 1; j < n; j++)
    {
      long double dx = points[i].x - points[j].x;
      long double dy = points[i].y - points[j].y;
      long double distance = (dx * dx) + (dy * dy);
      dmin = min(distance, dmin);
    }
  }
  return sqrtl(dmin);
}

long double efficientClosestPair(point* points_x, point* points_y, int n)
{
  if (n <= 3)
  {
    return closestPair(points_x, n);
  }

  int leftSize = ceil(n / 2.0);
  int rightSize = floor(n / 2.0);

  point* points_x_left = (point*) malloc(leftSize * sizeof(point));
  point* points_x_right = (point*) malloc(rightSize * sizeof(point));

  point* points_y_left = (point*) malloc(leftSize * sizeof(point));
  point* points_y_right = (point*) malloc(rightSize * sizeof(point));

  point medianPoint = points_x[leftSize - 1];

  for (int i = 0; i < leftSize; i++)
  {
    points_x_left[i] = points_x[i];
  }
  for (int i = leftSize; i < n; i++)
  {
    points_x_right[i - leftSize] = points_x[i];
  }

  int numLeft = 0;
  int numRight = 0;

  for (int i = 0; i < n; i++)
  {
    if (numLeft < leftSize && points_y[i].x <= medianPoint.x)
    {
      points_y_left[numLeft++] = points_y[i];
    }
    else if (numRight < rightSize && points_y[i].x >= medianPoint.x)
    {
      points_y_right[numRight++] = points_y[i];
    }
  }

  // printf("\nleftSize: %i\n", leftSize);
  // printf("numLeft: %i\n", numLeft);
  // printf("rightSize: %i\n", rightSize);
  // printf("numRight: %i\n\n", numRight);
  
  long double distanceLeft = efficientClosestPair(points_x_left, points_y_left, leftSize);
  long double distanceRight = efficientClosestPair(points_x_right, points_y_right, rightSize);

  long double minDistance = min(distanceLeft, distanceRight);
  long double median = medianPoint.x;
  long double sqrtDistance = minDistance * minDistance;

  int num = 0;

  point* s = (point*) malloc(n * sizeof(point));
  for (int i = 0; i < n; i++)
  {
    if (fabsl(points_y[i].x - median) < minDistance)
    {
      s[num++] = points_y[i];
    }
  }

  for (int i = 0; i < num - 1; i++)
  {
    int k = i + 1;
    while (k <= num - 1 && (s[k].y - s[i].y)*(s[k].y - s[i].y) < sqrtDistance)
    {
      long double dx = (s[i].x - s[k].x);
      long double dy = (s[i].y - s[k].y);
      sqrtDistance = min((dx*dx) + (dy*dy), sqrtDistance);
      k++;
    }
  }
  
  free(points_y_left);
  free(points_y_right);
  free(points_x_left);
  free(points_x_right);
  free(s);

  return sqrtl(sqrtDistance);
}

