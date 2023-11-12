#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CANT_PRODS 5
#define CANT_MOVS 8

typedef struct
{
    void* vec;
    int ce;
    size_t cap;
    size_t tamElem;
}
Lista;

typedef struct
{
    char codigo[11];
    char descripcion[31];
    float precio;
    int stock;
}
Producto;

typedef struct
{
    char codigo[11];
    int cantidad;
    float precio;
}
Movimiento;

typedef struct
{
    char codigo[11];
    unsigned nroReg;
}
IndProd;

bool listaCrear(Lista* pl, size_t tamElem);
bool listaCrearDeArchivo(Lista* pl, const char* nomArchivo, size_t tamElem);

//Crear archivos de prueba
void generarProductos(const char* nomArchivo);
void generarMovimientos(const char* nomArchivo);
void generarIndice(const char* nomProds, const char* nomIdx);

//Funciones de comparacion
int cmpIndProd(const void* a, const void* b);

#endif // FUNCIONES_H_INCLUDED
