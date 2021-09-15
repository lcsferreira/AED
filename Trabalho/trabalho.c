#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_NOME (11 * sizeof(char))
#define TAMANHO_IDADE (1 * sizeof(int))
#define TAMANHO_TELEFONE (1 * sizeof(int))
#define TAMANHO_CADASTRO ((11 * sizeof(char)) + (2 * sizeof(int)))

void InserirCadastro(void *pBuffer);
// void imprimeNodo(void *ponteiro);
void listar(void *pbuffer);

int main() {
  void *pBuffer = (void *)malloc(sizeof(int) + sizeof(char) + sizeof(void *) * 2);
  //[nPessoas][choice][pFirst][pLast]
  if (pBuffer == NULL) {
    printf("Erro de memoria!!\n");
    exit(1);
  }

  *(int *)(pBuffer) = 0;
  char *choice = (pBuffer + sizeof(int));

  do {
    printf("-- MENU:\n");
    printf("\t 1. Inserir um cadastro\n");
    printf("\t 2. Excluir um cadastro\n");
    printf("\t 3. Procurar um cadastro\n");
    printf("\t 4. Listar\n");
    printf("\t 5. Sair\n");
    printf("-- Digite sua escolha: ");
    scanf(" %c", choice);
    getchar(); //limpa o buffer do teclado

    switch (*choice) {
    case '1':
      InserirCadastro(pBuffer);
      //inserir
      break;
    case '2':
      //remover
      break;
    case '3':
      //procurar
      break;
    case '4':
      listar(pBuffer);
      break;
    case '5':
      //sair
      free(pBuffer);
      exit(0);
    }
  } while (choice != '5');

  return 0;
}

void InserirCadastro(void *pBuffer) {
  int *tamanhoDaLista = &*(int *)pBuffer;

  void *cadastro = malloc(TAMANHO_CADASTRO + sizeof(void *));

  printf("Insira um nome: ");
  scanf("%s", ((char *)cadastro));
  printf("Insira a idade: ");
  scanf("%d", (int *)(cadastro + TAMANHO_NOME));
  printf("Insira um telefone: ");
  scanf("%d", (int *)(cadastro + TAMANHO_NOME + TAMANHO_IDADE));

  *(void **)(cadastro + TAMANHO_NOME + TAMANHO_IDADE + TAMANHO_TELEFONE) = NULL;

  if (*tamanhoDaLista == 0) {
    *(void **)(pBuffer + sizeof(int) + sizeof(char)) = cadastro;
    *(void **)(pBuffer + sizeof(int) + sizeof(char) + sizeof(void *)) = cadastro;
  } else {
    void *ultimaPessoaAtual = *(void **)(pBuffer + sizeof(int) + sizeof(char) + sizeof(void *));
    *(void **)(ultimaPessoaAtual + TAMANHO_NOME + TAMANHO_IDADE + TAMANHO_TELEFONE) = cadastro;
    *(void **)(pBuffer + sizeof(int) + sizeof(char) + sizeof(void *)) = cadastro;
  }

  *tamanhoDaLista = *tamanhoDaLista + 1;
}

void imprimeNodo(void *ponteiro) {
  printf("%s\n", (char *)((char *)ponteiro));
  printf("%d\n", *(int *)(ponteiro + TAMANHO_NOME));
  printf("%d\n", *(int *)(ponteiro + TAMANHO_NOME + TAMANHO_IDADE));
  printf("----------\n");
}

void listar(void *pBuffer) {
  void *temp = *(void **)(pBuffer + sizeof(int) + sizeof(char));
  printf("--LISTA--\n");
  while (temp != NULL) {
    imprimeNodo(temp);
    temp = *(void **)(temp + TAMANHO_NOME + TAMANHO_IDADE + TAMANHO_TELEFONE);
  }
}