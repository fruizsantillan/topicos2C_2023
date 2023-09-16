#include "memoria_dinamica.h"

int main()
{
    /*
    memoria estática:
        la memoria se asigna en el stack.
        el stack pointer apunta al último dato cargado en el stack, para saber donde cargar el nuevo dato.

    memoria dinámica:
        heap
        devuelve la dirección de memoria del 1er byte reservado <- malloc(cant bytes); stdlib.h
        ej: char* cad = malloc(cantBytes);
        Alumno* alu = malloc(sizeof(Alumno) * 10) -> ejemplo de vector de alumno de 10

        free(direccionDeMemoriaDelBloque);
        ej: free(alu);

        ventajas:
            la variable vive hasta donde yo quiera
            puedo hacer que una función declare una variable y devuelva la misma
            en tiempo de ejecución defino el tamaño

        alu = realloc(alu, sizeof(Alumno) * 20);

        realloc reasigna la memoria
    */

    return 0;
}
