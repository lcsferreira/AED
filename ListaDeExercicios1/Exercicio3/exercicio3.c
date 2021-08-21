#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_NPESSOAS (1 * sizeof(int))
#define TAMANHO_NOME (11 * sizeof(char))
#define TAMANHO_IDADE (1 * sizeof(int))
#define TAMANHO_TELEFONE (1 * sizeof(int))
#define TAMANHO_CADASTRO ((10 * sizeof(char)) + (1 * sizeof(int)) + (1 * sizeof(int)))

int Menu(void);
void Listar(void *pBuffer, int i);
void InserirCadastro(void *pBuffer, int totalPessoas);
void BuscarNome(void *pBuffer, char buscaNome[], int i);
int ExcluirCadastro(void *pBuffer, char nomeRemover[], int i, int totalPessoas);

int main() {
  int escolha, flagRemove = 0, totalPessoas = 0;
  char nome[10];
  void *pBuffer = NULL;
  pBuffer = malloc(TAMANHO_NPESSOAS);

  while (1) {
    *(int *)(pBuffer) = 0;
    escolha = Menu();
    switch (escolha) {
    case 1:
      pBuffer = realloc(pBuffer, (TAMANHO_NPESSOAS) + (TAMANHO_CADASTRO * (totalPessoas + 1)));
      InserirCadastro(pBuffer, totalPessoas);
      totalPessoas++;
      *(int *)(pBuffer) = totalPessoas;
      break;
    case 2:
      printf("Digite o nome para remover: ");
      scanf("%s", nome);
      getchar();

      for (int i = 0; i < totalPessoas; i++) {
        flagRemove = ExcluirCadastro(pBuffer, nome, i, totalPessoas);
        if (flagRemove == 1) {
          totalPessoas--;
        }
        flagRemove = 0;
      }
      break;
    case 3:
      printf("Digite o nome que deseja procurar: ");
      scanf("%s", nome);
      getchar();
      for (int i = 0; i < totalPessoas; i++) {
        BuscarNome(pBuffer, nome, i);
      }
      break;
    case 4:
      for (int i = 0; i < totalPessoas; i++) {
        Listar(pBuffer, i);
      }
      break;
    case 5:
      free(pBuffer);
      exit(0);
      break;
    }
  }
}

int Menu(void) {
  int choice = 0;
  do {
    printf("-- MENU:\n");
    printf("\t 1. Inserir um nome\n");
    printf("\t 2. Excluir um nome\n");
    printf("\t 3. Procurar o nome\n");
    printf("\t 4. Listar\n");
    printf("\t 5. Sair\n");
    printf("-- Digite sua escolha: ");
    scanf("%d", &choice);
  } while (choice <= 0 || choice > 5);
  getchar(); //limpa o buffer do teclado
  return choice;
}

void InserirCadastro(void *pBuffer, int totalPessoas) {
  int telefone;
  printf("Insira um nome: ");
  scanf("%s", (char *)((char *)pBuffer + TAMANHO_NPESSOAS + (TAMANHO_CADASTRO * totalPessoas)));
  getchar();

  printf("Insira a idade: ");
  scanf("%d", (int *)(pBuffer + TAMANHO_NPESSOAS + TAMANHO_NOME + (TAMANHO_CADASTRO * totalPessoas)));

  do { //999384646 // 900000000
    printf("Insira um telefone valido: ");
    scanf("%d", &telefone);
  } while (telefone < 900000000 || telefone > 999999999);
  *(int *)(pBuffer + TAMANHO_NPESSOAS + TAMANHO_NOME + TAMANHO_IDADE + (TAMANHO_CADASTRO * totalPessoas)) = telefone;
}

int ExcluirCadastro(void *pBuffer, char nomeRemover[], int i, int totalPessoas) {
  if ((strcmp((char *)((char *)pBuffer + TAMANHO_NPESSOAS + (TAMANHO_CADASTRO * i)), nomeRemover) == 0)) {
    for (int j = i; j < (totalPessoas - 1); j++) {
      strcpy((char *)((char *)pBuffer + TAMANHO_NPESSOAS + (TAMANHO_CADASTRO * j)), (char *)((char *)pBuffer + TAMANHO_NPESSOAS + (TAMANHO_CADASTRO * (j + 1))));

      *(int *)(pBuffer + TAMANHO_NPESSOAS + TAMANHO_NOME + (TAMANHO_CADASTRO * j)) = *(int *)(pBuffer + TAMANHO_NPESSOAS + TAMANHO_NOME + (TAMANHO_CADASTRO * (j + 1)));

      *(int *)(pBuffer + TAMANHO_NPESSOAS + TAMANHO_NOME + TAMANHO_IDADE + (TAMANHO_CADASTRO * j)) = *(int *)(pBuffer + TAMANHO_NPESSOAS + TAMANHO_NOME + TAMANHO_IDADE + (TAMANHO_CADASTRO * (j + 1)));
    }
    totalPessoas--;
    *(int *)(pBuffer) = totalPessoas;
    pBuffer = realloc(pBuffer, (TAMANHO_NPESSOAS) + (TAMANHO_CADASTRO * (totalPessoas)));
    return 1;
  } else {
    return 0;
  }
}

void BuscarNome(void *pBuffer, char buscaNome[], int i) {
  if ((strcmp((char *)((char *)pBuffer + TAMANHO_NPESSOAS + (TAMANHO_CADASTRO * i)), buscaNome) == 0)) {
    printf("Nome: %s \n", (char *)((char *)pBuffer + TAMANHO_NPESSOAS + (TAMANHO_CADASTRO * i)));
    printf("Idade: %d\n", *(int *)(pBuffer + TAMANHO_NPESSOAS + TAMANHO_NOME + (TAMANHO_CADASTRO * i)));
    printf("Telefone: %d\n", *(int *)(pBuffer + TAMANHO_NPESSOAS + TAMANHO_NOME + TAMANHO_IDADE + (TAMANHO_CADASTRO * i)));
  }
}

void Listar(void *pBuffer, int i) {
  printf("Nome: %s \n", (char *)((char *)pBuffer + TAMANHO_NPESSOAS + (TAMANHO_CADASTRO * i)));
  printf("Idade: %d\n", *(int *)(pBuffer + TAMANHO_NPESSOAS + TAMANHO_NOME + (TAMANHO_CADASTRO * i)));
  printf("Telefone: %d\n", *(int *)(pBuffer + TAMANHO_NPESSOAS + TAMANHO_NOME + TAMANHO_IDADE + (TAMANHO_CADASTRO * i)));
}
