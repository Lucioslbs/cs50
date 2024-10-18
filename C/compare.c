#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Solicita os valores de i e j ao usuário
    int i = get_int("i: ");
    int j = get_int("j: ");

    // Verifica se i é igual a j
    if (i == j)
    {
        printf("Same\n"); // Se i for igual a j, imprime "Same"
    }
    else
    {
        printf("Different\n"); // Se i for diferente de j, imprime "Different"
    }

    return 0;
}
