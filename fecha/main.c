#include "main.h"

int main()
{
    Fecha fechaInicio;
    ingresarFecha(&fechaInicio);
    int dias = ingresarEnteroPos();
    Fecha fSuma = sumarDiasAFecha(&fechaInicio, dias);
    mostrarFecha(&fSuma);

    return 0;
}

void ingresarFecha(Fecha* f)
{
    //Puts es mas eficiente que printf cuando se trata de texto solamente, sin %
    puts("Ingrese una fecha(D/M/A): ");
    scanf("%d/%d/%d", &f->d, &f->m, &f->a);

    while(!esFechaValida(f))
    {
        puts("Fecha invalida, ingresela de nuevo: ");
        scanf("%d/%d/%d", &f->d, &f->m, &f->a);
    }
}

void intercambiar(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

bool esFechaValida(Fecha* fecha)
{
    if(fecha->a >= 1601){
        if(fecha->m >= 1 && fecha->m <= 12){
            if(fecha->d >= 1 && fecha->d <= cantDiasMes(fecha->m, fecha->a)){
                return true;
            }
        }
    }

    return false;
}

int cantDiasMes(int m, int a)
{
    int dm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(m == 2 && esBisiesto(a))
        return 29;

    return dm[m];
}

bool esBisiesto(int a)
{
    return a % 4 == 0 && (a % 100 != 0 || a % 400 == 0);
}

Fecha sumarDiasAFecha(const Fecha* fecha, int dias)
{
    Fecha fSuma = *fecha;
    int cdm;

    fSuma.d += dias;

    while(fSuma.d > (cdm = cantDiasMes(fSuma.m, fSuma.a)))
    {
        fSuma.d -= cdm;
        fSuma.m++;
        if(fSuma.m > 12)
        {
            fSuma.m = 1;
            fSuma.a++;
        }
    }

    return fSuma;
}
