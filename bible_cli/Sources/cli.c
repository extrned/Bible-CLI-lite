#include "cli.h"

int LAUNCHED = 1;

const char *getButtonString(LanguagePack *lp, MenuButton button) {
  switch (button) {
  case BUTTON_START:
    return lp->mainButtonStart;
  case BUTTON_CONTINUE:
    return lp->mainButtonContinue;
  case BUTTON_SETTINGS:
    return lp->mainButtonSettings;
  case BUTTON_EXIT:
    return lp->mainButtonExit;
  default:
    return "Unknown";
  }
}

void handleButton(MenuButton selected) {
  switch (selected) {
  case BUTTON_START:
    // startReaderFromScratch();
    break;
  case BUTTON_CONTINUE:
    // continueReader();
    break;
  case BUTTON_SETTINGS:
    // startSettings();
    break;
  }
}

void enableRawMode(struct termios *old_t) {
  struct termios new_t;
  tcgetattr(STDIN_FILENO, old_t);
  new_t = *old_t;
  new_t.c_lflag &= ~(ICANON | ECHO);
  new_t.c_cc[VMIN] = 1;
  new_t.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &new_t);
}

void disableRawMode(struct termios *old_t) {
  tcsetattr(STDIN_FILENO, TCSANOW, old_t);
}

void cliInit(LanguagePack *lp) {
  if (lp == NULL)
    return;
  if (DEBUG_MODE)
    sleep(TIMERSEC);
  system("clear");
  cliLoop(lp);
}

KeyCode readChar() {
  if (!LAUNCHED)
    return KEY_EXIT;
  char c;
  if (read(STDIN_FILENO, &c, 1) == -1)
    return -1;

  if (c == '\x1b') {
    char seq[3];
    if (read(STDIN_FILENO, &seq, 2) != 2)
      return KEY_EXIT;
    if (seq[0] == '[') {
      switch (seq[1]) {
      case 'A':
        return KEY_UP;
      case 'B':
        return KEY_DOWN;
      case 'C':
        return KEY_RIGHT;
      case 'D':
        return KEY_LEFT;
      }
    }
    return KEY_EXIT;
  }
  if (c == '\r' || c == '\n')
    return KEY_ENTER;
  return c;
}

void cliPrintMenu(LanguagePack *lp, MenuButton selected) {
  if (!LAUNCHED)
    return;
  system("clear");
  printf("%s\n\n\n", lp->mainTitleSection);
  for (int i = 0; i < BUTTON_COUNTER; i++) {
    if (i == selected) {
      if (i == BUTTON_EXIT)
        printf("\033[7m%s\033[0m", getButtonString(lp, i));
      else
        printf("\033[7m%s\033[0m    ", getButtonString(lp, i));
    } else
      printf("%s    ", getButtonString(lp, i));
  }
  printf("\n");
  fflush(stdout);
}

void cliLoop(LanguagePack *lp) {
  if (lp == NULL)
    return;
  struct termios old_t;
  enableRawMode(&old_t);
  MenuButton selected = BUTTON_START; // by default
  cliPrintMenu(lp, selected);

  while (LAUNCHED) {
    MenuButton prevSelected = selected;
    KeyCode key = readChar();

    switch (key) {
    case KEY_LEFT:
      selected = (selected - 1 + BUTTON_COUNTER) % BUTTON_COUNTER;
      break;
    case KEY_RIGHT:
      selected = (selected + 1) % BUTTON_COUNTER;
      break;
    case KEY_ENTER:
      if (selected == BUTTON_EXIT)
        cliExit(&old_t);
      handleButton(selected);
      break;
    case KEY_EXIT:
      cliExit(&old_t);
      break;
    }

    if (selected != prevSelected)
      cliPrintMenu(lp, selected);
  }
}
void cliExit(struct termios *old_t) {
  LAUNCHED = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, old_t);
}
