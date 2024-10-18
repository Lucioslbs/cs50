#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Solicite o valor inicial ao usuário
    int n;
    do
    {
        n = get_int("Start size: ");
    }
    while (n < 9);

    // TODO: Solicite o valor final ao usuário
    int i;
    do
    {
        i = get_int("End size: ");
    }
    while (i < n);

    // Caso especial se o tamanho inicial já é maior ou igual ao tamanho final
    if (n >= i)
    {
        printf("Years: 0\n");
        return 0;
    }

    // TODO: Calcule o número de anos até o limite
    int anos;
    for (anos = 0; n < i; anos++)
    {
        n = n + (n / 3) - (n / 4);
    }

    // TODO: Imprima o número de anos
    printf("Years: %i\n", anos);
}
