#include "funciones.h"

/* aquí deben declarar sus funciones */

char obtenerValorPorTeclado(const char *opcionesValidas, const char* primerMensaje, const char* segundoMensaje)
{

    /* Aquí deben hacer todas las validaciones necesarias para que el reporte extendido se muestre a pedido del usuario */
    char teclaIngresada='n';

    return teclaIngresada;
}

float calculaVelDesdePeriodo(const float periodo)
{
    return GRAVEDAD * (periodo / 2);
}

void solucionTP(t_juego* juegos)
{
    //Datos brindados por el enunciado
    const float periodosMessiSegundos[CANT_JUEGOS] = {1.5, 3.0, 5.0};
    const float alturaTotalAcunaMetros[CANT_JUEGOS] = {3.0, 11.11, 14.14};
    const int frecuenciasDiMariaMinuto[CANT_JUEGOS] = {10, 15, 30};

    for(int i = 0; i < CANT_JUEGOS; i++)
    {//Iteramos por la cantidad de juegos
        for(int j = 0; j < CANT_JUGADORES; j++)
        {//Iteramos por la cantidad de jugadores
            switch(i){//Realizamos los calculos segun el jugador
                case 0://Messi
                    (&juegos[0] + i)->jugadores[j].velocidadInicial = calculaVelDesdePeriodo(periodosMessiSegundos[j]);
                    printf("%7.2f \n", (&juegos[0] + i)->jugadores[j].velocidadInicial);
                    break;
                case 1://DiMaria

                    break;
                case 2://Acuna
                    break;
            }
        }
    }
  /* Aquí deben estar los llamados a las funciones creadas por ustedes */
}
