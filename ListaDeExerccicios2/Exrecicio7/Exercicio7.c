#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nome[30];
  int idade;
  int altura;
} Pessoa;

Pessoa pessoas[10];

void *InserirCadastro(void *pBuffer);
void Listar(void *pBuffer);
void BuscarNome(void *pBuffer);
void *ExcluirCadastro(void *pBuffer);

int main() {
  void *pBuffer;
  pBuffer = malloc(sizeof(int) * 2 + sizeof(char) * 11);
  //[tamanhoDaLista][choice][i][nomeBusca]
  //[int][char][int][char(tam_x)]
  if (pBuffer == NULL) {
    printf("Erro de memoria!!\n");
    exit(1);
  }
  *(int *)pBuffer = 0;
  char *choice = (pBuffer + sizeof(int));

  do {
    printf("-- MENU:\n");
    printf("\t 1. Inserir um nome\n");
    printf("\t 2. Excluir um nome\n");
    printf("\t 3. Procurar o nome\n");
    printf("\t 4. Listar\n");
    printf("\t 5. Sair\n");
    printf("-- Digite sua escolha: ");
    scanf(" %c", choice);
    getchar(); //limpa o buffer do teclado

    switch (*choice) {
    case '1':
      pBuffer = InserirCadastro(pBuffer);
      break;
    case '2':
      pBuffer = ExcluirCadastro(pBuffer);
      break;
    case '3':
      BuscarNome(pBuffer);
      break;
    case '4':
      Listar(pBuffer);
      break;
    case '5':
      free(pBuffer);
      exit(0);
    }
  } while (*choice != '5');
  return 0;
}
//pessoas[0]//pessoas[1]
void *InserirCadastro(void *pBuffer) {
  int *tamanhoDaLista = pBuffer;
  if (*tamanhoDaLista == 10) {
    printf("Lista cheia!!");
    return pBuffer;
  }
  printf("Digite o nome: ");
  scanf("%s", pessoas[*tamanhoDaLista].nome);
  getchar();
  printf("Insira a idade: ");
  scanf("%d", &pessoas[*tamanhoDaLista].idade);
  printf("Insira a altura: ");
  scanf("%d", &pessoas[*tamanhoDaLista].altura);

  *tamanhoDaLista = *tamanhoDaLista + 1;
  return pBuffer;
}

void Listar(void *pBuffer) {
  int *tamanhoDaLista = pBuffer;
  if (*tamanhoDaLista == 0) {
    printf("Lista vazia!!\n");
    return;
  }

  int *i = (pBuffer + sizeof(int) + sizeof(char));

  for (*i = 0; *i < *tamanhoDaLista; *i = *i + 1) {
    printf("%s\n", pessoas[*i].nome);
    printf("%d anos\n", pessoas[*i].idade);
    printf("%d cm\n", pessoas[*i].altura);
    printf("------------\n");
  }
}

void BuscarNome(void *pBuffer) {
  int *tamanhoDaLista = pBuffer;
  if (*tamanhoDaLista == 0) {
    printf("Lista vazia!!\n");
    return;
  }

  char *nomeBusca = (pBuffer + sizeof(int) + sizeof(char) + sizeof(int));
  printf("Insira o nome para buscar: ");
  scanf("%s", nomeBusca);

  int *i = (pBuffer + sizeof(int) + sizeof(char));
  for (*i = 0; *i < *tamanhoDaLista; *i = *i + 1) {
    if (strcmp(pessoas[*i].nome, nomeBusca) == 0) {
      printf("%s\n", pessoas[*i].nome);
      printf("%d anos\n", pessoas[*i].idade);
      printf("%d cm\n", pessoas[*i].altura);
      return;
    }
  }
  printf("Nome nao encontrado!!\n");
}

void *ExcluirCadastro(void *pBuffer) {
  int *tamanhoDaLista = pBuffer;
  if (*tamanhoDaLista == 0) {
    printf("Nao eh possivel remover!!!\n");
    printf("Lista vazia!!\n");
    return pBuffer;
  }
  char *nomeBusca = (pBuffer + sizeof(int) + sizeof(char) + sizeof(int));
  printf("Insira o nome para excluir: ");
  scanf("%s", nomeBusca);

  int *i = (pBuffer + sizeof(int) + sizeof(char));
  for (*i = 0; *i < *tamanhoDaLista; *i = *i + 1) {
    if (strcmp(pessoas[*i].nome, nomeBusca) == 0) {
      for (*i = *i; *i < *tamanhoDaLista - 1; *i = *i + 1) {
        pessoas[*i] = pessoas[*i + 1];
      }
      *tamanhoDaLista = *tamanhoDaLista - 1;
      return pBuffer;
    }
  }
  printf("Nao foi encontrado o nome!!\n");
  return pBuffer;
}