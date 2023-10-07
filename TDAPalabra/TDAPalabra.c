#include "TDAPalabra.h"

void crearSecuencia(SecuenciaPal* sec, char* cadena) {
    sec->cursor = cadena;
    sec->finSec = false;
}

bool leerPalabra(SecuenciaPal* sec, Palabra* pal) {
    while(*sec->cursor && !isalpha(*sec->cursor)) {
        sec->cursor++;
    }

    if(*sec->cursor == '\0') {
        sec->finSec = true;
        return false;
    }

    char* actPal = pal->vec;
    while(*sec->cursor && isalpha(*sec->cursor)) {
        *actPal = *sec->cursor;
        actPal++;
        sec->cursor++;
    }

    *actPal = '\0';

    return true;
}

void escribirPalabra(SecuenciaPal* sec, const Palabra* pal){
    char* actPal = (char *)pal->vec;
    while(*actPal) {
        *sec->cursor = *actPal;
        actPal++;
        sec->cursor++;
    }
}

void escribirCaracter(SecuenciaPal* sec, char c) {
    *sec->cursor = c;
    sec->cursor++;
}

void aTitulo(Palabra* pal) {
    char* actPal = pal->vec;
    *actPal = toupper(*actPal);
    actPal++;

    while(*actPal) {
        *actPal = tolower(*actPal);
        actPal++;
    }

}

void reposicionarCursor(SecuenciaPal* sec, long despl) {
    sec->cursor += despl;
}

void cerrarSecuencia(SecuenciaPal* sec) {
    *sec->cursor = '\0';
}

bool finSecuencia(const SecuenciaPal* sec) {
    return sec->finSec;
}
