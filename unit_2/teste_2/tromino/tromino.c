#include <stdio.h>
#include <stdlib.h>

// posicionamento de um trominó no tabuleiro
typedef struct tPos {
  int i, j;  // a posição da aresta do dominó
  int giro;  // giro = 0 ==> trominó tem a forma |_
         // giro = 1 ==> trominó tem a forma |‾
         // giro = 2 ==> trominó tem a forma _|
         // giro = 3 ==> trominó tem a forma ‾|
         // tromino sem giro é um L.
} posicionamento;

//Resolve o quebra cabeças
//d = dimensão do tabuleiro (um número múltiplo de 2)
//(i,j) = posição onde falta o quadrado do tabuleiro
//Retorna um array contendo os posicionamentos dos trominós no tabuleiro.
posicionamento* resolveTromino(int d, int i, int j) {
// **** COMPLETE AQUI
// **** Se for necessário, defina funções auxiliares
}

int ps[4][2] = {{1, 1},
        {1,-1},
        {-1,1},
        {-1,-1}};

//Coloca o trominó especificado por p na posicao (i,j) do tabuleiro tab
//d é a dimensão do tabuleiro, ou seja, o número de quadrados numa fila (ou coluna)
//Retorna zero se parte ou todo o trominó ficam fora do tabuleiro ou se o trominó
//está sendo colocado encima de parte ou toda uma peça colocada previamente.
int coloca(posicionamento p, int d, int** tab, int i, int j) {
  if ( p.i >= d ||
     p.j >= d ||              
     p.i + ps[p.giro][0] >= d ||
     p.j + ps[p.giro][1] >= d || 
     p.i == i && p.j == j ||
     p.i + ps[p.giro][0] == i && p.j == j ||
     p.i == i && p.j + ps[p.giro][1] == j ||
     tab[p.i][p.j] == 1 ||
     tab[p.i + ps[p.giro][0]][p.j] == 1 ||
     tab[p.i][p.j + ps[p.giro][1]] == 1 )
    return 0;
  else {
    tab[p.i][p.j] = 1;
    tab[p.i + ps[p.giro][0]][p.j] = 1;
    tab[p.i][p.j + ps[p.giro][1]] = 1;
    return 1;
  }
}

//d = dimensão do tabulueiro
//(i,j) = quadrado faltante no tabuleiro
//pos = array com os trominós a ser colocados (com posicao e giro cada um)
//nt = tamanho do array pos 
int verifica(int d, posicionamento* pos, int i, int j) {
  int** tabuleiro = (int**) malloc(d*sizeof(int*));
  for (int i=0; i<d; i++)
    tabuleiro[i] = (int*) calloc(d, sizeof(int));

  int nt = d*d/3; // quantidade de trominós para preencher o tabuleiro
  for (int k=0; k<nt; k++) {
    if (! coloca(pos[k], d, tabuleiro, i, j) ) {
      return 0;
    }
  }
  return 1;
}

//Função auxiliar. Calcula x^n.
int pot(int x, int n) {
  int p = 1;
  for (int i = 0; i<n; i++) {
    p *= x;
  }
  return p;
}

int main(void) {
  for (int k=0; k<10; k++) {
    int n = rand() % 3 + 3;
    int d = pot(2,n);
    int i = rand() % d;
    int j = rand() % d;
    posicionamento* pos = resolveTromino(d, i, j);
    if (! verifica(d, pos, i, j)) {
      printf("NAO");
      exit(1);
    }
  }
  printf("SIM");
}


