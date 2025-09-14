#include "logger.h"

void makeLog(const char *formattedStr, ...) {
    va_list args;
    printf("Logger: ");
    va_start(args, formattedStr);
    vprintf(formattedStr, args);
    printf("\n");
    va_end(args);
}

void makeWarning(const char *formattedStr, ...) {
    va_list args;
    printf("Warning: ");
    va_start(args, formattedStr);
    vprintf(formattedStr, args);
    printf("\n");
    va_end(args);
}

int makeError(const char *errorDesc) {
    if (strlen(errorDesc) == 0) makeWarning("No error provided.");
    else
        printf("Error: %s\n", errorDesc);
    return 0;
}

int makeErrorAndFreeString(const char *errorDesc, size_t pointersCount, ...) {
    if (strlen(errorDesc) == 0) makeWarning("No error provided.");
    else
        printf("Error: %s\n", errorDesc);
    va_list pointers;
    va_start(pointers, errorDesc);
    for (size_t i = 0; i < pointersCount; i++) {
        char *ptr = va_arg(pointers, char *);
        free(ptr);
    }
    return 0;
}
