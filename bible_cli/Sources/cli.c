#include "cli.h"

int LAUNCHED = 1;
struct termios oldT;

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
void handleSigint(int sig) {
  disableRawMode(&oldT);
  clearScreen();
  _exit(1);
}

void setupSignalHandler() { signal(SIGINT, handleSigint); }

void startReaderFromScratch(Bible *bible) {
  if (bible == NULL)
    return;
  clearScreen();

  int index = 0;
  const int last = bible->count - 1;
  printf("→ to move next, b to go to the Menu\n\n");
  while (1) {
    BibleVerse v = bible->verses[index];
    struct winsize ws;
    setWindow(&ws);

    for (int i = 0; i < ws.ws_col; i++)
      putchar('-');
    putchar('\n');
    char finalVerse[512];
    snprintf(finalVerse, 512, "[%s %d:%d] %s", v.book, v.chapter, v.verseNumber,
             v.verseText);

    if (strlen(finalVerse) >= (ws.ws_col - 1))
      printf("%s\n", finalVerse);
    else
      printf("%s |\n", finalVerse);
    fflush(stdout);

    KeyCode key = readChar();
    if (key == KEY_EXIT)
      break;
    else if (key == KEY_RIGHT && index < last)
      index++;
    else if (key == KEY_LEFT && index > 0)
      index--;
    // @TODO: Add an implementation of a 'b' key
  }
  cliExit(&oldT);
}

void handleButton(MenuButton selected, Bible *bible) {
  switch (selected) {
  case BUTTON_START:
    startReaderFromScratch(bible);
    break;
  case BUTTON_CONTINUE:
    // continueReader();
    break;
  case BUTTON_SETTINGS:
    // startSettings();
    break;
  }
}

void enableRawMode(struct termios *oldT) {
  struct termios newT;
  tcgetattr(STDIN_FILENO, oldT);
  newT = *oldT;
  newT.c_lflag &= ~(ICANON | ECHO);
  newT.c_cc[VMIN] = 1;
  newT.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &newT);
}

void disableRawMode(struct termios *oldT) {
  tcsetattr(STDIN_FILENO, TCSANOW, oldT);
}

void cliInit(LanguagePack *lp, const char *biblePath) {
  if (lp == NULL)
    return;
  srand(time(NULL));
  if (DEBUG_MODE) {
    makeLog("CLI is initialized");
  }

  Bible bible;
  initBible(&bible);
  if (parseBibleFile(biblePath, &bible) == 0)
    return;

  if (DEBUG_MODE) {
    makeLog("Bible was initialized and parsed from file %s.", biblePath);
    sleep(TIMERSEC);
  }
  cliLoop(lp, &bible);

  freeBible(&bible);
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

void printSpaces(int count) {
  for (int i = 0; i < count; i++)
    putchar(' ');
}

void cliPrintMenu(LanguagePack *lp, MenuButton selected) {
  if (!LAUNCHED)
    return;
  clearScreen();
  if (initAllArts()) {
    char **asciiArt = getRandomASCII();
    if (asciiArt) {
      int rows = getSelectedArtRows();
      for (int i = 0; i < rows; i++) {
        printf("| %s\t|\n", asciiArt[i]);
        if (i == rows - 1) {
          for (int j = 0; j < COLS; j++)
            putchar('-');
          putchar('\n');
        }
      }
    }
  }
  printf("%s\n\n", lp->mainTitleSection);
  struct winsize ws;
  setWindow(&ws);
  int totalLengthBtn = 0;
  for (int i = 0; i < BUTTON_COUNTER; i++) {
    const char *buttonName = getButtonString(lp, i);
    if (strcmp(buttonName, "Unknown") != 0)
      totalLengthBtn += strlen(buttonName);
  }
  int spacesCnt = (ws.ws_col - totalLengthBtn) / (BUTTON_COUNTER + 1);
  if (spacesCnt < 1)
    spacesCnt = 1;
  for (int i = 0; i < BUTTON_COUNTER; i++) {
    const char *buttonName = getButtonString(lp, i);
    if (strcmp(buttonName, "Unknown") == 0)
      continue;
    if (i == selected) {
      printf("\033[7m %s \033[0m", buttonName);
      printSpaces(spacesCnt);
    } else {
      printf("%s", buttonName);
      printSpaces(spacesCnt);
    }
  }
  putchar('\n');
  fflush(stdout);

  freeAllArts();
}

void cliLoop(LanguagePack *lp, Bible *bible) {
  if (lp == NULL)
    return;
  enableRawMode(&oldT);
  setupSignalHandler();
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
        cliExit(&oldT);
      else
        handleButton(selected, bible);
      break;
    case KEY_EXIT:
      cliExit(&oldT);
      break;
    default:
      break;
    }

    if (selected != prevSelected)
      cliPrintMenu(lp, selected);
  }
}
void cliExit(struct termios *oldT) {
  LAUNCHED = 0;
  disableRawMode(oldT);
}
