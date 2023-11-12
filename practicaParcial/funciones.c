#include "funciones.h"

bool listaCrear(Lista* pl, size_t tamElem)
{
    pl->vec = malloc(8 * tamElem);

    if(!pl->vec)
    {
        return false;
    }

    pl->ce = 0;
    pl->cap = 8;
    pl->tamElem = tamElem;

    return true;
}

//*****************************************

void generarProductos(const char* nomArchivo)
{
    FILE* fp = fopen(nomArchivo, "wb");

    if(!fp)
    {
        printf("ERROR. No se pudo crear el archivo de productos");
        exit(1);
    }

    Producto prods[CANT_PRODS] =
    {
        {"00", "Higo", 100.0, 100},
        {"04", "Banana", 200.0, 100},
        {"07", "Pera", 300.0, 50},
        {"09", "Manzana", 400.0, 70},
        {"14", "Durazno", 500.0, 90}
    };

    fwrite(prods, sizeof(Producto), CANT_PRODS, fp);

    fclose(fp);
}

void generarMovimientos(const char* nomArch)
{
    FILE* archMovs = fopen(nomArch, "wb");

    if(!archMovs)
    {
        exit(1);
    }

    Movimiento movs[CANT_MOVS] =
    {
        {"01", 20, 120},
        {"07", 20, 330},
        {"07", -10, 340},
        {"08", 40, 200},
        {"12", 60, 250},
        {"12", -10, 270},
        {"15", 80, 340},
        {"15", 40, 350}
    };

    fwrite(movs, sizeof(Movimiento), CANT_MOVS, archMovs);

    fclose(archMovs);
}

void generarIndice(const char* nomProds, const char* nomIdx)
{
    Lista listaIndProd;
    listaCrear(&listaIndProd, sizeof(IndProd));

    FILE* archProds = fopen(nomProds, "rb");

    if(!archProds)
    {
        printf("ERROR. No se pudo abrir el archivo de productos\n");
        exit(1);
    }

    int contReg = 0;
    Producto prod;
    IndProd indProd;

    fread(&prod, sizeof(Producto), 1, archProds);

    while(!feof(archProds))
    {
        strcpy(indProd.codigo, prod.codigo);
        indProd.nroReg = contReg;
        listaInsertarEnOrdAsc(&listaIndProd, &indProd, cmpIndProd);
        contReg++;
        fread(&prod, sizeof(Producto), 1, archProds);
    }
}

//**************************************************************
//Funciones de comparacion
int cmpIndProd(const void* a, const void* b)
{
    IndProd* indProdA = (IndProd*)a;
    IndProd* indProdB = (IndProd*)b;

    return strcmp(indProdA->codigo, indProdB->codigo);
}

