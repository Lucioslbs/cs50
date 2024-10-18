from cs50 import get_float

# Funções para calcular o número de cada tipo de moeda


def calculate_quarters(cents):
    quarters = cents // 25
    return quarters


def calculate_dimes(cents):
    dimes = (cents % 25) // 10
    return dimes


def calculate_nickels(cents):
    nickels = ((cents % 25) % 10) // 5
    return nickels


def calculate_pennies(cents):
    pennies = ((cents % 25) % 10) % 5
    return pennies


# Solicita o valor do troco ao usuário e verifica se é válido
while True:
    change_owed = get_float("Change owed: ")
    if change_owed is not None and change_owed >= 0:
        break
    print("Input inválido. Por favor, insira um número não negativo.")

# Converte o valor para centavos
cents = int(change_owed * 100)

# Calcula o número de quarters a serem dados ao cliente
quarters = calculate_quarters(cents)
cents -= quarters * 25

# Calcula o número de dimes a serem dados ao cliente
dimes = calculate_dimes(cents)
cents -= dimes * 10

# Calcula o número de nickels a serem dados ao cliente
nickels = calculate_nickels(cents)
cents -= nickels * 5

# Calcula o número de pennies a serem dados ao cliente
pennies = cents

# Soma as moedas
coins = quarters + dimes + nickels + pennies

# Imprime o número total de moedas a serem dadas ao cliente
print(coins)
