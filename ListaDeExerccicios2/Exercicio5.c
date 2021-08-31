#include <stdio.h>

typedef struct {
  char nome[30];
  int idade;
  int altura;
} Pessoa;

void cadastrarPessoa(Pessoa *infoPessoas, int numPessoas);
void listarInfo(Pessoa *infoPessoas, int numPessoas);

int main() {
  Pessoa *infoPessoas = NULL;
  int continua, numPessoas = 0;

  while (1) {
    printf("Adicionar uma pessoa?\n1.sim 2.nao\n");
    scanf("%d", &continua);
    if (continua == 2) {
      listarInfo(infoPessoas, numPessoas);
      free(infoPessoas);
      exit(0);
    } else if (continua == 1) {
      if (numPessoas == 0) {
        infoPessoas = (Pessoa *)malloc((numPessoas + 1) * sizeof(Pessoa));
        if (infoPessoas == NULL) {
          printf("Erro memoria!!\n");
          return -1;
        }
      } else {
        infoPessoas = (Pessoa *)realloc(infoPessoas, (numPessoas + 1) * sizeof(Pessoa));
        if (infoPessoas == NULL) {
          printf("Erro memoria!!\n");
          return -1;
        }
      }
      cadastrarPessoa(infoPessoas, numPessoas);
      numPessoas++;
    } else {
      printf("Digite unm opcao valida!!\n");
    }
  }

  return 0;
}

void cadastrarPessoa(Pessoa *infoPessoas, int numPessoas) {
  printf("Digite o nome da pessoa: ");
  scanf("%s", infoPessoas[numPessoas].nome);
  getchar();
  printf("Digite a idade da pessoa: ");
  scanf("%d", &infoPessoas[numPessoas].idade);
  printf("Digite a altura da pessoa: ");
  scanf("%d", &infoPessoas[numPessoas].altura);
}

void listarInfo(Pessoa *infoPessoas, int numPessoas) {
  for (int i = 0; i < numPessoas; i++) {
    printf("Nome: %s\n", infoPessoas[i].nome);
    printf("Idade: %d\n", infoPessoas[i].idade);
    printf("Altura: %d\n", infoPessoas[i].altura);
    printf("----------\n");
  }
}