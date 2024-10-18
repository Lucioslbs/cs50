#include <stdint.h>

#include <stdio.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])

{

    // Verificar o uso

    if (argc != 2)

    {

        return 1;

    }

    // Abrir o arquivo

    FILE *file = fopen(argv[1], "r");

    if (!file)

    {

        return 1;

    }

    // Ler os primeiros 3 bytes

    BYTE bytes[3];

    fread(bytes, sizeof(BYTE), 3, file);

    // Verificar os três primeiros bytes

    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff)

    {

        printf("Talvez\n");

    }

    else

    {

       printf("Não\n");

    }

    // Fechar o arquivo

    fclose(file);

}
