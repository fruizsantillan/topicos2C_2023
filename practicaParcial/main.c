#include "funciones.h"

int main()
{
    //Genero archivos para probar
    generarProductos("productos.bin");
    generarMovimientos("movimientos.bin");
    generarIndice("productos.bin", "productos.idx");

    Lista lista;
    //crear lista
    listaCrear(&lista, sizeof(int));

    //crear indice?
    //mergear productos
    //actualizar precios

    return 0;
}
