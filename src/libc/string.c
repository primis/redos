#include <string.h>

void *memcpy(void *dst, const void *src, size_t len) {
    char *sp = (char*) src;
    char *dp = (char*) dst;
    for(; len != 0; len--) {
		*dp++ = *sp++;
	}
	return dst;
}

void memset(void *dst, int val, size_t len) {
    char *temp = (char*) dst;
    for ( ; len != 0; len--) {	
		*temp++ = val;
	}
}

int memcmp(const void *s1, const void *s2, size_t n) {
	const unsigned char *us1 = (const unsigned char *)s1;
	const unsigned char *us2 = (const unsigned char *)s2;
	while(n-- != 0) {
		if(*us1 != *us2) {
			return (*us1 < *us2) ? -1 : +1;
		}			
		us1++;
		us2++;
	}
	return 0;
}

char *strchr(const char *s, int c) {
	while (*s != (char)c) {
		if (!*s++) {
			return 0;
		}
	}
	return (char *)s;
}

size_t strspn(const char *s1, const char *s2) {
	size_t ret=0;
	while(*s1 && strchr(s2,*s1++)) {
		ret++;
	}
	return ret;
}

size_t strcspn(const char *s1, const char *s2) {
	size_t ret=0;
	while(*s1) {
		if(strchr(s2,*s1)) {		
			return ret;
		} else {
			 s1++,ret++;
		}	
	}	
	return ret;
}

char *strtok(char *str, const char *delim) {
	static char* p=0;
	if(str) {  	/* Does the string exist? */
		p=str;	/* If so, change p to current position. */
	} else if(!p) { 
		return 0; /* Otherwise, exit null. */
	}
	str = p   + strspn(p,delim);
	p   = str + strcspn(str,delim);
	if(p==str) {
		return p=0;
	}
	p = *p ? *p=0,p+1 : 0;
	return str;
}

char *strstr(const char *s1, const char *s2) {
	size_t s2len;
	if(*s2 == '\0') {
		return (char *) s1;
	}
	s2len = strlen(s2);
	for (; (s1 = strchr(s1, *s2)) != NULL; s1++) {
		if (strncmp(s1, s2, s2len) == 0) {
			return (char *) s1;
		}	
	}
	return NULL;
}

size_t strlen(const char *s) {
   size_t i;
   for(i=0; s[i] != '\0'; i++);
   return i;
}

int strcmp(const char *s1, const char *s2) {
    for(; *s1 == *s2; ++s1, ++s2) {
        if(*s1 == 0) {
            return 0;
		}
	}
    return *(unsigned char *)s1 < *(unsigned char *)s2 ? -1 : 1;
}

int strncmp(const char *s1, const char *s2, size_t n) {
	unsigned char uc1, uc2;
	if (n==0)
		return 0;
	while (n-- > 0 && *s1 == *s2) {
		if ( n==0 || *s1 == '\0') {
			return 0;
		}
		s1++;
		s2++;
	}
	uc1 = (*(unsigned char *) s1);
	uc2 = (*(unsigned char *) s2);
	return ((uc1 < uc2) ? -1 : (uc1 > uc2));
}

char *strcpy(char *dest, char *src) {
    do {
      *dest++ = *src++;
    } while (*src != 0);
	return dest;
}

char *strcat(char *dst, char *src) {
   size_t len;

   len = strlen(dst);
   strcpy(dst + len, src);
   return dst;
}
