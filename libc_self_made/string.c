#include "string.h"

size_t sm_strlen(const uint8_t *str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}

void sm_strrev(unsigned char *str) {
    int head = 0;
    int tail = sm_strlen(str) - 1;
    for (; head < tail; head++, tail--) {
        char tmp = str[head];
        str[head] = str[tail];
        str[tail] = tmp;
    }
}

char *sm_strcpy(char *dst, const char *src) {
    size_t i = 0;
    while (src[i]) {
        dst[i] = src[i];
        i++;
    }
    return dst;
}

char *sm_strcat(char *dst, const char *src) {
    size_t dst_len = sm_strlen(dst);
    size_t i = 0;
    while (src[i]) {
        dst[dst_len + i] = src[i];
        i++;
    }
    return dst;
}