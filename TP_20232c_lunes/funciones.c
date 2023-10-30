#include "funciones.h"

/* aqu� deben declarar sus funciones */
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

float calcularDistanciaRecorrida(float duracionJuegoEnMinutos, float velocidadInicial, float alturaMaximaDeLaPelota, float periodo)
{
    return ((duracionJuegoEnMinutos * 60) * alturaMaximaDeLaPelota) / periodo;
}

double calcularAltura(double velocidad, double tiempo, float alturaGolpe)
{
    return (velocidad * tiempo - 0.5 * GRAVEDAD * pow(tiempo, 2)) + alturaGolpe;
}

void calculaCantAlineamientos(t_juego* juegos)
{
    t_coordenada coordenadas[CANT_JUGADORES];
    int duracionAlineamiento = 0;
    t_instante instanteAlineamiento;
    int cantAlineamientos = 0;

    for (int i = 0; i < CANT_JUGADORES; i++)
        coordenadas[i].x = juegos->jugadores[i].posicion;

    float pendienteAB = 0.0; // Inicializa la pendiente
    float pendienteBC = 0.0;

    for (int j = 0; j < CANT_MILISEG; j++)
    {
        for (int k = 0; k < CANT_JUGADORES; k++)
        {
            const float tiempoGolpe = juegos->jugadores[k].velocidadInicial / GRAVEDAD * 2;
            // Actualiza la altura de la pelota
            coordenadas[k].y = calcularAltura(juegos->jugadores[k].velocidadInicial, milisegASeg(j), juegos->jugadores[k].alturaGolpe);
        }

        if (duracionAlineamiento == 0)
        {
            pendienteAB = calculaPendiente(&coordenadas[0], &coordenadas[1]);
            pendienteBC = calculaPendiente(&coordenadas[1], &coordenadas[2]);
        }

        if (fabs(pendienteAB - pendienteBC) < DELTA)
        {
            if (duracionAlineamiento == 0)
            {
                instanteAlineamiento.milisegundo = j;
                instanteAlineamiento.segundo = milisegASeg(j);
                instanteAlineamiento.minuto = milisegAMin(j);

                juegos->alineamientos[cantAlineamientos].instanteInicial = instanteAlineamiento;
                juegos->alineamientos[cantAlineamientos].pendiente = (pendienteAB + pendienteBC) / 2;
                juegos->alineamientos[cantAlineamientos].pos1 = coordenadas[0];
                juegos->alineamientos[cantAlineamientos].pos2 = coordenadas[1];
                juegos->alineamientos[cantAlineamientos].pos3 = coordenadas[2];

                cantAlineamientos++;
                duracionAlineamiento = 1; // Inicializa la duración del alineamiento actual
            }
            else
            {
                duracionAlineamiento++; // Incrementa la duración del alineamiento actual
            }
        }
        else
        {
            duracionAlineamiento = 0; // Reinicia la duración si no hay alineamiento
        }
    }
    juegos->cantidadAlineamientos = cantAlineamientos;
}

char obtenerValorPorTeclado(const char *opcionesValidas, const char* primerMensaje, const char* segundoMensaje)
{
    /* Aqu� deben hacer todas las validaciones necesarias para que el reporte extendido se muestre a pedido del usuario */
    char teclaIngresada;

    printf(primerMensaje);
    scanf("%c", &teclaIngresada);
    fflush(stdin);
    while(teclaIngresada != opcionesValidas[0] && teclaIngresada != opcionesValidas[1])
    {
        printf(segundoMensaje);
        scanf("%c", &teclaIngresada);
        fflush(stdin);
    }

    return teclaIngresada;
}

void calcularDatosJugador(t_jugador *jugador, int juegoIndex, int jugadorIndex)
{
    //Datos brindados por el enunciado.
    const float periodosMessiSegundos[CANT_JUEGOS] = {1.5, 3.0, 5.0};
    const float alturaTotalAcunaMetros[CANT_JUEGOS] = {3.0, 11.11, 14.14};
    const int frecuenciasDiMariaMinuto[CANT_JUEGOS] = {10, 15, 30};

    switch (jugadorIndex)
    {
        case 0: // Messi
            jugador->velocidadInicial = calculaVelDesdePeriodo(periodosMessiSegundos[juegoIndex]);
            float alturaTempMessi = calculaAlturaDesdeVelocidad(jugador->velocidadInicial);
            jugador->alturaGolpe = (alturaTempMessi > 1.5) ? jugador->estatura * 0.15 : jugador->estatura * 0.1;
            jugador->alturaMaximaDeLaPelota = alturaTempMessi + jugador->alturaGolpe;
            jugador->golpesPorMinuto = 60 / periodosMessiSegundos[juegoIndex];
            jugador->distanciaRecorrida = (jugador->golpesPorMinuto * 3) * ((jugador->alturaMaximaDeLaPelota - jugador->alturaGolpe) * 2);
            break;
        case 1: // DiMaria
            jugador->golpesPorMinuto = frecuenciasDiMariaMinuto[juegoIndex];
            jugador->velocidadInicial = calculaVelDesdePeriodo(60.0 / jugador->golpesPorMinuto);
            float alturaTempDiMaria = calculaAlturaDesdeVelocidad(jugador->velocidadInicial);
            jugador->alturaGolpe = (alturaTempDiMaria > 1.5) ? jugador->estatura * 0.15 : jugador->estatura * 0.1;
            jugador->alturaMaximaDeLaPelota = alturaTempDiMaria + jugador->alturaGolpe;
            jugador->distanciaRecorrida = (jugador->golpesPorMinuto * 3) * ((jugador->alturaMaximaDeLaPelota - jugador->alturaGolpe) * 2);
            break;
        case 2: // Acuna
            jugador->alturaMaximaDeLaPelota = alturaTotalAcunaMetros[juegoIndex];
            jugador->velocidadInicial = calculaVelDesdeAltura(jugador->alturaMaximaDeLaPelota  - jugador->estatura * 0.15);
            jugador->alturaGolpe = (jugador->alturaMaximaDeLaPelota > 1.5) ? jugador->estatura * 0.15 : jugador->estatura * 0.1;
            jugador->golpesPorMinuto = (60) / (calculaTiempoDesdeVelocidad(jugador->velocidadInicial) * 2);
            jugador->distanciaRecorrida = (jugador->golpesPorMinuto * 3) * ((jugador->alturaMaximaDeLaPelota - jugador->alturaGolpe) * 2);
            break;
    }
}

void solucionTP(t_juego* juegos)
{
    for (int i = 0; i < CANT_JUEGOS; i++)
    {
        for (int j = 0; j < CANT_JUGADORES; j++)
        {
            calcularDatosJugador(&(juegos + i)->jugadores[j], i, j);
        }
        calculaCantAlineamientos(juegos + i);
    }
  /* Aqu� deben estar los llamados a las funciones creadas por ustedes */
}
