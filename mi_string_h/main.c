#include "mi_string_h.h"

int main()
{
    char text1[] = "independiente";
    char text2[] = "depen";
    printf("%s", mi_strstr(text1, text2));
    return 0;
}
