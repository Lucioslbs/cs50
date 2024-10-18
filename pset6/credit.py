from cs50 import get_string

# Função para calcular o dígito de controle


def calcular_digito_controle(numero):
    soma = 0
    multiplica_por_dois = False
    contador = 0

    # Iterar pelos dígitos do número
    for i in range(len(numero) - 1, -1, -1):
        digito = int(numero[i])

        # Verifica se o dígito deve ser multiplicado por 2
        if multiplica_por_dois:
            digito *= 2

            # Se o resultado da multiplicação tem dois dígitos, somar esses dígitos
            if digito >= 10:
                soma += digito % 10
                soma += digito // 10
            else:
                soma += digito
            multiplica_por_dois = False
        else:
            soma += digito
            multiplica_por_dois = True

        contador += 1

    return soma % 10


# Solicitar o número do cartão de crédito
numero_cartao = get_string("Numero: ")

# Remover hífens do número do cartão e manter apenas os dígitos
numero_limpo = ""
for char in numero_cartao:
    if char.isdigit():
        numero_limpo += char

# Calcula o total dos dígitos
total = calcular_digito_controle(numero_limpo)

# Verifica se o número é válido e imprime o tipo de cartão
if total == 0:
    if numero_limpo.startswith("34") or numero_limpo.startswith("37") and len(numero_limpo) == 15:
        print("AMEX")
    elif numero_limpo.startswith("51") or numero_limpo.startswith("52") or numero_limpo.startswith("53") or numero_limpo.startswith("54") or numero_limpo.startswith("55") and len(numero_limpo) == 16:
        print("MASTERCARD")
    elif numero_limpo.startswith("4") and (len(numero_limpo) == 13 or len(numero_limpo) == 16):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
