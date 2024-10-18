#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Percorre cada pixel na imagem
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calcula a média dos valores de vermelho, verde e azul
            int average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;

            // Atribui a média a todos os canais de cor do novo pixel
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Pecorre cada linha da imagem
    for (int i = 0; i < height; i++)
    {
        // Define dois ponteiros para o inicio e o final da cada linha
        int start = 0;
        int end = width - 1;

        // Pecorre a metade da largura da imagem
        while (start < end)
        {
            // Troca os pixel da extremidade esquerda com os da extremidade direita
            RGBTRIPLE temp = image[i][start];
            image[i][start] = image[i][end];
            image[i][end] = temp;

            // Avança o ponteiro de inicio e retrocede o ponteiro de fim
            start++;
            end--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Cria uma cópia temporária da imagem original
    RGBTRIPLE temp[height][width];
    // Percorre cada pixel na imagem
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            // Percorre os pixels vizinhos ao redor do pixel atual
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int newi = i + di;
                    int newj = j + dj;

                    // Verifica se o pixel vizinho está dentro dos limites da imagem
                    if (newi >= 0 && newi < height && newj >= 0 && newj < width)
                    {
                        sumRed += image[newi][newj].rgbtRed;
                        sumGreen += image[newi][newj].rgbtGreen;
                        sumBlue += image[newi][newj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calcula os valores médios de vermelho, verde e azul para o pixel atual
            temp[i][j].rgbtRed = round((float) sumRed / count);
            temp[i][j].rgbtGreen = round((float) sumGreen / count);
            temp[i][j].rgbtBlue = round((float) sumBlue / count);
        }
    }

    // Copia os valores da imagem temporária de volta para a imagem original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Cria uma cópia temporária da imagem original
    RGBTRIPLE temp[height][width];
    // Define os kernels para detecção de bordas horizontal e vertical
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Percorre cada pixel na imagem
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gx_red = 0, Gy_red = 0;
            int Gx_green = 0, Gy_green = 0;
            int Gx_blue = 0, Gy_blue = 0;

            // Percorre os pixels vizinhos ao redor do pixel atual
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int newi = i + di;
                    int newj = j + dj;

                    // Verifica se o pixel vizinho está dentro dos limites da imagem
                    if (newi >= 0 && newi < height && newj >= 0 && newj < width)
                    {
                        // Aplica os kernels de Sobel aos canais de cor RGB
                        Gx_red += Gx[di + 1][dj + 1] * image[newi][newj].rgbtRed;
                        Gy_red += Gy[di + 1][dj + 1] * image[newi][newj].rgbtRed;

                        Gx_green += Gx[di + 1][dj + 1] * image[newi][newj].rgbtGreen;
                        Gy_green += Gy[di + 1][dj + 1] * image[newi][newj].rgbtGreen;

                        Gx_blue += Gx[di + 1][dj + 1] * image[newi][newj].rgbtBlue;
                        Gy_blue += Gy[di + 1][dj + 1] * image[newi][newj].rgbtBlue;
                    }
                }
            }

            // Calcula os gradientes de intensidade para cada canal de cor
            int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            // Limita os valores a 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            // Define os valores resultantes na imagem temporária
            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtBlue = blue;
        }
    }

    // Copia os valores da imagem temporária de volta para a imagem original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Apply sepia filter to image
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate sepia values for each color channel
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen +
                                 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen +
                                   0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen +
                                  0.131 * image[i][j].rgbtBlue);

            // Cap the values at 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Assign sepia values to the pixel
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}
