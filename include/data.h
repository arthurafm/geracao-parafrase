#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definição de constantes
#define MAX_STRING 100
#define TAB "\t"
#define LF "\n"
#define ESPACO " "

// Definição do tipo da árvore
struct TNodoA{
char palavra[MAX_STRING];
char sinonimo[MAX_STRING];
int FB;
struct TNodoA *esq;
struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;

// Função para inserção de nodos em uma ABP que armazene strings
pNodoA* InsereArvoreABP(pNodoA *a, char str_pal[], char str_sin[]);

// Função que calcula a altura
int Altura (pNodoA *a);

// Função que calcula o fator de balanceamento
int FatorBalanceamento(pNodoA *a);

// Função de consulta de ABP
pNodoA* consultaArvore(pNodoA *a, char chave[], int *cmp);

// Função de rotação à direita
pNodoA* rotate_right(pNodoA *a);

// Função de rotação à esquerda
pNodoA* rotate_left(pNodoA *a);

// Função de rotação dupla à direita
pNodoA* double_rotate_right(pNodoA *p);

// Função de rotação dupla à esquerda
pNodoA* double_rotate_left(pNodoA *p);

// Função para contar os nodos de uma ABP
int ContarNodos(pNodoA *a);

// Funções para inserção de nodos em uma AVL que armazene strings
pNodoA* Caso1 (pNodoA *a , int *ok);
pNodoA* Caso2 (pNodoA *a , int *ok);
pNodoA* InsereArvoreAVL(pNodoA *a, char str_pal[], char str_sin[], int *ok, int *contador_rot);

// Funções de arquivos texto
short AbreArquivo(FILE **arq_txt, char nome_arq[], char *modo);
short ColocaTxt(char string[]);
void LeArquivoEntrada(FILE *arq_txt, pNodoA **abp, pNodoA **avl, int *contador_rot);
void ProcessaDados(FILE *arq_entrada, FILE *arq_saida, pNodoA *abp, pNodoA *avl, int *cmp_abp, int *cmp_avl);
