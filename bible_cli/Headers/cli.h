#pragma once

#include "tool.h"
#include "utils.h"
#include <stdio.h>
#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#endif

void cliInit();
void cliLoop(int *isRunning);
void cliExit(int *isRunning, struct termios *old_t);
