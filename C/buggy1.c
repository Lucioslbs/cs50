#include <cs50.h>
#include <stdio.h>

// prototype
int get_negative_int(void);

int main(void)
{
    // get negative from user
    int i = get_negative_int();
    printf("%i\n", i);
}

int get_negative_int(void)
{
    int n;
    do
    {
        n = get_int("Negative Integer: ");
    }
    while (n < 0);
    return n;
}
