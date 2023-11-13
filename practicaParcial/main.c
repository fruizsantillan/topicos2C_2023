#include "funciones.h"

int main()
{
    //Genero archivos para probar
    const char nomProd[] = "productos.bin";
    const char nomMovs[] = "movimientos.txt";
    const char nomIndex[] = "productos.idx";

    generarProductos(nomProd);
    generarMovimientos(nomMovs);

    mostrarProductos(nomProd);
    Lista lista;
    //crear lista
    listaCrear(&lista, sizeof(int));

    //crear indice
    generarIndice(nomProd, nomIndex);

    //mergear productos

    //actualizar precios

    return 0;
}
