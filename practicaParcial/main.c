#include "funciones.h"

int main()
{
    //Genero archivos para probar
    generarProductos("productos.bin");
    generarMovimientos("movimientos.bin");

    Lista lista;
    //crear lista
    listaCrear(&lista, sizeof(int));

    //crear indice
    generarIndice("productos.bin", "productos.idx");

    //mergear productos

    //actualizar precios

    return 0;
}
