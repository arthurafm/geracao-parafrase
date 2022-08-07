#include <stdio.h>
#include <stdlib.h>
#include "data.h"

// Função que abre arquivo
short AbreArquivo(FILE **arq_txt, char nome_arq[], char *modo)
{
    *arq_txt = fopen(nome_arq, modo);
    if(*arq_txt == NULL)
        return 0;
    else
        return 1;
}

// Função que coloca tipo de arquivo
short ColocaTxt(char string[])
{
    int i;
    char s[] = ".txt";
    for(i = 0; string[i] != '\0'; i++);
    if(string[i - 1] == 't')
    {
        if(string[i - 2] == 'x')
        {
            if(string[i - 3] == 't')
            {
                if(string[i - 4] == '.') // Caso a string termine em .txt, retorna 1
                    return 1;
            }
        }
    }
    strcat(string, s); // Caso a string nao termine em .txt, coloca o .txt na string e retorna 0
    return 0;
}

// Função que lê o conteúdo do dicionário
void LeArquivoEntrada(FILE *arq_txt, pNodoA **abp, pNodoA **avl, int *contador_rot)
{
    // Declaração de variáveis buffers
    char str_temp[MAX_STRING], string_palavra[MAX_STRING], string_sinonimo[MAX_STRING];
    int ok = 0;

    while(!feof(arq_txt)) // Enquanto não chegar no fim do arquivo texto
    {
        if(fgets(str_temp, 2*MAX_STRING+1, arq_txt) != NULL) // Se não houver erro na leitura de strings no arquivo
        {
            // Destaca as palavras e associa às variáveis buffers
            strcpy(string_palavra, strtok(str_temp, TAB));
            strcpy(string_sinonimo, strtok(NULL, TAB));
            strcpy(string_sinonimo, strtok(string_sinonimo, LF)); // Retira o LF no final da string

            // Insere nas árvores
            *abp = InsereArvoreABP(*abp, string_palavra, string_sinonimo);
            *avl = InsereArvoreAVL(*avl, string_palavra, string_sinonimo, &ok, contador_rot);
        }
    }

    fclose(arq_txt); // Fecha o arquivo
}

// Função que transforma os dados do arquivo de entrada e coloca no arquivo de saída
void ProcessaDados(FILE *arq_entrada, FILE *arq_saida, pNodoA *abp, pNodoA *avl, int *cmp_abp, int *cmp_avl)
{
    // Declaração de variáveis buffers
    char str_temp[MAX_STRING], *string_palavra;
    pNodoA *a;
    int i = 0, p = 0;

    while(!feof(arq_entrada)) // Enquanto não fechar ao fim do arquivo de entrada
    {
        if(fgets(str_temp, MAX_STRING, arq_entrada) != NULL) // Se não houver erro na leitura do arquivo
        {
            // Destaca as palavras e associa às variáveis buffers
            strcpy(str_temp, strtok(str_temp, LF));
            string_palavra = strtok(str_temp, ESPACO);

            // Se chegar no fim da linha, põe um LF no arquivo
            if(string_palavra == NULL)
                fwrite(LF, sizeof(char), strlen(LF), arq_saida);

            // Enquanto não chegar no fim da linha
            while(string_palavra != NULL)
            {
                // Se a primeira letra da palavra for maiúscula
                if(string_palavra[0] == toupper(string_palavra[0]))
                {
                    // Se a palavra toda for maiúscula, armazena o resultado
                    if((string_palavra[1] == toupper(string_palavra[1])) && (string_palavra[1] != '\0'))
                        p = 2;
                    // Se for só a primeira letra, armazena o resultado
                    else
                        p = 1;

                    // Transforma todas as letras da palavra para minúsculas
                    for(i = 0; string_palavra[i] != '\0'; i++)
                    {
                        string_palavra[i] = tolower(string_palavra[i]);
                    }
                }
                // Caso a primeira letra for minúscula, armazena o resultado
                else
                    p = 0;

                // Consulta nas duas árvores, contando as comparações
                consultaArvore(avl, string_palavra, cmp_avl);
                a = consultaArvore(abp, string_palavra, cmp_abp);

                // Se achar algum sinônimo, troca a palavra por seu sinônimo
                if (a != NULL)
                {
                    string_palavra = a->sinonimo;
                }

                // Se apenas a primeira letra da palavra original for maiúscula
                if(p == 1)
                    string_palavra[0] = toupper(string_palavra[0]); // Transforma a primeira letra em maiúscula

                // Se a palavra original toda for maiúscula
                if(p == 2)
                {
                    for(i = 0; string_palavra[i] != '\0'; i++) // Transforma a palavra toda em maiúscula
                    {
                        string_palavra[i] = toupper(string_palavra[i]);
                    }
                }

                // Escreve no arquivo de saída a palavra processada
                fwrite(string_palavra, sizeof(char), strlen(string_palavra), arq_saida);

                // Transforma a palavra na árvore de volta a toda minúscula
                for(i = 0; string_palavra[i] != '\0'; i++)
                {
                    string_palavra[i] = tolower(string_palavra[i]);
                }

                // Procura a próxima palavra
                string_palavra = strtok(NULL, ESPACO);

                // Caso exista alguma palavra, escreve um espaço
                if(string_palavra != NULL)
                    fwrite(ESPACO, sizeof(char), strlen(ESPACO), arq_saida);
                // Caso não tenha palavra, pula uma linha
                else
                    fwrite(LF, sizeof(char), strlen(LF), arq_saida);
            }
        }
    }

    // Fecha os arquivos
    fclose(arq_entrada);
    fclose(arq_saida);
}


