#ifndef U1_ARRAYS_ARRAYS_H
#define U1_ARRAYS_ARRAYS_H

#define TAM 7

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
void muestraArrayEnteros(int* vec, int ce);

void arrayInsertaEnPosicion(int* vec, int ce, int num, int pos);
//Ejercicio 1.1 Desarrollar una función que inserte un elemento en un arreglo de enteros, dada la posición de inserción.

void arrayInsertaOrdenadoAsc(int* vec, int ce, int num);
//Ejercicio 1.2 Desarrollar una función que inserte un elemento en un arreglo de enteros,
//ordenado en forma ascendente, de forma de no alterar el orden.

void eliminaElemPosicion(int* vec, int ce, int pos);
//Ejercicio 1.3 Desarrollar una función que elimine el elemento que ocupa una determinada posición de un arreglo de enteros.

void eliminaPrimerAparicion(int* vec, int ce, int elem);
//Ejercicio 1.4 Desarrollar una función que elimine la primera aparición de un elemento determinado de un arreglo de enteros.

void eliminaTodasApariciones(int * vec, int ce, int elem);
//Ejercicio 1.5 Desarrollar una función que elimine todas las apariciones de un determinado elemento de un arreglo de enteros.

bool esPalindromo(char* palabra);
//Ejercicio 1.6 Desarrollar una función que determine si una cadena de caracteres es un palíndromo.
#endif //U1_ARRAYS_ARRAYS_H
