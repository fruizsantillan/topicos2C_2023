#ifndef MI_STRING_H_H_INCLUDED
#define MI_STRING_H_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

char* mi_strcat(char* dest, const char* src);
//Appends the string pointed to, by src to the end of the string pointed to by dest.
char* mi_strchr(const char* str, int c);
//Searches for the first occurrence of the character c (an unsigned char) in the string pointed to, by the argument str
int mi_strcmp(const char* str1, const char* str2);
//Compares the string pointed to, by str1 to the string pointed to by str2.
char* mi_strcpy(char* dest, const char* src);
//Copies the string pointed to, by src to dest.
size_t mi_strlen(const char* str);
//Computes the length of the string str up to but not including the terminating null character.
char* mi_strrchr(const char* str, int c);
//Searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument str.
char *mi_strstr(const char *haystack, const char *needle);
//Finds the first occurrence of the entire string needle (not including the terminating null character) which appears in the string haystack.
#endif // MI_STRING_H_H_INCLUDED
