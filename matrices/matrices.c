#include "matrices.h"

int sumarDiagonalPrincipal(int** matriz, int orden) {
    int suma = 0;

    for (int i = 0; i < orden; i++)
        suma += matriz[i][i];

    return suma;
}

int sumarTriangularInferior(int orden, int matriz[][orden]) {
    int suma = 0;

    for(int i = 1; i < orden; i++) {
        for(int j = 0; j < i; j++) {
            suma += matriz[i][j];
        }
    }

    return suma;
}

int sumarTriangularSuperior(int orden, int matriz[][orden]) {
    int suma = 0;

    for(int i = 0; i < orden - 1; i++) {
        for(int j = i + 1; j < orden; j++) {
            suma += matriz[i][j];
        }
    }

    return suma;
}

int sumarDiagonalSecundaria(int orden, int matriz[][orden]) {
    int suma = 0;

    for(int i = 0; i < orden; i++) {
        suma += matriz[i][orden - 1 - i];
    }

    return suma;
}

void** crearMatriz(int filas, int columnas, size_t tamElem) {
    void** mat = malloc(filas * sizeof(void*));

    if(!mat)
        return NULL;

    for(int i = 0; i < filas; i++) {
        mat[i] = malloc(columnas * tamElem);

        if(!mat[i]){
            destruirMatriz(mat, i);
            return NULL;
        }
    }

    return mat;
}

void destruirMatriz(void** matriz, int filas) {
    for(int i = 0; i < filas; i++){
        free(matriz[i]);
    }

    free(matriz);
}

void mostrarMatriz(int** mat, int filas, int columnas){
    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < columnas; j++){
            printf("%4d", mat[i][j]);
        }
        putchar('\n');
    }
}

int** productoMatrices(int** mat1, int** mat2, int filasM1, int columnasM1FilasM2, int colM2){
    int** mProd = (int**)crearMatriz(filasM1, colM2, sizeof(int));

    if(!mProd)
        return NULL;

    for(int i = 0; i < filasM1; i++){
        for(int j = 0; j < colM2; j++){
            mProd[i][j] = 0;
            for(int k = 0; k < columnasM1FilasM2; k++){
                mProd[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return mProd;
}