#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#define SIN_MEM -1
#define DUPLICADO -2
#define TODO_OK 0

#define TAM 5;

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int vec[TAM];
    int ce;
}Lista;

int insertar_ordenado(Lista * pLista, int elem);

#endif // FUNCIONES_H_INCLUDED
