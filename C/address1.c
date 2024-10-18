#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string s = "HI!";
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
}
