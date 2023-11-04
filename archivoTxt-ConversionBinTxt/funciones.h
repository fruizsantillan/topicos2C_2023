#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TODO_OK 0
#define ERR_ARCH 1
#define ERR_MEM 2
#define ERR_LINEA_LARGA 3

#define TAM_APYN 50
#define TAM_LINEA 1000

typedef struct
{
    int dia;
    int mes;
    int anio;
}
Fecha;

typedef struct
{
    int dni;
    char apyn[TAM_APYN + 1];
    char sexo;
    Fecha fechaIngreso;
    float sueldo;
}
Empleado;

typedef void(*BinATxt)(const void* registro, FILE* archivoTxt);
typedef int(*TxtABin)(char* linea, void* registro, bool* errorFatal);

//Para BIN A TXT
void empleadoBinATxtV(const void* registro, FILE* archivoTxt);
void empleadoBinATxtF(const void* registro, FILE* archivoTxt);
int archivoBinATxt(const char* nombreBin, const char* nombreTxt, BinATxt binATxt, size_t tamReg);

//Para TXT a BIN
int empleadoTxtVABin(char* linea, void* registro, bool* errorFatal);
int empleadoTxtFABin(char* linea, void* registro, bool* errorFatal);
int archivoTxtABin(const char* nombreTxt, const char* nombreBin, TxtABin txtABin, size_t tamReg);


#endif // FUNCIONES_H_INCLUDED
