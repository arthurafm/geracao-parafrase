#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int main()
{
    // Declaração de variáveis estatísticas
    int cmpABP = 0, cmpAVL = 0, contador_rot = 0, nodos_abp = 0, altura_abp = 0, nodos_avl = 0, altura_avl = 0, ctrl = 1;
    // Declaração de variáveis de TADs
    pNodoA *ABP = NULL, *AVL = NULL;
    // Declaração de variáveis de arquivos texto
    FILE *arq_dicionario = NULL, *arq_entrada = NULL, *arq_saida = NULL;
    // Declaração de variáveis de interação com o usuário
    char nome_dicionario[MAX_STRING], nome_entrada[MAX_STRING], nome_saida[MAX_STRING];

    while(ctrl == 1)
    {
        // Mensagens para o usuário
        printf("Digite o nome do arquivo de dicionario:\n");
        gets(nome_dicionario);
        ColocaTxt(nome_dicionario);
        fflush(stdin);
        printf("\nDigite o nome do arquivo de entrada:\n");
        gets(nome_entrada);
        ColocaTxt(nome_entrada);
        fflush(stdin);
        printf("\nDigite o nome do arquivo de saida:\n");
        gets(nome_saida);
        ColocaTxt(nome_saida);
        fflush(stdin);

        // Chamada de funções que processam os dados
        if(AbreArquivo(&arq_dicionario, nome_dicionario, "r") == 0)
            printf("Erro na abertura do arquivo de dicionario.\n\n\n");
        else
        {
            if(AbreArquivo(&arq_entrada, nome_entrada, "r") == 0)
                printf("Erro na abertura do arquivo de entrada.\n\n\n");
            else
            {
                if(AbreArquivo(&arq_saida, nome_saida, "w") == 0)
                    printf("Erro na abertura do arquivo de entrada.\n\n\n");
                else
                {
                    LeArquivoEntrada(arq_dicionario, &ABP, &AVL, &contador_rot);
                    ProcessaDados(arq_entrada, arq_saida, ABP, AVL, &cmpABP, &cmpAVL);
                    nodos_abp = ContarNodos(ABP);
                    nodos_avl = ContarNodos(AVL);
                    altura_abp = Altura(ABP);
                    altura_avl = Altura(AVL);
                    ctrl = 0;
                }
            }
        }
    }

    // Mensagens para o usuário
    printf("\n\n======= ESTATISTICAS ABP =======\n");
    printf("Numero de nodos: %d\n", nodos_abp);
    printf("Altura: %d\n", altura_abp);
    printf("Rotacoes: 0\n");
    printf("Comparacoes: %d\n\n\n", cmpABP);
    printf("======= ESTATISTICAS AVL =======\n");
    printf("Numero de nodos: %d\n", nodos_avl);
    printf("Altura: %d\n", altura_avl);
    printf("Rotacoes: %d\n", contador_rot);
    printf("Comparacoes: %d\n\n\n", cmpAVL);

    return 0;
}
