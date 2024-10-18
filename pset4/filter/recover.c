#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Verifica se o número de argumentos é válido
    if (argc != 2)
    {
        fprintf(stderr, "Uso: ./recover imagem\n");
        return 1;
    }

    // Abre o arquivo de imagem forense para leitura
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Não foi possível abrir o arquivo %s para leitura.\n", argv[1]);
        return 1; // Retorna 1 em caso de falha
    }

    // Variáveis para controle de arquivos JPEG
    FILE *img = NULL;
    BYTE buffer[BLOCK_SIZE];
    char filename[8];
    int counter = 0;
    int writing = 0;

    // Lê blocos de 512 bytes até o final do arquivo
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Verifica se o bloco é o início de um novo arquivo JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Fecha o arquivo JPEG anterior, se estiver aberto
            if (img != NULL)
            {
                fclose(img);
            }

            // Cria um novo arquivo JPEG
            sprintf(filename, "%03i.jpg", counter++);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fprintf(stderr, "Não foi possível criar o arquivo %s.\n", filename);
                fclose(file);
                return 1;
            }

            // Marca que está gravando no arquivo
            writing = 1;
        }

        // Escreve o bloco no arquivo JPEG atual, se estiver aberto
        if (writing)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    // Fecha os arquivos
    fclose(file);
    if (img != NULL)
    {
        fclose(img);
    }

    return 0;
}
