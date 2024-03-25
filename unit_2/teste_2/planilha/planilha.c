#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *nome;
  char *sobrenome;
  int idade;
  char sexo;
  int matricula;
} Aluno;

Aluno *sortByAge(Aluno *alunos, int size, int lower, int upper);
Aluno *sortByGender(Aluno *alunos, int size);

int main(void) {
  int size;
  scanf("%i", &size);

  Aluno *alunos = (Aluno *)malloc(size * sizeof(Aluno));

  for (int i = 0; i < size; i++) {
    alunos[i].nome = (char *)calloc(16, sizeof(char));
    alunos[i].sobrenome = (char *)calloc(16, sizeof(char));
    scanf("%15s %15s %i %c %i", alunos[i].nome, alunos[i].sobrenome,
          &alunos[i].idade, &alunos[i].sexo, &alunos[i].matricula);
  }

  Aluno *sorted = sortByAge(alunos, size, 10, 120);

  for (int i = 0; i < size; i++) {
    printf("%s %s %i %c %i\n", sorted[i].nome, sorted[i].sobrenome,
           sorted[i].idade, sorted[i].sexo, sorted[i].matricula);
  }

  printf("#\n");

  Aluno *sorted1 = sortByGender(sorted, size);
  Aluno *sorted2 = sortByAge(sorted1, size, 10, 120);

  for (int i = 0; i < size; i++) {
    printf("%s %s %i %c %i\n", sorted2[i].nome, sorted2[i].sobrenome,
           sorted2[i].idade, sorted2[i].sexo, sorted2[i].matricula);
  }

  free(sorted);
  free(sorted1);
  free(sorted2);
  for (int i = 0; i < size; i++) {
    free(alunos[i].nome);
    free(alunos[i].sobrenome);
  }
  free(alunos);
  return 0;
}

Aluno *sortByAge(Aluno *alunos, int size, int lower, int upper) {
  int *count = (int *)calloc(upper - lower + 1, sizeof(int));
  Aluno *sortedAlunos = (Aluno *)malloc(size * sizeof(Aluno));

  for (int i = 0; i < size; i++) {
    count[alunos[i].idade - lower] = count[alunos[i].idade - lower] + 1;
  }
  for (int i = 1; i < upper - lower; i++) {
    count[i] = count[i - 1] + count[i];
  }
  for (int i = size - 1; i >= 0; i--) {
    int j = alunos[i].idade - lower;
    sortedAlunos[--count[j]] = alunos[i];
  }

  free(count);
  return sortedAlunos;
}

Aluno *sortByGender(Aluno *alunos, int size) {
  int *count = (int *)calloc(2, sizeof(int));
  Aluno *sortedAlunos = (Aluno *)malloc(size * sizeof(Aluno));

  for (int i = 0; i < size; i++) {
    if (alunos[i].sexo == 'F')
      count[0] += 1;
    else
      count[1] += 1;
  }
  count[1] += count[0];
  for (int i = size - 1; i >= 0; i--) {
    if (alunos[i].sexo == 'F') {
      sortedAlunos[--count[0]] = alunos[i];
    } else {
      sortedAlunos[--count[1]] = alunos[i];
    }
  }

  free(count);
  return sortedAlunos;
}
