#include "funciones.h"

/* aquí deben declarar sus funciones */
float calculaVelDesdePeriodo(const float periodo)
{
    return GRAVEDAD * (periodo / 2);
}

float calculaAlturaDesdeVelocidad(const float velocidad)
{
    return (pow(velocidad, 2)) / (2 * GRAVEDAD);
}

float calculaVelDesdeAltura(const float alturaMaxima)
{
    return sqrt(2 * alturaMaxima * GRAVEDAD);
}

float calculaTiempoDesdeVelocidad(const float velocidad)
{
    return velocidad / GRAVEDAD;
}

float calculaPendiente(const t_coordenada* coordenada1, const t_coordenada* coordenada2)
{
    return (coordenada2->y - coordenada1->y)/(coordenada2->x - coordenada1->x);
}

double milisegASeg(double miliseg)
{
    return miliseg / 1000.0;
}

double milisegAMin(double miliseg)
{
    return miliseg / 60000.0;
}

float calculaAlturaEnFuncionTiempo(const float tiempo, const float velocidad)
{
    return velocidad * tiempo + ((1/2) * GRAVEDAD * pow(tiempo, 2));
}

int calculaCantAlineamientos(t_juego* juegos)
{
    t_coordenada coordenadas[CANT_JUGADORES];
    int duracionAlineamiento = 0;
    int cantidadAlineamientos = 0;
    t_instante instanteAlineamiento;
    instanteAlineamiento.milisegundo = 0;
    instanteAlineamiento.segundo = 0;
    instanteAlineamiento.minuto = 0;

    juegos->cantidadAlineamientos = 0;

    for(int i = 0; i < CANT_JUGADORES; i++)
        coordenadas[i].x = juegos->jugadores[i].posicion;

    for(int j = 0; j < CANT_MILISEG; j++)
    {
        for(int k = 0; k < CANT_JUGADORES; k++)
        {
            coordenadas[k].y = (calculaAlturaEnFuncionTiempo(milisegASeg(j), juegos->jugadores[k].velocidadInicial));

        }

        float pendienteAB = fabs(calculaPendiente(&coordenadas[0], &coordenadas[1]));
        float pendienteBC = fabs(calculaPendiente(&coordenadas[1], &coordenadas[2]));

        if(pendienteAB - pendienteBC < DELTA)
        {
            instanteAlineamiento.milisegundo = j % 1000;
            instanteAlineamiento.segundo = milisegASeg(j);
            instanteAlineamiento.minuto = milisegAMin(j);

            juegos->alineamientos[juegos->cantidadAlineamientos].instanteInicial = instanteAlineamiento;
            juegos->alineamientos[juegos->cantidadAlineamientos].pendiente = pendienteAB - pendienteBC;
            juegos->alineamientos[juegos->cantidadAlineamientos].pos1 = coordenadas[0];
            juegos->alineamientos[juegos->cantidadAlineamientos].pos2 = coordenadas[1];
            juegos->alineamientos[juegos->cantidadAlineamientos].pos3 = coordenadas[2];
            juegos->cantidadAlineamientos++;
        }
    }
}


char obtenerValorPorTeclado(const char *opcionesValidas, const char* primerMensaje, const char* segundoMensaje)
{

    /* Aquí deben hacer todas las validaciones necesarias para que el reporte extendido se muestre a pedido del usuario */
    char teclaIngresada='s';

    return teclaIngresada;
}

void solucionTP(t_juego* juegos)
{
    //Datos brindados por el enunciado
    const float duracionJuegoEnMinutos = 3.0;
    const float periodosMessiSegundos[CANT_JUEGOS] = {1.5, 3.0, 5.0};
    const float alturaTotalAcunaMetros[CANT_JUEGOS] = {3.0, 11.11, 14.14};
    const int frecuenciasDiMariaMinuto[CANT_JUEGOS] = {10, 15, 30};

    for(int i = 0; i < CANT_JUEGOS; i++)
    {//Iteramos por la cantidad de juegos
        for(int j = 0; j < CANT_JUGADORES; j++)
        {//Iteramos por la cantidad de jugadores
            switch(j){//Realizamos los calculos segun el jugador
                case 0:
                //Messi. Nos dicen que patea cada x tiempo la pelota.
                    (juegos + i)->jugadores[j].velocidadInicial = calculaVelDesdePeriodo(periodosMessiSegundos[i]);
                    float alturaTempMessi = calculaAlturaDesdeVelocidad((juegos + i)->jugadores[j].velocidadInicial);
                    if(alturaTempMessi > 1.5)
                    {
                        (juegos + i)->jugadores[j].alturaGolpe = (juegos + i)->jugadores[j].estatura * 0.15;
                        (juegos + i)->jugadores[j].alturaMaximaDeLaPelota = alturaTempMessi + (juegos + i)->jugadores[j].alturaGolpe;
                    }
                    else
                    {
                        (juegos + i)->jugadores[j].alturaGolpe = (juegos + i)->jugadores[j].estatura * 0.1;
                        (juegos + i)->jugadores[j].alturaMaximaDeLaPelota = alturaTempMessi + (juegos + i)->jugadores[j].alturaGolpe;
                    }

                    (juegos + i)->jugadores[j].golpesPorMinuto = (duracionJuegoEnMinutos * 60) / periodosMessiSegundos[i];
                    //Ej. juego 1 para distancia total: Si la pelota recorre 3.01 m cada 1.5 seg -> en 180 seg ¿cuanta distancia recorre?
                    (juegos + i)->jugadores[j].distanciaRecorrida = ((duracionJuegoEnMinutos * 60) * (juegos + i)->jugadores[j].alturaMaximaDeLaPelota) / periodosMessiSegundos[i];
                    break;
                case 1:
                //DiMaria. Nos dicen que patea x veces por minuto la pelota.
                    (juegos + i)->jugadores[j].golpesPorMinuto = frecuenciasDiMariaMinuto[i];
                    const float periodoDiMariaSegundos = 60 / (juegos + i)->jugadores[j].golpesPorMinuto;

                    (juegos + i)->jugadores[j].velocidadInicial = calculaVelDesdePeriodo(periodoDiMariaSegundos);
                    float alturaTempDiMaria = calculaAlturaDesdeVelocidad((juegos + i)->jugadores[j].velocidadInicial);
                    if(alturaTempDiMaria > 1.5)
                    {
                        (juegos + i)->jugadores[j].alturaGolpe = (juegos + i)->jugadores[j].estatura * 0.15;
                        (juegos + i)->jugadores[j].alturaMaximaDeLaPelota = alturaTempDiMaria + (juegos + i)->jugadores[j].alturaGolpe;
                    }
                    else
                    {
                        (juegos + i)->jugadores[j].alturaGolpe = (juegos + i)->jugadores[j].estatura * 0.1;
                        (juegos + i)->jugadores[j].alturaMaximaDeLaPelota = alturaTempDiMaria + (juegos + i)->jugadores[j].alturaGolpe;
                    }
                    (juegos + i)->jugadores[j].distanciaRecorrida = ((duracionJuegoEnMinutos * 60) * (juegos + i)->jugadores[j].alturaMaximaDeLaPelota) / periodoDiMariaSegundos;
                    break;
                case 2:
                    //Acuna. Nos dicen que la pelota llega a x altura total
                    (juegos + i)->jugadores[j].alturaMaximaDeLaPelota = alturaTotalAcunaMetros[i];
                    (juegos + i)->jugadores[j].velocidadInicial = calculaVelDesdeAltura((juegos + i)->jugadores[j].alturaMaximaDeLaPelota);
                    const float tiempoAcuna = calculaTiempoDesdeVelocidad((juegos + i)->jugadores[j].velocidadInicial) * 2;
                    float alturaTempAcuna = calculaAlturaDesdeVelocidad((juegos + i)->jugadores[j].velocidadInicial);
                    if(alturaTempAcuna > 1.5)
                    {
                        (juegos + i)->jugadores[j].alturaGolpe = (juegos + i)->jugadores[j].estatura * 0.15;
                    }
                    else
                    {
                        (juegos + i)->jugadores[j].alturaGolpe = (juegos + i)->jugadores[j].estatura * 0.1;
                    }
                    (juegos + i)->jugadores[j].golpesPorMinuto = (duracionJuegoEnMinutos * 60) / tiempoAcuna;
                    (juegos + i)->jugadores[j].distanciaRecorrida = ((duracionJuegoEnMinutos * 60) * (juegos + i)->jugadores[j].alturaMaximaDeLaPelota) / tiempoAcuna;
                    break;
            }
        }
        calculaCantAlineamientos(juegos + i);
    }
  /* Aquí deben estar los llamados a las funciones creadas por ustedes */
}
