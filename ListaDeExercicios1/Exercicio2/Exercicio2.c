#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(void);
void listar(char *ListaNomes, int qtdNomes);

int main() {
  int escolha, tamanhoDoNome, numeroCaracteres, qntdNomes = 0;
  char *ListaNomes = NULL, *pontAux = NULL;
  char nome[20];

  while (1) {
    escolha = menu();
    switch (escolha) {
    case 1:
      if (qntdNomes == 0) {
        printf("Digite o nome: ");
        scanf("%s", nome);
        tamanhoDoNome = strlen(nome);
        ListaNomes = (char *)malloc((tamanhoDoNome + 1) * sizeof(char));
        strcpy(ListaNomes, nome);
        numeroCaracteres = strlen(ListaNomes);
      } else {
        ListaNomes = (char *)realloc(ListaNomes, (numeroCaracteres + 2) * sizeof(char));
        ListaNomes[numeroCaracteres] = ',';
        numeroCaracteres++;
        ListaNomes[numeroCaracteres] = '\0';
        printf("Digite o nome: ");
        scanf("%s", nome);
        tamanhoDoNome = strlen(nome);
        ListaNomes = (char *)realloc(ListaNomes, (numeroCaracteres + tamanhoDoNome + 2) * sizeof(char));
        strcat(ListaNomes, nome);
        numeroCaracteres = strlen(ListaNomes);
      }
      ListaNomes[numeroCaracteres] = '\0';
      qntdNomes++;
      break;
    case 2:
      if (qntdNomes > 0) {
        printf("Digite o nome para remover: ");
        scanf("%s", nome);
        tamanhoDoNome = strlen(nome);
        pontAux = strstr(ListaNomes, nome);
        if (pontAux) {
          for (int i = 0; i <= tamanhoDoNome; i++) {
            strcpy((pontAux), pontAux + 1);
          }
          qntdNomes--;
        } else {
          printf("nome nao encontrado!!\n");
          break;
        }
        if (qntdNomes == 0) {
          free(ListaNomes);
        } else {
          ListaNomes[numeroCaracteres - tamanhoDoNome - 1] = '\0';
          numeroCaracteres = strlen(ListaNomes);
          ListaNomes = (char *)realloc(ListaNomes, (numeroCaracteres + 1) * sizeof(char));
        }
      } else {
        printf("nao ha nomes para serem excluidos!\n");
      }
      break;
    case 3:
      listar(ListaNomes, qntdNomes);
      break;
    case 4:
      if (qntdNomes > 0) {
        free(ListaNomes);
      }
      exit(0);
      break;
    }
  }

  return 0;
}

int menu(void) {
  int choice = 0;
  do {
    printf("-- MENU:\n");
    printf("\t 1. Inserir um nome\n");
    printf("\t 2. Excluir um nome\n");
    printf("\t 3. Listar os nomes\n");
    printf("\t 4. Sair\n");
    printf("-- Digite sua escolha: ");
    scanf("%d", &choice);
  } while (choice <= 0 || choice > 4);
  getchar(); //limpa o buffer do teclado
  return choice;
}

void listar(char *ListaNomes, int qtdNomes) {
  if (qtdNomes == 0) {
    printf("nao existem nomes na lista!\n");
  } else {
    printf("nomes: %s\n", ListaNomes);
  }
}