#include "cadenas.h"

int main()
{
    char* cadANormalizar = "{}:<>hola\t$$%mundo@#$";
    char cadNormalizada[100];

    normalizar(cadANormalizar, cadNormalizada);

    printf("%s", cadNormalizada);
    return 0;
}
