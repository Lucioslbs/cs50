#include <cs50.h>
#include <stdio.h>

const int TOTAL = 3;

float average(int length, int array[])
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum = sum + array[i];
    }
    return sum / (float) length;
}

int main(void)
{   // Sem Arrays
    // int score1 = 72;
    // int score2 = 73;
    // int score3 = 33;

    // Usando Arrays
    int scores[TOTAL];
    for (int i = 0; i < TOTAL; i++)
    {
        scores[i] = get_int("Score: ");
    }

    printf("Average: %.2f\n", average(TOTAL, scores));
}


