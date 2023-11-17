#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void reduz (float *x, float *y)
{
    *x -= *y;
}

int main() {
    float x, y;
    scanf("%f %f", &x, &y);
    reduz(&x, &y);
    printf("%.2f %.2f\n", x, y);
  	return 0;
}
