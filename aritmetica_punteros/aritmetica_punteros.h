#ifndef ARITMETICA_PUNTEROS_H_INCLUDED
#define ARITMETICA_PUNTEROS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define SIN_MEM -1
#define DUPLICADO -2
#define TODO_OK 0

#define TAM 7

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int vec[TAM];
    int ce;
}Lista;

int insertar_ordenado(Lista * pLista, int elem);
bool eliminar_lista_ordenado(Lista* pLista, int elem);
#endif // ARITMETICA_PUNTEROS_H_INCLUDED
