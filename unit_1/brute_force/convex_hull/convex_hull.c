#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  double x;
  double y;
} coordinate;

typedef struct {
  coordinate p1;
  coordinate p2;
} edge;

typedef struct node {
  coordinate p;
  struct node* next;
} node;

typedef struct {
  int size;
  node* start;
} linked_list;

linked_list* create_list();
linked_list* convex_hull (coordinate* points, int n);
node* create_node(coordinate value);
void insert(linked_list* list, coordinate value);
bool is_in_list(linked_list* list, coordinate value);

int main (void)
{
  int n;
  scanf("%i", &n);
  coordinate* points = (coordinate*) malloc(n * sizeof(coordinate));
  for (int i = 0; i < n; i++)
  {
    scanf("%lf %lf", &(points[i].x), &(points[i].y));
  }
  linked_list* convex = convex_hull(points, n);
  node* curr = convex->start;
  while (curr != NULL)
  {
    printf("%.4lf %.4lf\n", curr->p.x, curr->p.y);
    curr = curr->next;
  }
  curr = convex->start;
  while (curr != NULL)
  {
    node* aux = curr;
    curr = curr->next;
    free(aux);
  }
  free(convex);
  free(points);
  return 0;
}

linked_list* create_list()
{
  linked_list* new = (linked_list*) malloc(sizeof(linked_list));
  if (!new)
  {
    printf("could not allocate linked list\n");
    exit(EXIT_FAILURE);
  }
  new->start = NULL;
  new->size = 0;
  return new;
}

node* create_node(coordinate value)
{
  node* new = (node*) malloc(sizeof(node));
  if (!new)
  {
    printf("could not allocate node\n");
    exit(EXIT_FAILURE);
  }
  new->p = value;
  new->next = NULL;
  return new;
}

void insert(linked_list* list, coordinate value)
{
  node* new = create_node(value);
  if (list->size == 0)
  {
    list->start = new;
    list->size = 1;
    return;
  }
  node* curr = list->start;
  while (curr->p.x < value.x && curr->next != NULL)
  {
    curr = curr->next;
  }
  while (curr->p.x > value.x && curr->p.y < value.y && curr->next != NULL)
  {
    curr = curr->next;
  }
  new->next = curr->next;
  curr->next = new;
  list->size++;
  return;
}

bool is_in_list(linked_list* list, coordinate value)
{
  node* curr = list->start;
  while (curr != NULL)
  {
    if (curr->p.x == value.x && curr->p.y == value.y)
    {
      return true;
    }
    curr = curr->next;
  }
  return false;
}

linked_list* convex_hull (coordinate* points, int n)
{
  linked_list* vertices = create_list();
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      edge e;
      e.p1 = points[i];
      e.p2 = points[j];

      double a = e.p2.y - e.p1.y;
      double b = e.p1.x - e.p2.x;
      double c = (e.p1.x * e.p2.y) - (e.p1.y * e.p2.x);
      
      int positive = 0;
      int negative = 0;

      for (int k = 0; k < n; k++)
      {
        if (k != i && k != j)
        {
          double value = (a * points[k].x) + (b * points[k].y) - c;
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
        if (!is_in_list(vertices, e.p1))
        {
          insert(vertices, e.p1);
        }
        if (!is_in_list(vertices, e.p2))
        {
          insert(vertices, e.p2);
        }
      }
    }
  }
  return vertices;
}
 
