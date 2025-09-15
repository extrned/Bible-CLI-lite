#pragma once

#define TIMERSEC 10

#include <stdio.h>
#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#endif
#include "lang_parser.h"
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
  KEY_EXIT = 'q'
} KeyCode;

void cliInit(LanguagePack *lp);
const char *getButtonString(LanguagePack *lp, MenuButton button);
void handleButton(MenuButton selected);
void enableRawMode(struct termios *old_t);
void disableRawMode(struct termios *old_t);
KeyCode readChar();
void cliExit(struct termios *old_t);
void cliLoop(LanguagePack *lp);
