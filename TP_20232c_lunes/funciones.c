#include "funciones.h"

/* aquí deben declarar sus funciones */

float calculaVelDesdePeriodo(const float periodo)
{
    return GRAVEDAD * (periodo / 2);
}

float calculaAlturaDesdeVelocidad(const float velocidad)
{
    return (velocidad * velocidad) / (2 * GRAVEDAD);
}

float calculaVelDesdeAltura(const float altura)
{
    return sqrt(2 * altura * GRAVEDAD);
}

char obtenerValorPorTeclado(const char *opcionesValidas, const char* primerMensaje, const char* segundoMensaje)
{

    /* Aquí deben hacer todas las validaciones necesarias para que el reporte extendido se muestre a pedido del usuario */
    char teclaIngresada='n';

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
                case 2://Acuna
                    (juegos + i)->jugadores[j].alturaMaximaDeLaPelota = alturaTotalAcunaMetros[i];
                    (juegos + i)->jugadores[j].velocidadInicial = calculaVelDesdeAltura((juegos + i)->jugadores[j].alturaMaximaDeLaPelota);
                    break;
            }
        }
    }
  /* Aquí deben estar los llamados a las funciones creadas por ustedes */
}
