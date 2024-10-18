#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char *s = "HI!";
    printf("%c\n", *s);
    printf("%c\n", *(s + 1));
    printf("%c\n", *(s + 2));

    // Verificar se o comprimento da string é maior ou igual a 4 antes de tentar acessar o quarto elemento
    if (*(s + 3) != '\0') // '\0' é o caractere nulo que marca o final da string
    {
        printf("%c\n", *(s + 3));
    }
    else
    {
        printf("A string não tem um quarto caractere.\n");
    }
}
