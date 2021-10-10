#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No {
  int valor;
  struct No *pEsq;
  struct No *pDir;
} No;

int Insere(No **ppRaiz, int valor);
int Balanceamento(No **ppRaiz);
int FB(No *pRaiz);
int Altura(No *pRaiz);
void RotacaoEsquerdaSimples(No **ppRaiz);
void RotacaoDireitaSimples(No **ppRaiz);
int balancaEsquerda(No **ppRaiz);
int balancaDireita(No **ppRaiz);
int EhArvoreArvl(No *pRaiz);
void limparArvore(No *ppRaiz);
void ImprimeArvore(No *ppRaiz);
void SegundoCenario();

int main() {
  int i = 0, valorInserir, numeroDeNos;
  No *ppRaiz = NULL;

  printf("Digite quantos nodos voce quer: ");
  scanf("%d", &numeroDeNos);
  getchar();

  srand(time(0));

  while (i < numeroDeNos) {
    valorInserir = rand() % 100;
    Insere(&ppRaiz, valorInserir);
    i++;
  }

  ImprimeArvore(ppRaiz);

  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }

  limparArvore(ppRaiz);

  SegundoCenario();

  return 0;
}

int Insere(No **ppRaiz, int valor) {
  if (*ppRaiz == NULL) { //se o no em questão == null
    *ppRaiz = (No *)malloc(sizeof(No));
    (*ppRaiz)->valor = valor;
    (*ppRaiz)->pEsq = NULL;
    (*ppRaiz)->pDir = NULL;
    return 1;
  } else if ((*ppRaiz)->valor > valor) {
    if (Insere(&(*ppRaiz)->pEsq, valor)) { //insere na esquerda
      if (Balanceamento(ppRaiz)) {
        return 0; //raiz alterada
      } else {
        return 1; //raiz mantém
      }
    }
  } else if ((*ppRaiz)->valor < valor) { //insere na direita
    if (Insere(&(*ppRaiz)->pDir, valor)) {
      if (Balanceamento(ppRaiz)) {
        return 0; //raiz alterada
      } else {
        return 1; //raiz mantém
      }
    }
  } else {
    return 0; //valor já existente;
  }
}

int Balanceamento(No **ppRaiz) {
  int fb = FB(*ppRaiz);

  if (fb > 1) {
    return balancaEsquerda(ppRaiz); //balanca tende esquerda
  } else if (fb < -1) {
    return balancaDireita(ppRaiz); //balanca tende a direita
  } else {
    return 0;
  }
}

int FB(No *pRaiz) {
  if (pRaiz == NULL) {
    return 0; //se não tiver nenhum elemento, FB = 0
  }
  return Altura(pRaiz->pEsq) - Altura(pRaiz->pDir); //retorna o resultado da subtração da altura da esquerda com a da direita;
}

int Altura(No *pRaiz) {
  int Esq, Dir;

  if (pRaiz == NULL) {
    return 0; //se não houver um nó, altura 0
  }

  Esq = Altura(pRaiz->pEsq);
  Dir = Altura(pRaiz->pDir); //chama a próprioa função para calcular a altura do próprio nó

  if (Esq > Dir) {
    return Esq + 1;
  } else {
    return Dir + 1;
  }
}

void RotacaoEsquerdaSimples(No **ppRaiz) {
  No *pAux;

  pAux = (*ppRaiz)->pDir;
  (*ppRaiz)->pDir = pAux->pEsq;
  pAux->pEsq = (*ppRaiz);
  (*ppRaiz) = pAux;
}

void RotacaoDireitaSimples(No **ppRaiz) {
  No *pAux;

  pAux = (*ppRaiz)->pEsq;
  (*ppRaiz)->pEsq = pAux->pDir;
  pAux->pDir = (*ppRaiz);
  (*ppRaiz) = pAux;
}

int balancaEsquerda(No **ppRaiz) {
  int FBE = FB((*ppRaiz)->pEsq);

  if (FBE > 0) {
    RotacaoDireitaSimples(ppRaiz);
    // printf("RDSimples\n");
    return 1;
  } else if (FBE < 0) {
    RotacaoEsquerdaSimples(&((*ppRaiz)->pEsq));
    RotacaoDireitaSimples(ppRaiz);
    // printf("RDDupla\n");
    return 1;
  }
  return 0;
}

int balancaDireita(No **ppRaiz) {
  int FBD = FB((*ppRaiz)->pDir);

  if (FBD <= 0) {
    RotacaoEsquerdaSimples(ppRaiz);
    // printf("RESimples\n");
    return 1;
  } else if (FBD > 0) {
    RotacaoDireitaSimples(&((*ppRaiz)->pDir));
    RotacaoEsquerdaSimples(ppRaiz);
    // printf("REDupla\n");
    return 1;
  }
  return 0;
}

void limparArvore(No *ppRaiz) {
  if (ppRaiz == NULL) return;

  limparArvore(ppRaiz->pEsq);
  limparArvore(ppRaiz->pDir);

  free(ppRaiz);
}

int EhArvoreArvl(No *ppRaiz) {
  int fb;
  fb = FB(ppRaiz);

  if (ppRaiz == NULL)
    return 1;

  if (!EhArvoreArvl(ppRaiz->pEsq)) {
    return 0;
  }
  if (!EhArvoreArvl(ppRaiz->pDir)) {
    return 0;
  }

  if ((fb > 1) || (fb < -1)) {
    return 0;
  } else {
    return 1;
  }
}

void ImprimeArvore(No *ppRaiz) {
  if (ppRaiz != NULL) {
    printf("%d(", ppRaiz->valor);
    ImprimeArvore(ppRaiz->pEsq);
    ImprimeArvore(ppRaiz->pDir);
    printf(")");
  }
}

void SegundoCenario() {
  printf("\n\t--CASO 1A--\n");
  caso1a();
  printf("\n\t--CASO 2A--\n");
  caso2a();
  printf("\n\t--CASO 3A--\n");
  caso3a();
  printf("\n\t--CASO 1B--\n");
  caso1b();
  printf("\n\t--CASO 2B--\n");
  caso2b();
  printf("\n\t--CASO 3B--\n");
  caso3b();
}

void caso1a() {
  No *ppRaiz = NULL;
  int valorInserir;
  valorInserir = 20;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 4;
  Insere(&ppRaiz, valorInserir);
  ImprimeArvore(ppRaiz);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  printf("\n\n");
  valorInserir = 15;
  Insere(&ppRaiz, valorInserir);
  ImprimeArvore(ppRaiz);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  limparArvore(ppRaiz);
}

void caso2a() {
  No *ppRaiz = NULL;
  int valorInserir;
  valorInserir = 20;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 4;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 26;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 3;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 9;
  Insere(&ppRaiz, valorInserir);
  ImprimeArvore(ppRaiz);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  printf("\n\n");
  valorInserir = 15;
  Insere(&ppRaiz, valorInserir);
  ImprimeArvore(ppRaiz);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }

  limparArvore(ppRaiz);
}

void caso3a() {
  No *ppRaiz = NULL;
  int valorInserir;
  valorInserir = 20;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 4;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 26;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 3;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 9;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 2;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 7;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 11;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 21;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 30;
  Insere(&ppRaiz, valorInserir);
  ImprimeArvore(ppRaiz);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  printf("\n\n");
  valorInserir = 15;
  Insere(&ppRaiz, valorInserir);
  ImprimeArvore(ppRaiz);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  limparArvore(ppRaiz);
}

void caso1b() {
  No *ppRaiz = NULL;
  int valorInserir;
  valorInserir = 20;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 4;
  Insere(&ppRaiz, valorInserir);
  ImprimeArvore(ppRaiz);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  printf("\n\n");
  valorInserir = 8;
  Insere(&ppRaiz, valorInserir);
  ImprimeArvore(ppRaiz);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  limparArvore(ppRaiz);
}

void caso2b() {
  No *ppRaiz = NULL;
  int valorInserir;
  valorInserir = 20;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 4;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 26;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 3;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 9;
  Insere(&ppRaiz, valorInserir);
  ImprimeArvore(ppRaiz);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  printf("\n\n");
  valorInserir = 8;
  Insere(&ppRaiz, valorInserir);
  ImprimeArvore(ppRaiz);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }

  limparArvore(ppRaiz);
}

void caso3b() {
  No *ppRaiz = NULL;
  int valorInserir;
  valorInserir = 20;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 4;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 26;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 3;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 9;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 2;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 7;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 11;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 21;
  Insere(&ppRaiz, valorInserir);
  valorInserir = 30;
  Insere(&ppRaiz, valorInserir);
  ImprimeArvore(ppRaiz);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  printf("\n\n");
  valorInserir = 8;
  Insere(&ppRaiz, valorInserir);
  ImprimeArvore(ppRaiz);
  if (EhArvoreArvl(ppRaiz)) {
    printf("\nSUCESSO! Eh Arvore AVL\n");
  } else {
    printf("\nERRO!! Nao eh Arvore AVL\n");
  }
  limparArvore(ppRaiz);
}