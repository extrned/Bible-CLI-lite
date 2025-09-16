// ASCII ART MGR

#include "ascii.h"

static char ***arts = NULL;

static int rowsPerArt[NUMBER_ARTS] = {
    7, 9, 13}; // number of elements of an array with the art

static const char *artCross[] = {"     .-.", "   __| |", "  [__   __]",
                                 "     | |", "     | |", "     | |",
                                 "     '-'"};

static const char *artCross2[] = {"      |V|",     "   .::| |::.",
                                  "  ::__| |__::", " >____   ____<",
                                  "  ::  | |  ::", "   '::| |::'",
                                  "      | |",     "      | |",
                                  "      |A|"};

static const char *artBible[] = {
    "         ,   ,", "        /////|", "       ///// |", "      /////  |",
    "     |~~~| | |", "     |===| |/|", "     | B |/| |", "     | I | | |",
    "     | B | | |", "     | L |  /",  "     | E | /",   "     |===|/",
    "     '---'"};

static int selArtIndex = -1;

int initAllArts() {
  arts = (char ***)malloc(NUMBER_ARTS * sizeof(char **));
  if (arts == NULL)
    return makeError("Failed to allocate memory for ASCII arts.");
  for (int i = 0; i < NUMBER_ARTS; i++) {
    arts[i] = (char **)malloc(rowsPerArt[i] * sizeof(char *));
    if (arts[i] == NULL)
      return makeError("Failed to allocate memory for an ASCII art.");

    for (int j = 0; j < rowsPerArt[i]; j++) {
      arts[i][j] = (char *)malloc(COLS * sizeof(char));
      if (arts[i][j] == NULL)
        return makeError("Failed to allocate memory for an ASCII piece.");
      memset(arts[i][j], ' ', COLS - 1);
      arts[i][j][COLS - 1] = '\0';
    }
  }

  setASCII(arts[0], rowsPerArt[0], COLS, artCross);
  setASCII(arts[1], rowsPerArt[1], COLS, artCross2);
  setASCII(arts[2], rowsPerArt[2], COLS, artBible);
  return 1;
}

void setASCII(char **artArr, int rows, int cols, const char *art[]) {
  for (int i = 0; i < rows; i++) {
    strncpy(artArr[i], art[i], cols - 1);
    artArr[i][cols - 1] = '\0';
  }
}

void freeAllArts() {
  if (arts == NULL)
    return;
  for (int i = 0; i < NUMBER_ARTS; i++) {
    for (int j = 0; j < rowsPerArt[i]; j++) {
      free(arts[i][j]);
    }
    free(arts[i]);
  }
  free(arts);
  arts = NULL;
}

char **getRandomASCII() {
  if (arts == NULL || NUMBER_ARTS <= 0)
    return NULL;
  selArtIndex = rand() % NUMBER_ARTS;
  return arts[selArtIndex];
}

int getSelectedArtRows() {
  if (selArtIndex >= 0 && selArtIndex < NUMBER_ARTS)
    return rowsPerArt[selArtIndex];
  return 0;
}
