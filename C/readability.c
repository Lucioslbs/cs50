#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void countLettersWordsSentences(string text, int *letters, int *words, int *sentences);
float calculateIndex(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");
    int letters = 0, words = 1, sentences = 0;

    countLettersWordsSentences(text, &letters, &words, &sentences);

    float index = calculateIndex(letters, words, sentences);

    printf("Index: %.2f\n", index);

    if (index < 1)
    {
        printf("Less than Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

void countLettersWordsSentences(string text, int *letters, int *words, int *sentences)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            (*letters)++;
        }
        else if (isspace(text[i]))
        {
            (*words)++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            (*sentences)++;
        }
    }
}

float calculateIndex(int letters, int words, int sentences)
{
    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;
    return 0.0588 * L - 0.296 * S - 15.8;
}
