#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ImprimeVetor(int vetorDados[], int numeroDeElementos);
void VerificaOrdem(int vetorDados[], int numeroDeElementos);
void EscolhaAlgoritmo(int escolha, int vetorDados[], int numeroDeElementos);
void PreencheVetor(int vetorDados[], int numeroDeElementos);
void InsertionSort(int vetorDados[], int numeroDeElementos);
void SelectionSort(int vetorDados[], int numeroDeElementos);
void QuickSort(int vetorDados[], int valorEsq, int valorDir);
void MergeSort(int vetorDados[], int tamanho, int esq, int dir);
void Merge(int vetorDados[], int tamanho, int esq, int meio, int dir);

int main() {
  int numeroDeElementos, escolha;
  srand(time(0));

  printf("Informe o numero de elementos do vetor: ");
  scanf("%d", &numeroDeElementos);

  int vetorDados[numeroDeElementos];

  PreencheVetor(vetorDados, numeroDeElementos);

  ImprimeVetor(vetorDados, numeroDeElementos);

  printf("Escolha o algoritmo de ordenacao: \n");
  printf("\t1. Insertion\n\t2. Selection\n\t3. Quick\n\t4. Merge\n");
  scanf("%d", &escolha);

  EscolhaAlgoritmo(escolha, vetorDados, numeroDeElementos);

  VerificaOrdem(vetorDados, numeroDeElementos);
  ImprimeVetor(vetorDados, numeroDeElementos);
  return 0;
}

void InsertionSort(int vetorDados[], int numeroDeElementos) {
  int indiceAux, temp;
  for (int i = 1; i < numeroDeElementos; i++) {
    temp = vetorDados[i];
    indiceAux = i - 1;
    while (indiceAux >= 0 && vetorDados[indiceAux] > temp) {
      vetorDados[indiceAux + 1] = vetorDados[indiceAux];
      indiceAux--;
    }
    vetorDados[indiceAux + 1] = temp;
  }
}

void SelectionSort(int vetorDados[], int numeroDeElementos) {
  int menorValor, temp, indiceMenorValor;

  for (int i = 0; i <= numeroDeElementos; i++) {
    indiceMenorValor = i;
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
  }
}

void QuickSort(int vetorDados[], int valorEsq, int valorDir) {
  int pivo, temp;
  int i = valorEsq, j = valorDir;
  pivo = vetorDados[(valorEsq + valorDir) / 2];

  do {
    while (vetorDados[i] < pivo) { //buscando o maior
      i++;
    }
    while (vetorDados[j] > pivo) { //buscando o menor
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

void MergeSort(int vetorDados[], int tamanho, int esq, int dir) {
  if (esq >= dir) {
    return;
  }

  int meio = (esq + dir) / 2;

  MergeSort(vetorDados, tamanho, esq, meio);     //chama recursivamente para dividir o vetor
  MergeSort(vetorDados, tamanho, meio + 1, dir); //chama recursivamente para dividir o vetor

  if (vetorDados[meio] <= vetorDados[meio + 1]) { //se já estiver ordenado
    return;
  }
  Merge(vetorDados, tamanho, esq, meio, dir); //merge de todas as partes
}

void Merge(int vetorDados[], int tamanho, int esq, int meio, int dir) {
  int indiceAux = esq, inicioVetorDados = esq, indiceProxMeio = meio + 1;
  int vetorAux[tamanho];

  for (int i = esq; i <= dir; i++) { //copio o vetor original para um auxiliar
    vetorAux[i] = vetorDados[i];
  }

  while (inicioVetorDados <= meio && indiceProxMeio <= dir) {
    if (vetorAux[inicioVetorDados] <= vetorAux[indiceProxMeio]) {
      vetorDados[indiceAux] = vetorAux[inicioVetorDados];
      indiceAux++;
      inicioVetorDados++;
    } else {
      vetorDados[indiceAux] = vetorAux[indiceProxMeio];
      indiceAux++;
      indiceProxMeio++;
    }
  }

  while (inicioVetorDados <= meio) {
    vetorDados[indiceAux] = vetorAux[inicioVetorDados];
    indiceAux++;
    inicioVetorDados++;
  }

  while (indiceProxMeio <= dir) {
    vetorDados[indiceAux] = vetorAux[indiceProxMeio];
    indiceAux++;
    indiceProxMeio++;
  }
}

void PreencheVetor(int vetorDados[], int numeroDeElementos) {
  int i = 0;
  while (i <= numeroDeElementos) {
    vetorDados[i] = rand() % 100;
    i++;
  }
}

void EscolhaAlgoritmo(int escolha, int vetorDados[], int numeroDeElementos) {
  switch (escolha) {
  case 1:
    printf("\tInsertion\n");
    InsertionSort(vetorDados, numeroDeElementos);
    break;
  case 2:
    printf("\tSelection\n");
    SelectionSort(vetorDados, numeroDeElementos);
    break;
  case 3:
    printf("\tQuick\n");
    QuickSort(vetorDados, 0, numeroDeElementos - 1);
    break;
  case 4:
    printf("\tMerge\n");
    MergeSort(vetorDados, numeroDeElementos, 0, numeroDeElementos - 1);
    break;
  default:
    printf("Algoritmo invalido!!\n");
    break;
  }
}

void ImprimeVetor(int vetorDados[], int numeroDeElementos) {
  for (int i = 0; i < numeroDeElementos; i++) {
    printf("[%d]", vetorDados[i]);
  }
  printf("\n");
}

void VerificaOrdem(int vetorDados[], int numeroDeElementos) {
  for (int i = 0; i < numeroDeElementos - 1; i++) {
    if (vetorDados[i] > vetorDados[i + 1]) {
      printf("NAO esta ORDENADO!!\n");
      return;
    }
  }
  printf("ORDENADO com SUCESSO\n");
  return;
}