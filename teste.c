#include <stdio.h>

void f()
{
    static int i = 0;

    i++;
    printf("%d\n", i);
}

int main(void)
{
    f();
    f();

    return (0);
}