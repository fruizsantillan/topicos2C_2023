#include "matrices.h"

int main() {
/*    int matriz[4][4] = {
            {1, 2, 3, 4},
            {5, 6,7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}};*/

    int** matriz = (int**)crearMatriz(4, 4, sizeof(int));

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            matriz[i][j] = i * 4 + j + 1;
        }
    }

    mostrarMatriz(matriz, 4, 4);
    printf("Suma diagonal principal: %d\n", sumarDiagonalPrincipal(matriz, 4));
//    printf("Suma triangular inferior: %d\n", sumarTriangularInferior(4, matriz));;
//    printf("Suma triangular superior: %d\n", sumarTriangularSuperior(4, matriz));
//    printf("Suma diagonal secundaria: %d\n", sumarDiagonalSecundaria(4, matriz));

    destruirMatriz((void**)matriz, 4);

    int** m1 = (int**) crearMatriz(2, 4, sizeof(int));
    int** m2 = (int**) crearMatriz(4, 3, sizeof(int));

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++) {
            m1[i][j] = i * 4 + j + 1;
        }
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++) {
            m2[i][j] = i * 3 + j + 1;
        }
    }

    int** mProd = productoMatrices(m1, m2, 2, 4, 3);
    mostrarMatriz(mProd, 2, 3);

    destruirMatriz((void**)m1, 2);
    destruirMatriz((void**)m2, 4);
    destruirMatriz((void**)mProd, 2);

    return 0;
}
