#ifndef _STRING_H
#define _STRING_H

#ifndef NULL
    #define NULL ((void*)0)
#endif

#include <stddef.h>

void *memcpy(void*, const void*, size_t);
void memset(void*, int, size_t);
void memcmp(const void*, const void*, size_t);

#endif
