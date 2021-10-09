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
int VerificaRotacaoSimplesOuDupla(No **ppRaiz);
void RotacaoEsquerdaSimples(No **ppRaiz);
void RotacaoDireitaSimples(No **ppRaiz);
int balancaEsquerda(No **ppRaiz);
int balancaDireita(No **ppRaiz);
int EhArvoreArvl(No *pRaiz);
void limparArvore(No *ppRaiz);

int main() {
  int i = 0, valorInserir, numeroDeNos;
  No *ppRaiz = NULL;

  printf("Digite quantos nodos voce quer: ");
  scanf("%d", &numeroDeNos);
  getchar();

  srand(time(0));

  while (i < numeroDeNos) {
    valorInserir = rand() % 100;
    printf("valor inserir: %d\n", valorInserir);
    Insere(&ppRaiz, valorInserir);
    i++;
  }

  if (EhArvoreArvl(ppRaiz)) {
    printf("Arvore AVL\n");
  } else {
    printf("Nao eh Arvore AVL\n");
  }

  limparArvore(ppRaiz);

  return 0;
}

int Insere(No **ppRaiz, int valor) {
  if (*ppRaiz == NULL) {
    *ppRaiz = (No *)malloc(sizeof(No));
    (*ppRaiz)->valor = valor;
    (*ppRaiz)->pEsq = NULL;
    (*ppRaiz)->pDir = NULL;
    return 1; //bem sucedido
  } else if ((*ppRaiz)->valor > valor) {
    if (Insere(&(*ppRaiz)->pEsq, valor)) {
      if (Balanceamento(ppRaiz)) {
        return 0; //houve balanceamento;
      } else {
        return 1; //bem sucedido sem balanceamento;
      }
    }
  } else if ((*ppRaiz)->valor < valor) {
    if (Insere(&(*ppRaiz)->pDir, valor)) {
      if (Balanceamento(ppRaiz)) {
        return 0; //houve balanceamento;
      } else {
        return 1; //bem sucedido sem balanceamento;
      }
    }
  } else {
    printf("Valor ja existe!!\n");
    return 0; //valor já existente;
  }
}

int Balanceamento(No **ppRaiz) {
  int fb = FB(*ppRaiz);

  if (fb > 1) {
    return balancaEsquerda(ppRaiz);
  } else if (fb < -1) {
    return balancaDireita(ppRaiz);
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

  if (FBE >= 0) {
    RotacaoDireitaSimples(ppRaiz);
    printf("RDSimples\n");
    return 1;
  } else if (FBE < 0) {
    RotacaoEsquerdaSimples(&((*ppRaiz)->pEsq));
    RotacaoDireitaSimples(ppRaiz);
    printf("RDDupla\n");
    return 1;
  }
  return 0;
}

int balancaDireita(No **ppRaiz) {
  int FBD = FB((*ppRaiz)->pDir);

  if (FBD <= 0) {
    RotacaoEsquerdaSimples(ppRaiz);
    printf("RESimples\n");
    return 1;
  } else if (FBD > 0) {
    RotacaoDireitaSimples(&((*ppRaiz)->pDir));
    RotacaoEsquerdaSimples(ppRaiz);
    printf("REDupla\n");
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