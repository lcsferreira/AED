#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InsertionSort(int vetorDados[], int numeroDeElementos);
void SelectionSort(int vetorDados[], int numeroDeElementos);
void QuickSort(int vetorDados[], int valorEsq, int valorDir);
void MergeSort(int vetorDados[], int numeroDeElementos);
void Sort(int vetorDados[], int *vetorAux[], int esq, int dir);
void Merge(int vetorDados[], int *vetorAux[], int esq, int meio, int dir);

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

  //SelectionSort(vetorDados, numeroDeElementos);
  MergeSort(vetorDados, numeroDeElementos);
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

void MergeSort(int vetorDados[], int numeroDeElementos) {
  int *vetorAux = malloc(sizeof(int) * numeroDeElementos);
  Sort(vetorDados, vetorAux, 0, numeroDeElementos - 1);
  free(vetorAux);
}

void Sort(int vetorDados[], int *vetorAux[], int esq, int dir) {
  if (esq >= dir) {
    return;
  }

  int meio = (esq + dir) / 2;

  Sort(vetorDados, vetorAux, esq, meio);
  Sort(vetorDados, vetorAux, meio + 1, dir);

  if (vetorDados[meio] <= vetorDados[meio + 1]) {
    return;
  }
  Merge(vetorDados, vetorAux, esq, meio, dir);
}

void Merge(int vetorDados[], int *vetorAux[], int esq, int meio, int dir) {
  int indiceAux, inicioVetorDados = esq, inicioVetorAux = meio + 1;

  for (indiceAux = esq; indiceAux <= dir; indiceAux++) {
    vetorAux[indiceAux] = vetorDados[indiceAux];
  }
  indiceAux = esq;
  while (inicioVetorDados <= meio && inicioVetorAux <= dir) {
    /* Invariante: v[i..z] possui os valores de v[iv..m] e v[ic..f] em ordem crescente. */
    if (vetorAux[inicioVetorDados] <= vetorAux[inicioVetorAux])
      vetorDados[indiceAux++] = vetorAux[inicioVetorDados++];
    else
      vetorDados[indiceAux++] = vetorAux[inicioVetorAux++];
  }

  while (inicioVetorDados <= meio)
    vetorDados[indiceAux++] = vetorAux[inicioVetorDados++];

  while (inicioVetorAux <= dir) {
    vetorDados[indiceAux++] = vetorAux[inicioVetorAux++];
  }
}