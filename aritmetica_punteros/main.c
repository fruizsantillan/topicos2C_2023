#include "aritmetica_punteros.h"

int main()
{
    Lista vec[TAM] = {1, 3, 5, 9};
    int inserta = 4;

    for(int i = 0; i < TAM; i++)
        printf("%d ", vec[i]);

    printf("\n\n");

    insertar_ordenado(vec, inserta);

    for(int j = 0; j < TAM; j++)
        printf("%d ", vec[j]);

    return 0;
}
