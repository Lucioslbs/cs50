#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Protótipo da função para criptografar o texto
void encryptText(string plaintext, int key);

int main(int argc, string argv[])
{
    // Verifica se há exatamente um argumento de linha de comando
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Converte o argumento de linha de comando para um número inteiro
    int key = atoi(argv[1]);

    // Verifica se o argumento de linha de comando contém apenas dígitos
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Use: ./caesar key\n");
            return 1;
        }
    }

    // Solicita ao usuário o texto a ser criptografado
    string plaintext = get_string("plaintext: ");

    // Criptografa o texto fornecido
    encryptText(plaintext, key);

    return 0;
}

// Função para criptografar o texto
void encryptText(string plaintext, int key)
{
    printf("ciphertext: ");

    // Itera sobre cada caractere do texto
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        char encryptedChar = plaintext[i];

        // Verifica se o caractere é alfabético
        if (isalpha(plaintext[i]))
        {
            char base;
            // Determina se o caractere é maiúsculo ou minúsculo e define a base correta
            if (isupper(plaintext[i]))
            {
                base = 'A';
            }
            else
            {
                base = 'a';
            }

            // Aplica a cifra de César
            encryptedChar = ((plaintext[i] - base + key) % 26) + base;
        }

        // Imprime o caractere criptografado ou não criptografado
        printf("%c", encryptedChar);
    }

    printf("\n");
}
