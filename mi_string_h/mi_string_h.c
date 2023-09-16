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
        if(*str == c) {
            return (char*)str;
        }
        str++;
    }

    return NULL;
}

char* strrchr(const char* str, int c) { //Searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument str.

}

int mi_strcmp(const char* str1, const char* str2) { //Compares the string pointed by str1 to the string pointed to by str2.
    while(*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    return *(const char)str1 - *(const char)str2;
}

char* mi_strcpy(char* dest, const char* src) { //Copies the string pointed to, by src to dest.
    while(*src) {

    }
}

size_t mi_strlen(const char* str) { //Computes the length of the string str up to but not including the terminating null character.
    size_t cant = 0;

    while(*str) {
        cant++;
        str++;
    }

    return cant;
}

char *strstr(const char *haystack, const char *needle) { //Finds the first occurrence of the entire string needle (not including the terminating null character) which appears in the string haystack.


}
