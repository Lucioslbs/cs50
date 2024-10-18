#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Solicita ao usuário a altura da pirâmide
    do
    {
        printf("Digite a altura da pirâmide (um número inteiro entre 1 e 8): ");
        scanf("%d", &height);

        // Verifica se a altura está dentro do intervalo desejado
        if (height < 1 || height > 8)
        {
            printf("Por favor, insira um número entre 1 e 8.\n");
        }
    }
    while (height < 1 || height > 8);

    // Loop para iterar pelas linhas
    for (int i = 0; i < height; i++)
    {
        // Loop para imprimir espaços em branco antes no meio e depois dos caracteres '#'
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }

        // Loop para imprimir os caracteres duplos '#' na linha atual
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }

        // Adicionar espaços entre as duas pirâmides
        printf("  ");

        // Loop para imprimir os caracteres '#' á direita
        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }

        // Quebra de linha após cada linha da pirâmide
        printf("\n");
    }

    return 0;
}
