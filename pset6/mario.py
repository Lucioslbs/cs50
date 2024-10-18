from cs50 import get_int

# Solicitar altura do usuário
height = get_int("Height: ")

# Verificar se a altura está dentro do intervalo desejado
while height not in range(1, 9):
    print("A altura deve estar entre 1 e 8")
    height = get_int("Height: ")

# Imprimir linhas de hashtags
for i in range(height):
    print(" " * (height - i - 1) + "#" * (i + 1))
