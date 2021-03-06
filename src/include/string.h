#ifndef _STRING_H
#define _STRING_H

#if !defined(NULL)              /* Define NULL */
	#define NULL ((void*)0)
#endif

#include <stddef.h>

void *memcpy(void *dst, const void *src, size_t len); /* Copy Memory                            */
void memset(void *dst, int val, size_t len);          /* Set memory to a certian value          */
int memcmp(const void *s1, const void *s2, size_t n); /* Compare memory.                        */

size_t strcspn(const char *s1, const char *s2); /* Find length of s1 without charecters in s2.  */
size_t strspn(const char *s1, const char *s2);  /* Find length of parts of s1 included in s2.   */
char *strtok(char *str, const char *delim);     /* Cut a string at a certian deliminator.		*/
char *strchr(const char *s, int c);             /* Find first occurance of c in *s.			    */ 
char *strstr(const char *s1, const char *s2);   /* Find s2 string in s1.                        */
size_t strlen(const char *s);                   /* Find string length.                          */
int strcmp(const char *s1, const char *s2);     /* Compare two strings                          */
char *strcpy(char *dst, char *src);             /* Copy one string into another.                */
char *strcat(char *dst, char *src);             /* Add one string to the end of another string. */
int strncmp(const char *s1, const char *s2, size_t n); /* Compare n bytes in a string.	        */

#endif
