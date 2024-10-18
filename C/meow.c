#include <stdio.h>
// Prototype
void meow(int n);

int main(void)
{
    meow(3);
    return 0;
}

void meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}


