#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>
#include <stdint.h>

size_t sm_strlen(const uint8_t *);
void sm_strrev(unsigned char *);
char *sm_strcpy(char *, const char *);
char *sm_strcat(char *, const char *);

#endif