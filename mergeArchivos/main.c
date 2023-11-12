#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG_PRODS 1
#define ARG_MOVS 2

// Merge

#define CANT_PRODS 5
#define CANT_MOVS 8
#define TODO_OK 0
#define ERR_ARCHIVO 1


typedef struct
{
    char codigo[11];
    char descripcion[31];
    float precio;
    int stock;
}
Producto;


typedef struct
{
    char codigo[11];
    int cantidad;
    float precio;
}
Movimiento;


void generarProductos(const char* nomProds);
void generarMovimientos(const char* nomMovs);
int actualizarStock(const char* nomProds, const char* nomMovs);
void procesarProductoNuevo(Movimiento* mov, FILE* archMovs, FILE* archProdsTemp);
int mostrarProductos(const char* nomProds);


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Cantidad de argumentos incorrecta\n");
        return 1;
    }

    generarProductos(argv[ARG_PRODS]);
    generarMovimientos(argv[ARG_MOVS]);

    actualizarStock(argv[ARG_PRODS], argv[ARG_MOVS]);

    mostrarProductos(argv[ARG_PRODS]);

    return 0;
}


void generarProductos(const char* nomProds)
{
    Producto prods[CANT_PRODS] =
    {
        {"00", "Higo", 100.0, 100},
        {"04", "Banana", 200.0, 100},
        {"07", "Pera", 300.0, 50},
        {"09", "Manzana", 400.0, 70},
        {"14", "Durazno", 500.0, 90}
    };

    FILE* archProds = fopen(nomProds, "wb");

    if(archProds == NULL)
    {
        printf("No se pudo abrir el archivo de productos\n");
        exit(1);
    }

    fwrite(prods, sizeof(Producto), CANT_PRODS, archProds);

    fclose(archProds);
}


void generarMovimientos(const char* nomMovs)
{
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

    FILE* archMovs = fopen(nomMovs, "wb");

    if(archMovs == NULL)
    {
        printf("No se pudo abrir el archivo de movimientos\n");
        exit(1);
    }

    fwrite(movs, sizeof(Movimiento), CANT_MOVS, archMovs);

    fclose(archMovs);
}


int actualizarStock(const char* nomProds, const char* nomMovs)
{
    FILE* archProds = fopen(nomProds, "rb");

    if(archProds == NULL)
    {
        printf("No se pudo abrir el archivo de productos\n");
        return ERR_ARCHIVO;
    }

    FILE* archMovs = fopen(nomMovs, "rb");

    if(archMovs == NULL)
    {
        printf("No se pudo abrir el archivo de movimientos\n");
        return ERR_ARCHIVO;
    }

    FILE* archProdsTemp = fopen("productos.tmp", "wb");

    if(archProdsTemp == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return ERR_ARCHIVO;
    }

    Producto prod;
    Movimiento mov;
    int comp;

    fread(&prod, sizeof(Producto), 1, archProds);
    fread(&mov, sizeof(Movimiento), 1, archMovs);
    while(!feof(archProds) && !feof(archMovs))
    {
        comp = strcmp(prod.codigo, mov.codigo);

        if(comp == 0)
        {
            prod.stock += mov.cantidad;
            prod.precio = mov.precio;
            fread(&mov, sizeof(Movimiento), 1, archMovs);
        }

        if(comp < 0) // Prod sin movs
        {
            fwrite(&prod, sizeof(Producto), 1, archProdsTemp);
            fread(&prod, sizeof(Producto), 1, archProds);
        }

        if(comp > 0) // Prod nuevo
        {
            procesarProductoNuevo(&mov, archMovs, archProdsTemp);
        }
    }

    while(!feof(archProds)) // Prods sin movs.
    {
        fwrite(&prod, sizeof(Producto), 1, archProdsTemp);
        fread(&prod, sizeof(Producto), 1, archProds);
    }

    while(!feof(archMovs)) // Prods nuevos.
    {
        procesarProductoNuevo(&mov, archMovs, archProdsTemp);
    }

    fclose(archProds);
    fclose(archMovs);
    fclose(archProdsTemp);

    remove(nomProds);
    rename("Productos.tmp", nomProds);

    return TODO_OK;
}


void procesarProductoNuevo(Movimiento* mov, FILE* archMovs, FILE* archProdsTemp)
{
    Producto prodNuevo;
    prodNuevo.descripcion[0] = '\0';
    strcpy(prodNuevo.codigo, mov->codigo);
    prodNuevo.stock = mov->cantidad;
    prodNuevo.precio = mov->precio;

    fread(mov, sizeof(Movimiento), 1, archMovs);
    while(!feof(archMovs) && strcmp(mov->codigo, prodNuevo.codigo) == 0)
    {
        prodNuevo.stock += mov->cantidad;
        prodNuevo.precio = mov->precio;
        fread(mov, sizeof(Movimiento), 1, archMovs);
    }

    fwrite(&prodNuevo, sizeof(Producto), 1, archProdsTemp);
}


int mostrarProductos(const char* nomProds)
{
    FILE* archProds = fopen(nomProds, "rb");

    if(archProds == NULL)
    {
        printf("No se pudo abrir el archivo de productos\n");
        return ERR_ARCHIVO;
    }

    Producto prod;

    fread(&prod, sizeof(Producto), 1, archProds);
    while(!feof(archProds))
    {
        printf("%2s - %10s - %5f - %3d\n", prod.codigo, prod.descripcion, prod.precio, prod.stock);
        fread(&prod, sizeof(Producto), 1, archProds);
    }

    fclose(archProds);

    return TODO_OK;
}
