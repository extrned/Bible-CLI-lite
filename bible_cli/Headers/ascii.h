#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"

#define NUMBER_ARTS 3
#define COLS 15

int initAllArts();
void setASCII(char **artArr, int rows, int cols, const char *art[]);
void freeAllArts();
char **getRandomASCII();
int getSelectedArtRows();
