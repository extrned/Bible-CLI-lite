#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void makeLog(const char *formattedStr, ...);
void makeWarning(const char *formattedStr, ...);
int makeError(const char *errorDesc);
int makeErrorAndFreeString(const char *errorDesc, size_t pointerCount, ...);
