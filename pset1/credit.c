#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Função para calcular o dígito de controle
int calcularDigitoControle(string numero);

int main(void)
{
    // Solicitar o número do cartão de crédito
    string numeroCartao = get_string("Número: ");

    // Remover hífens do número do cartão
    string numeroLimpo = "";
    for (int i = 0, n = strlen(numeroCartao); i < n; i++)
    {
        if (numeroCartao[i] >= '0' && numeroCartao[i] <= '9')
        {
            numeroLimpo += numeroCartao[i];
        }
    }

    // Calcula o total dos dígitos
    int total = calcularDigitoControle(numeroLimpo);

    // Verifica se o número é válido e imprime o tipo de cartão
    if (total % 10 == 0)
    {
        if ((strncmp(numeroLimpo, "34", 2) == 0 || strncmp(numeroLimpo, "37", 2) == 0) && strlen(numeroLimpo) == 15)
        {
            printf("AMEX\n");
        }
        else if ((strncmp(numeroLimpo, "51", 2) == 0 || strncmp(numeroLimpo, "52", 2) == 0 ||
                  strncmp(numeroLimpo, "53", 2) == 0 || strncmp(numeroLimpo, "54", 2) == 0 ||
                  strncmp(numeroLimpo, "55", 2) == 0) && strlen(numeroLimpo) == 16)
        {
            printf("MASTERCARD\n");
        }
        else if ((strncmp(numeroLimpo, "4", 1) == 0) && (strlen(numeroLimpo) == 13 || strlen(numeroLimpo) == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

int calcularDigitoControle(string numero)
{
    int soma = 0;
    int multiplicaPorDois = 0;
    int contador = 0;

    // Iterar pelos dígitos do número
    for (int i = strlen(numero) - 1; i >= 0; i--)
    {
        int digito = numero[i] - '0';

        // Verificar se o dígito deve ser multiplicado por 2
        if (contador % 2 == 1)
        {
            multiplicaPorDois = digito * 2;

            // Se o resultado da multiplicação tem dois dígitos, somar esses dígitos
            if (multiplicaPorDois >= 10)
            {
                soma += multiplicaPorDois % 10;
                multiplicaPorDois /= 10;
            }

            soma += multiplicaPorDois;
        }
        else
        {
            soma += digito;
        }

        contador++;
    }

    return soma % 10;
}
