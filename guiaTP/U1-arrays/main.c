#include "arrays.h"

int main() {
    int vec[TAM] = {1, 2, 3, 6, 7, 8};
    int ce = 6;
    int num = 6;
    int pos = 3;
    muestraArrayEnteros(vec, ce);
    arrayInsertaOrdenadoAsc(vec, ce, num);
    muestraArrayEnteros(vec, ce + 1);
    return 0;
}
