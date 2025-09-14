#include "utils.h"

char *trim(char *str) {
    char *end;
    while (isspace((unsigned char) *str)) str++;
    if (*str == NULL) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;
    *(end+1) = 0;
    return str;
}
