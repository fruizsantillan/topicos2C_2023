#include "funciones.h"

int factorial(int n)
{
    int fact = 1;

    for(int i = n; i > 1; i--)
    {
        fact *= i;
    }

    return fact;
}

int factorialRec(int n)
{
    if(n <= 1)
    {
        return 1;
    }

    return n * factorialRec(n - 1);
}

int dmcRec(int x, int y)
{
    if(y == 0)
    {
        return x;
    }

    return dmcRec(y, x % y);
}
