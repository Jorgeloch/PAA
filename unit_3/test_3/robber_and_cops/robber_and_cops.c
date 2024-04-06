#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_MATRIX_SIZE 5
#define MAX_QUEUE_SIZE 25

typedef struct {
  int row;
  int column;
} coordinate;

typedef struct {
  int start;
  int finish;
  int size;
  coordinate queue[MAX_QUEUE_SIZE];
} queue;

typedef enum {
  CAMINHO,
  BARREIRA,
  MARCADO,
  VISITADO,
} status;

queue *initializequeue(int n) {
  queue *result = (queue *)calloc(1, sizeof(queue));
  result->start = 0;
  result->finish = -1;
  result->size = 0;
  return result;
}

bool isFull(queue *q) { return q->size == MAX_QUEUE_SIZE; }

bool isEmpty(queue *q) { return q->size == 0; }

void enqueue(queue *q, int row, int column) {
  if (isFull(q)) {
    printf("impossivel inserir na fila, fila cheia\n");
    exit(EXIT_FAILURE);
  }

  coordinate c;
  c.row = row;
  c.column = column;

  q->finish = (q->finish + 1) % MAX_QUEUE_SIZE;
  q->queue[q->finish] = c;
  q->size++;
}

coordinate dequeue(queue *q) {
  if (isEmpty(q)) {
    printf("impossivel dar pop, queue vazia\n");
    exit(EXIT_FAILURE);
  }

  coordinate result = q->queue[q->start];

  q->start = (q->start + 1) % MAX_QUEUE_SIZE;
  q->size--;

  return result;
}

void initializeMatrix(status **matrix) {
  for (int i = 0; i < MAX_MATRIX_SIZE; i++) {
    scanf("%i %i %i %i %i", &matrix[i][0], &matrix[i][1], &matrix[i][2],
          &matrix[i][3], &matrix[i][4]);
  }
}

bool hasPath(status **matrix) {
  queue *q = initializequeue(25);

  enqueue(q, 0, 0);

  while (!isEmpty(q)) {
    coordinate cur = q->queue[q->start];

    int next_row = cur.row + 1;
    int next_col = cur.column + 1;

    int prev_row = cur.row - 1;
    int prev_col = cur.column - 1;

    if (cur.row == 4 && cur.column == 4) {
      // achou o alvo
      return true;
    }

    if (next_row < MAX_MATRIX_SIZE && matrix[next_row][cur.column] == CAMINHO) {
      enqueue(q, next_row, cur.column);
      matrix[next_row][cur.column] = MARCADO;
    }
    if (next_col < MAX_MATRIX_SIZE && matrix[cur.row][next_col] == CAMINHO) {
      enqueue(q, cur.row, next_col);
      matrix[cur.row][next_col] = MARCADO;
    }

    if (prev_row > -1 && matrix[prev_row][cur.column] == CAMINHO) {
      enqueue(q, prev_row, cur.column);
      matrix[prev_row][cur.column] = MARCADO;
    }
    if (prev_col > -1 && matrix[cur.row][prev_col] == CAMINHO) {
      enqueue(q, cur.row, prev_col);
      matrix[cur.row][prev_col] = MARCADO;
    }

    matrix[cur.row][cur.column] = VISITADO;
    dequeue(q);
  }

  return false;
}

int main(void) {
  int n;
  scanf("%i", &n);

  status **matrix = (status **)malloc(MAX_MATRIX_SIZE * sizeof(status *));

  for (int i = 0; i < MAX_MATRIX_SIZE; i++) {
    matrix[i] = (status *)calloc(MAX_MATRIX_SIZE, sizeof(status));
  }

  for (int i = 0; i < n; i++) {
    initializeMatrix(matrix);
    if (hasPath(matrix))
      printf("COPS\n");
    else
      printf("ROBBERS\n");
  }

  for (int i = 0; i < MAX_MATRIX_SIZE; i++) {
    free(matrix[i]);
  }
  free(matrix);

  return 0;
}
