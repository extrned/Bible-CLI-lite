#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef __linux__
    #include <unistd.h>
#endif

typedef struct {
    char language[50];
    char translation[50];
} ConfigParams;

char *trim(char *str);
int initConfig(ConfigParams *vals, const char *configPath);
