import sys
import csv


def main():
    # Verifica se o número correto de argumentos foi passado
    if len(sys.argv) != 3:
        print("Usage: python dna.py databases.csv sequences.txt")
        sys.exit(1)

    # Extrai os nomes dos arquivos dos argumentos de linha de comando
    database_file = sys.argv[1]
    sequence_file = sys.argv[2]

    # Lê os dados dos arquivos CSV e de sequência de DNA
    database = read_csv(database_file)
    sequence = read_dna(sequence_file)

    # Analisa a sequência de DNA em relação ao banco de dados
    analyze_dna(database, sequence)


def read_csv(filename):
    # Lê o arquivo CSV e retorna os dados como uma lista de dicionários
    with open(filename, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        return list(reader)


def read_dna(filename):
    # Lê o arquivo de sequência de DNA e retorna seu conteúdo como uma string
    with open(filename) as file:
        return file.read().strip()


def analyze_dna(database, sequence):
    # Percorre cada pessoa no banco de dados
    for person in database:
        match = True
        # Compara cada padrão STR para a pessoa atual
        for key in person.keys():
            if key != "name":
                str_count = count_str(sequence, key)
                if str_count != int(person[key]):
                    match = False
                    break
        # Se houver uma correspondência, imprime o nome da pessoa e retorna
        if match:
            print(person["name"])
            return
    # Se nenhuma correspondência for encontrada, imprime "No match"
    print("No match")


def count_str(sequence, str_pattern):
    # Conta o número máximo de repetições consecutivas de um padrão STR na sequência de DNA
    max_count = 0
    current_count = 0
    str_length = len(str_pattern)
    i = 0
    while i < len(sequence):
        # Se a sequência atual corresponder ao padrão STR
        if sequence[i:i+str_length] == str_pattern:
            current_count += 1
            i += str_length
        else:
            # Se a sequência atual não corresponder ao padrão STR
            current_count = 0
            i += 1
        # Atualiza a contagem máxima
        if current_count > max_count:
            max_count = current_count
    return max_count


if __name__ == "__main__":
    main()
