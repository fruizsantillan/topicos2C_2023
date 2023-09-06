#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Estructuras

typedef struct {
    int d;
    int m;
    int a;
} Fecha;

//Funciones

void ingresarFecha(Fecha* f);
void intercambiar(int* x, int* y);
bool esFechaValida(Fecha* fecha);
int cantDiasMes(int m, int a);
bool esBisiesto(int a);
Fecha sumarDiasAFecha(const Fecha* fecha, int dias);

#endif // MAIN_H_INCLUDED
