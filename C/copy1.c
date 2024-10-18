#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Obtém a string do usuário
    char *s = get_string("s: ");

    // Aloca memória para t, com tamanho igual ao de s + 1 para o caractere nulo
    char *t = malloc(strlen(s) + 1);

    // Verifica se a alocação de memória foi bem-sucedida
    if (t == NULL)
    {
        return 1; // Retorna 1 em caso de falha na alocação de memória
    }

    // Copia os caracteres de s para t
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        t[i] = s[i];
    }

    // Adiciona o caractere nulo ao final de t para indicar o final da string
    t[strlen(s)] = '\0';

    // Torna o primeiro caractere de t maiúsculo
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    // Imprime s e t
    printf("s: %s\n", s);
    printf("t: %s\n", t);

    // Libera a memória alocada para t
    free(t);

    return 0;
}
