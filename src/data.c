#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"

// Fun��o para inser��o de nodos em uma ABP que armazene strings
pNodoA* InsereArvoreABP(pNodoA *a, char str_pal[], char str_sin[])
{
    // Se chegar � uma folha
    if (a == NULL)
    {
        // Aloca mem�ria
        a = (pNodoA*) malloc(sizeof(pNodoA));

        // Coloca os dados no nodo
        strcpy(a->palavra, str_pal);
        strcpy(a->sinonimo, str_sin);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;

        // Retorna o nodo
        return a;
    }
    else
    {
        // Se o nodo n�o for igual � raiz
        if(0 != (strcmp(a->palavra, str_pal)))
        {
            // Se a raiz tiver uma ordem lexicogr�fica maior que o inserido
            if(0 < (strcmp(a->palavra, str_pal)))
                a->esq = InsereArvoreABP(a->esq, str_pal, str_sin);
            // Se a raiz tiver uma ordem lexicogr�fica menor que o inserido
            else
                a->dir = InsereArvoreABP(a->dir, str_pal, str_sin);
        }

        // Retorna o nodo
        return a;
    }
}

// Fun��o que calcula a altura
int Altura (pNodoA *a)
{
    int Alt_Esq, Alt_Dir;

    // Se n�o houver �rvore, retorna 0
    if (a == NULL)
        return 0;
    else
    {
        // Seta as alturas de cada lado
        Alt_Esq = Altura(a->esq);
        Alt_Dir = Altura(a->dir);

        // Se a altura da sub-�rvore da esquerda for maior, retorna 1 + altura da esquerda
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        // Se a altura da sub-�rvore da direita for maior, retorna 1 + altura da direita
        else
            return (1 + Alt_Dir);
    }
}

// Fun��o que calcula o fator de balanceamento
int FatorBalanceamento(pNodoA *a)
{
    return(Altura(a->esq) - Altura(a->dir));
}

// Fun��o de consulta de ABP
pNodoA* consultaArvore(pNodoA *a, char chave[], int *cmp)
{
    // Enquanto a �rvore n�o chegar a uma folha
    while (a!=NULL)
    {
        (*cmp)++; // Incrementa as compara��es

        // Se achar um nodo igual
        if ((strcmp(a->palavra, chave)) == 0)
        {
            (*cmp)++; // Incrementa as compara��es

            // Retorna o nodo achado
            return a;
        }
        else
        {
            (*cmp)++; // Incrementa as compara��es

            // Caso a ordem lexicogr�fica da raiz for maior que a da palavra, procura na sub-�rvore esquerda
            if ((strcmp(a->palavra, chave)) > 0)
                a = a->esq;
            // Caso a ordem lexicogr�fica da raiz for menor que a da palavra, procura na sub-�rvore direita
            else
                a = a->dir;
        }
    }

    // Caso n�o ache o nodo, retorna NULL
    return NULL;
}

// Fun��o de rota��o � direita
pNodoA* rotate_right(pNodoA *p)
{
    pNodoA *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
}

// Fun��o de rota��o � esquerda
pNodoA* rotate_left(pNodoA *p)
{
    pNodoA *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}

// Fun��o de rota��o dupla � direita
pNodoA* double_rotate_right(pNodoA *p)
{
    pNodoA *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if(v->FB == 1)
        p->FB = -1;
    else
        p->FB = 0;
    if(v->FB == -1)
        u->FB = 1;
    else
        u->FB = 0;
    p = v;
    return p;
}

// Fun��o de rota��o dupla � esquerda
pNodoA* double_rotate_left(pNodoA *p)
{
    pNodoA *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if(y->FB == -1)
        p->FB = 1;
    else
        p->FB = 0;
    if(y->FB == 1)
        z->FB = -1;
    else
        z->FB = 0;
    p = y;
    return p;
}

// Fun��o para contar os nodos de uma ABP
int ContarNodos(pNodoA *a)
{
    if(a == NULL)
        return 0;
    else
        return(ContarNodos(a->esq) + ContarNodos(a->dir) + 1);
}

// Fun��es para inser��o de nodos em uma AVL que armazene strings

pNodoA* Caso1 (pNodoA *a , int *ok)
{
    pNodoA *z;
    z = a->esq;
    if (z->FB == 1)
        a = rotate_right(a);
    else
        a = double_rotate_right(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA* Caso2 (pNodoA *a , int *ok)
{
    pNodoA *z;
    z = a->dir;
    if (z->FB == -1)
        a = rotate_left(a);
    else
        a = double_rotate_left(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA* InsereArvoreAVL(pNodoA *a, char str_pal[], char str_sin[], int *ok, int *contador_rot)
{
    // Caso chegar � uma folha
    if(a == NULL)
    {
        // Aloca mem�ria
        a = (pNodoA*) malloc(sizeof(pNodoA));

        // Coloca os dados no nodo
        strcpy(a->palavra, str_pal);
        strcpy(a->sinonimo, str_sin);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;

        // Retorna o nodo
        return a;
    }
    else
    {
        // Se o nodo n�o for igual � raiz
        if(0 != (strcmp(a->palavra, str_pal)))
        {
            // Se a raiz tiver uma ordem lexicogr�fica maior que o inserido
            if(0 < (strcmp(a->palavra, str_pal)))
            {
                a->esq = InsereArvoreAVL(a->esq, str_pal, str_sin, ok, contador_rot);
                if (*ok)
                {
                    switch (a->FB)
                    {
                        case -1:
                            a->FB = 0;
                            *ok = 0;
                            break;
                        case 0:
                            a->FB = 1;
                            break;
                        case 1:
                            // Caso seja necess�rio uma rota��o
                            (*contador_rot)++;
                            a = Caso1(a,ok);
                            break;
                    }
                }

                // Retorna o nodo
                return a;
            }
            // Se a raiz tiver uma ordem lexicogr�fica menor que o inserido
            else
                {
                    a->dir = InsereArvoreAVL(a->dir, str_pal, str_sin, ok, contador_rot);
                    if (*ok)
                    {
                        switch (a->FB)
                        {
                            case 1:
                                a->FB = 0;
                                *ok = 0;
                                break;
                            case 0:
                                a->FB = -1;
                                break;
                            case -1:
                                // Caso seja necess�rio uma rota��o
                                a = Caso2(a,ok);
                                (*contador_rot)++;
                                break;
                        }
                    }
                }
        }

        // Retorna o nodo
        return a;
    }
}
