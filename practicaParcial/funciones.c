#include "funciones.h"

//**************************************************************
//                  Funciones de Lista
//**************************************************************

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

void listaDestruir(Lista* pl)
{
    free(pl->vec);
}

int listaInsertarEnOrdAsc(Lista* pl, void* elem, Cmp cmp)
{
    if(pl->ce == pl->cap)
    {
        size_t nuevaCap = pl->cap * 2;
        void* nuevoVec = realloc(pl->vec, nuevaCap * pl->tamElem);

        if(!nuevoVec)
            return SIN_MEM;

        pl->vec = nuevoVec;
        pl->cap = nuevaCap;
    }

    void* i = pl->vec;
    void* ult = pl->vec + (pl->ce - 1) * pl->tamElem;

    while(i <= ult && cmp(elem, i) > 0)
        i += pl->tamElem;

    if(cmp(i, ult) <= 0 && cmp(elem, i) == 0)
        return DUPLICADO;

    for(void* j = ult; j >= i; j -= pl->tamElem)
        memcpy(j + pl->tamElem, j, pl->tamElem);

    memcpy(i, elem, pl->tamElem);

    pl->ce++;

    return TODO_OK;
}

bool listaGrabarEnArchivo(Lista* pl, const void* nomArchivo)
{
    FILE* arch = fopen(nomArchivo, "wb");

    if(!arch)
    {
        printf("ERROR. No se pudo grabar el archivo\n");
        return false;
    }

    fwrite(pl->vec, sizeof(pl->tamElem), sizeof(pl->ce), arch);

    fclose(arch);

    return true;
}

//**************************************************************
//                  Funciones de archivos
//**************************************************************

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

    listaGrabarEnArchivo(&listaIndProd, nomIdx);
    fclose(archProds);
    listaDestruir(&listaIndProd);
}

//**************************************************************
//                  Funciones de comparacion
//**************************************************************
int cmpIndProd(const void* a, const void* b)
{
    IndProd* indProdA = (IndProd*)a;
    IndProd* indProdB = (IndProd*)b;

    return strcmp(indProdA->codigo, indProdB->codigo);
}

