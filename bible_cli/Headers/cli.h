#pragma once

#define TIMERSEC 3
#define clearScreen() system("clear")
#define setWindow(ws) ioctl(STDIN_FILENO, TIOCGWINSZ, ws)

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <sys/ioctl.h>
#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#endif
#include "ascii.h"
#include "config_manager.h"
#include "lang_parser.h"
#include "parser.h"
#include "time.h"
#include "tool.h"
#include "utils.h"

typedef struct LanguagePack LanguagePack;

typedef enum {
  BUTTON_START,
  BUTTON_CONTINUE,
  BUTTON_SETTINGS,
  BUTTON_EXIT,
  BUTTON_COUNTER
} MenuButton;

typedef enum {
  KEY_UP = 1000,
  KEY_DOWN = 1001,
  KEY_LEFT = 1002,
  KEY_RIGHT = 1003,
  KEY_ENTER = '\r',
  KEY_EXIT = 'q',
  KEY_BACK = 'b'
} KeyCode;

void cliInit(LanguagePack *lp, const char *biblePath);
const char *getButtonString(LanguagePack *lp, MenuButton button);
void handleSigint(int sig);
void setupSignalHandler();
void handleButton(MenuButton selected, Bible *bible);
void enableRawMode(struct termios *oldT);
void disableRawMode(struct termios *oldT);
KeyCode readChar();
void cliExit(struct termios *oldT);
void cliLoop(LanguagePack *lp, Bible *bible);
