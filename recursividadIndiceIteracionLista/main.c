#include "funciones.h"

int main()
{
    /*
    RECURSIVIDAD: Hacer referencia a lo mismo que se puede definir.
                  Caso tipico: funcion factorial.
                  Ej. 5! = 5 * 4 * 3 * 2 * 1
                  5! = 5 * 4!
                  n! = n * (n - 1)! | Si n > 1
                  n! = 1 si n <= 1
    */
    int n = 5;

    printf("%d! = %d\n", n, factorialRec(n));

    int x = 16, y = 24;

    printf("DCM(%d, %d) = %d", x, y , dmcRec(x, y));
    return 0;
}
