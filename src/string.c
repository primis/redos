#include <string.h>

void *memcpy(void * dest, const void *src, size_t n) {
    char *sp = (char*) src;
    char *dp = (char*) dest;
    for(; n != 0; n--) {
        *dp++ = *sp++;
    }
    return dest;
}

void memset(void *s, int c, size_t n)
{
    char *temp = (char*) s;
    for (; n != 0; n--) {
        *temp++ = c;
    }
}

