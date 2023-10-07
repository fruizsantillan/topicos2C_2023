#include "mi_string_h.h"

char* mi_strcat(char* dest, const char* src) { //Appends the string pointed to, by src to the end of the string pointed to by dest.
    char * fin_dest = dest + mi_strlen(dest);

    while(*src) {
        *fin_dest = *src;
        fin_dest++;
        src++;
    }

    *fin_dest = '\0';

    return dest;
}

char* mi_strchr(const char* str, int c) { //Searches for the first occurrence of the character c (an unsigned char) in the string pointed to, by the argument str
    while(*str) {
        if (*str == c)
            return (char *) str;

        str++;
    }

    return NULL;
}

char* mi_strrchr(const char* str, int c) { //Searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument str.
    const char* ultimaOcurrencia = NULL;

    while(*str) {
        if(*str == c)
            ultimaOcurrencia = str;
        str++;
    }

    if(ultimaOcurrencia)
        return (char*) ultimaOcurrencia;
    else
        return NULL;
}

int mi_strcmp(const char* str1, const char* str2) { //Compares the string pointed by str1 to the string pointed to by str2.
    while(*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    return str1 - str2;
}

char* mi_strcpy(char* dest, const char* src) { //Copies the string pointed by src to dest.
    char* original = dest;

    while(*src) {
        *dest = *src;
        dest++;
        src++;
    }

    return original;
}

size_t mi_strlen(const char* str) { //Computes the length of the string str up to but not including the terminating null character.
    size_t cant = 0;

    while(*str) {
        cant++;
        str++;
    }

    return cant;
}

char *mi_strstr(const char *haystack, const char *needle) { //Finds the first occurrence of the entire string needle (not including the terminating null character) which appears in the string haystack.
    while(*haystack) {
        const char* h = haystack;
        const char* n = needle;

        while(*n && *h == *n) {
            h++;
            n++;
        }

        if(*n == '\0')
            return (char*) haystack;

        haystack++;

    }
    return NULL;
}
