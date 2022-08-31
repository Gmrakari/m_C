#include <stdio.h>

void primeNumfunc()
{
    int number = 0;
    int divisor = 0;
    int primeArr;
    for (number = 3; number <= 100; number += 2)
    {
        for (divisor = 3; divisor < number; divisor += 2)
        {
            if (number % divisor == 0)
            {
                break;
            }
        }
        if (divisor >= number)
        {
            printf("prime number is %d\n", number);
        }
    }
}

int main()
{
    primeNumfunc();
}