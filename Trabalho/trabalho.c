#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DEFINE VARIAVEIS CADASTRO
#define NOME 0
#define IDADE (sizeof(char) * 11)
#define TELEFONE ((sizeof(char) * 11) + sizeof(int))
#define P_NEXT ((sizeof(char) * 11) + (sizeof(int) * 2))
#define P_PREVIOUS ((sizeof(char) * 11) + (sizeof(int) * 2) + sizeof(void *))

#define CADASTRO ((11 * sizeof(char)) + (2 * sizeof(int)) + (2 * sizeof(void *)))

//DEFINE VARIAVEIS pBuffer
#define N_PESSOAS 0
#define CHOICE (sizeof(int))
#define NOME_BUSCA (sizeof(char) + sizeof(int))
#define P_FIRST (sizeof(char) + sizeof(int) + (sizeof(char) * 10))
#define P_LAST (sizeof(char) + sizeof(int) + (sizeof(char) * 10) + sizeof(void *))
#define ITERATOR (sizeof(char) + sizeof(int) + (sizeof(char) * 10) + (2 * sizeof(void *)))

//FUNÇÕES DECLARADAS
void inserirCadastro(void *pBuffer);
void imprimeNodo(void *ponteiro);
void listar(void *pbuffer);
void limpaFila(void *pBuffer);
void ordenar(void *pBuffer, void *pCadastro);
void removerPrimeiro(void *pBuffer);

int main() {
  void *pBuffer = (void *)malloc(sizeof(int) + sizeof(char) * 11 + sizeof(void *) * 2);
  //[nPessoas][choice][nomeBuscar][pFirst][pLast][iterator]
  if (pBuffer == NULL) {
    printf("Erro de memoria!!\n");
    exit(1);
  }

  *(int *)(pBuffer + N_PESSOAS) = 0;
  char *choice = (pBuffer + CHOICE);

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
      inserirCadastro(pBuffer);
      break;
    case '2':
      removerPrimeiro(pBuffer);
      break;
    case '3':
      buscarNome(pBuffer);
      break;
    case '4':
      listar(pBuffer);
      break;
    case '5':
      limpaFila(pBuffer);
      free(pBuffer);
      exit(0);
    }
  } while (choice != '5');

  return 0;
}

void inserirCadastro(void *pBuffer) {
  int *tamanhoDaLista = &*(int *)(pBuffer + N_PESSOAS);

  void *cadastro = malloc(CADASTRO);
  printf("--INSERINDO CADASTRO--\n");
  printf("Insira um nome: ");
  scanf("%s", ((char *)cadastro + NOME));
  printf("Insira a idade: ");
  scanf("%d", (int *)(cadastro + IDADE));
  printf("Insira um telefone: ");
  scanf("%d", (int *)(cadastro + TELEFONE));

  *(void **)(cadastro + P_NEXT) = NULL;
  *(void **)(cadastro + P_PREVIOUS) = NULL;

  if (*tamanhoDaLista == 0) {
    *(void **)(pBuffer + P_FIRST) = cadastro;
    *(void **)(pBuffer + P_LAST) = cadastro;
  } else {
    ordenar(pBuffer, cadastro);
  }

  *tamanhoDaLista = *tamanhoDaLista + 1;
}

void imprimeNodo(void *ponteiro) {
  printf("\t%s\n", (char *)((char *)ponteiro + NOME));
  printf("\t%d\n", *(int *)(ponteiro + IDADE));
  printf("\t%d\n", *(int *)(ponteiro + TELEFONE));
  printf("----------\n");
}

void buscarNome(void *pBuffer) {
  int *tamanhoDaLista = &*(int *)(pBuffer + N_PESSOAS);
  if (*tamanhoDaLista == 0) {
    printf("Fila vazia!!\n");
  } else {
    char *nomeBuscar = &*(char *)(pBuffer + NOME_BUSCA);
    printf("--BUSCAR--\n");
    printf("Insira o nome: ");
    scanf("%s", nomeBuscar);
    void *cadastro = *(void **)(pBuffer + P_FIRST);

    printf("Buscando");
    while (cadastro != NULL) {
      printf("...\n");
      if (strcmp(nomeBuscar, (char *)(cadastro + NOME)) == 0) {
        imprimeNodo(cadastro);
      }
      cadastro = *(void **)(cadastro + P_NEXT);
    }
    printf("Fim da lista!\n");
  }
}

void listar(void *pBuffer) {
  void *temp = *(void **)(pBuffer + P_FIRST);
  int *tamanhoDaLista = &*(int *)(pBuffer + N_PESSOAS);
  int *i = &*(pBuffer + ITERATOR);
  *i = 1;

  if (*tamanhoDaLista == 0) {
    printf("Fila vazia!!\n");
  } else {
    printf("--FILA--\n");
    while (temp != NULL) {
      printf("%do", *i);
      imprimeNodo(temp);
      temp = *(void **)(temp + P_NEXT);
      *i = *i + 1;
    }
  }
}

void limpaFila(void *pBuffer) {
  void *temp = *(void **)(pBuffer + P_FIRST);
  int *tamanhoDaLista = &*(int *)(pBuffer + N_PESSOAS);
  if (*tamanhoDaLista == 0) {
    printf("Ate mais!!\n");
  } else {
    printf("limpando...\n");

    while (*(void **)(pBuffer + P_FIRST) != NULL) {
      temp = *(void **)(pBuffer + P_FIRST);
      *(void **)(pBuffer + P_FIRST) = *(void **)(temp + P_NEXT);
      free(temp);
      printf("...\n");
    }

    printf("Fila limpa com sucesso!\n");
    printf("Ate mais!!\n");
  }
}

void ordenar(void *pBuffer, void *pCadastro) {
  void *cadastroAux = *(void **)(pBuffer + P_LAST);

  if (strcmp((char *)(cadastroAux + NOME), (char *)(pCadastro + NOME)) <= 0) {

    *(void **)(pCadastro + P_PREVIOUS) = *(void **)(pBuffer + P_LAST);
    cadastroAux = *(void **)(pBuffer + P_LAST);
    *(void **)(pBuffer + P_LAST) = pCadastro;
    *(void **)(cadastroAux + P_NEXT) = pCadastro;
    return;

  } else {
    while (cadastroAux != NULL) {
      if (strcmp((char *)(cadastroAux + NOME), (char *)(pCadastro + NOME)) <= 0) {
        *(void **)(pCadastro + P_NEXT) = *(void **)(cadastroAux + P_NEXT);
        *(void **)(pCadastro + P_PREVIOUS) = cadastroAux;

        void *temp = *(void **)(cadastroAux + P_NEXT);
        *(void **)(temp + P_PREVIOUS) = pCadastro;

        *(void **)(cadastroAux + P_NEXT) = pCadastro;
        return;
      }
      cadastroAux = *(void **)(cadastroAux + P_PREVIOUS);
    }
    printf("ENTROOOO");
    *(void **)(pCadastro + P_NEXT) = *(void **)(pBuffer + P_FIRST);
    cadastroAux = *(void **)(pBuffer + P_FIRST);
    *(void **)(cadastroAux + P_PREVIOUS) = pCadastro;
    *(void **)(pBuffer + P_FIRST) = pCadastro;
  }
}

void removerPrimeiro(void *pBuffer) {
  int *tamanhoDaLista = &*(int *)(pBuffer + N_PESSOAS);
  if (*tamanhoDaLista == 0) {
    printf("Fila vazia!!\n");
    return;
  } else if (*tamanhoDaLista == 1) {
    printf("Removendo...\n");
    void *temp = *(void **)(pBuffer + P_FIRST);
    *(void **)(pBuffer + P_FIRST) = NULL;
    *(void **)(pBuffer + P_LAST) = NULL;
    free(temp);
    *tamanhoDaLista = *tamanhoDaLista - 1;
    return;
  }
  printf("Removendo...\n");
  void *temp = *(void **)(pBuffer + P_FIRST);
  *(void **)(pBuffer + P_FIRST) = *(void **)(temp + P_NEXT);
  free(temp);
  void *aux = *(void **)(pBuffer + P_FIRST);
  *(void **)(aux + P_PREVIOUS) = NULL;
  *tamanhoDaLista = *tamanhoDaLista - 1;
  printf("Primeiro removido com sucesso!\n");
}
