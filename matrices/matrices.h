#ifndef MATRICES_MATRICES_H
#define MATRICES_MATRICES_H

#include <stdio.h>
#include <stdlib.h>

void mostrarMatriz(int** mat, int filas, int columnas);

int sumarDiagonalPrincipal(int** matriz, int orden);
int sumarTriangularInferior(int orden, int matriz[][orden]);
int sumarTriangularSuperior(int orden, int matriz[][orden]);
int sumarDiagonalSecundaria(int orden, int matriz[][orden]);
void** crearMatriz(int filas, int columnas, size_t tamElem);
void destruirMatriz(void** matriz, int filas);
int** productoMatrices(int** mat1, int** mat2, int filasM1, int columnasM1FilasM2, int colM2);

#endif //MATRICES_MATRICES_H
