#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Defini��o de constantes
#define MAX_STRING 100
#define TAB "\t"
#define LF "\n"
#define ESPACO " "

// Defini��o do tipo da �rvore
struct TNodoA{
char palavra[MAX_STRING];
char sinonimo[MAX_STRING];
int FB;
struct TNodoA *esq;
struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;

// Fun��o para inser��o de nodos em uma ABP que armazene strings
pNodoA* InsereArvoreABP(pNodoA *a, char str_pal[], char str_sin[]);

// Fun��o que calcula a altura
int Altura (pNodoA *a);

// Fun��o que calcula o fator de balanceamento
int FatorBalanceamento(pNodoA *a);

// Fun��o de consulta de ABP
pNodoA* consultaArvore(pNodoA *a, char chave[], int *cmp);

// Fun��o de rota��o � direita
pNodoA* rotate_right(pNodoA *a);

// Fun��o de rota��o � esquerda
pNodoA* rotate_left(pNodoA *a);

// Fun��o de rota��o dupla � direita
pNodoA* double_rotate_right(pNodoA *p);

// Fun��o de rota��o dupla � esquerda
pNodoA* double_rotate_left(pNodoA *p);

// Fun��o para contar os nodos de uma ABP
int ContarNodos(pNodoA *a);

// Fun��es para inser��o de nodos em uma AVL que armazene strings
pNodoA* Caso1 (pNodoA *a , int *ok);
pNodoA* Caso2 (pNodoA *a , int *ok);
pNodoA* InsereArvoreAVL(pNodoA *a, char str_pal[], char str_sin[], int *ok, int *contador_rot);

// Fun��es de arquivos texto
short AbreArquivo(FILE **arq_txt, char nome_arq[], char *modo);
short ColocaTxt(char string[]);
void LeArquivoEntrada(FILE *arq_txt, pNodoA **abp, pNodoA **avl, int *contador_rot);
void ProcessaDados(FILE *arq_entrada, FILE *arq_saida, pNodoA *abp, pNodoA *avl, int *cmp_abp, int *cmp_avl);
