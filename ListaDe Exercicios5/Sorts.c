#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InsertionSort(int vetorDados[], int numeroDeElementos);
void SelectionSort(int vetorDados[], int numeroDeElementos);
void QuickSort(int vetorDados[], int valorEsq, int valorDir);

int main() {
  int numeroDeElementos, i = 0;
  srand(time(0));

  printf("Informe o numero de elementos do vetor: ");
  scanf("%d", &numeroDeElementos);

  int vetorDados[numeroDeElementos];
  while (i <= numeroDeElementos) {
    vetorDados[i] = rand() % 100;
    i++;
  }

  for (int i = 0; i < numeroDeElementos; i++) {
    printf("[%d]", vetorDados[i]);
  }
  printf("\n");

  SelectionSort(vetorDados, numeroDeElementos);
  //QuickSort(vetorDados, 0, numeroDeElementos);
  //InsertionSort(vetorDados, numeroDeElementos);
  for (int i = 0; i < numeroDeElementos; i++) {
    printf("[%d]", vetorDados[i]);
  }
  return 0;
}

void InsertionSort(int vetorDados[], int numeroDeElementos) {
  int j, chave;
  for (int i = 1; i < numeroDeElementos; i++) {
    chave = vetorDados[i];
    j = i - 1;
    while (j >= 0 && vetorDados[j] > chave) {
      vetorDados[j + 1] = vetorDados[j];
      j--;
    }
    vetorDados[j + 1] = chave;
  }
}

void SelectionSort(int vetorDados[], int numeroDeElementos) {
  int menorValor, temp, indiceMenorValor;

  for (int i = 0; i < numeroDeElementos - 1; i++) {
    menorValor = vetorDados[i];

    for (int j = i + 1; j < numeroDeElementos; j++) {
      if (vetorDados[j] < menorValor) {
        menorValor = vetorDados[j];
        indiceMenorValor = j;
      }
    }

    temp = vetorDados[i];
    vetorDados[i] = vetorDados[indiceMenorValor];
    vetorDados[indiceMenorValor] = temp;
    indiceMenorValor = i + 1;
  }
}

void QuickSort(int vetorDados[], int valorEsq, int valorDir) {
  int pivo, temp;
  int i = valorEsq, j = valorDir;
  pivo = vetorDados[(valorEsq + valorDir) / 2];
  do {
    while (vetorDados[i] < pivo) {
      i++;
    }
    while (vetorDados[j] > pivo) {
      j--;
    }
    if (i <= j) {
      temp = vetorDados[i];
      vetorDados[i] = vetorDados[j];
      vetorDados[j] = temp;
      i++;
      j--;
    }
  } while (i <= j);
  if (valorEsq < j) {
    QuickSort(vetorDados, valorEsq, j);
  }
  if (valorDir > j) {
    QuickSort(vetorDados, i, valorDir);
  }
}
