#include "lang_parser.h"
#define MAX_LINE_LENGTH 1024
#define MAX_LANG_LENGTH 50

int initLanguagePack(LanguagePack *lp, char *langName) {
  if (lp == NULL) {
    return makeError("LanguagePack pointer is NULL.");
  }
  if (strlen(langName) == 0) {
    return makeError("Language name is empty");
  }
  lp->langCode = strdup(langName);
  return 1;
}

int processLanguagePack(LanguagePack *lp, const char *lpPath) {
  if (!lp)
    return makeError("LanguagePack pointer is NULL.");
  if (!lpPath || !*lpPath)
    return makeError("LanguagePack path is empty");

  FILE *f = fopen(lpPath, "r");
  if (!f)
    return makeError("Failed to open a language pack");

  char line[MAX_LINE_LENGTH];
  char header[MAX_LANG_LENGTH];
  int langFound = 0;

  while (fgets(line, sizeof line, f)) {
    line[strcspn(line, "\n")] = '\0';
    if (line[0] == '\0' || line[0] == '*')
      continue;

    if (sscanf(line, " [ %49[^] \t] ] ", header) == 1) {
      if (langFound)
        break;
      char *trimmed = trim(header);
      if (strcmp(trimmed, lp->langCode) == 0) {
        langFound = 1;
        if (DEBUG_MODE)
          makeLog("LanguagePack: using section '%s'", trimmed);
      }
      continue;
    }

    if (langFound) {
      char key[128];
      char value[MAX_LINE_LENGTH];
      if (sscanf(line, " %127s %[^\n]", key, value) != 2)
        continue;

      char **dest = NULL;
      if (strcmp(key, "main-title-section") == 0)
        dest = &lp->mainTitleSection;
      else if (strcmp(key, "main-button-start") == 0)
        dest = &lp->mainButtonStart;
      else if (strcmp(key, "main-button-continue") == 0)
        dest = &lp->mainButtonContinue;
      else if (strcmp(key, "main-button-settings") == 0)
        dest = &lp->mainButtonSettings;
      else if (strcmp(key, "main-button-exit") == 0)
        dest = &lp->mainButtonExit;
      else if (strcmp(key, "reader-title-book") == 0)
        dest = &lp->readerTitleBook;
      else if (strcmp(key, "reader-title-chapter") == 0)
        dest = &lp->readerTitleChapter;
      else if (strcmp(key, "reader-title-verse") == 0)
        dest = &lp->readerTitleVerse;

      if (dest) {
        *dest = strdup(trim(value));
        if (!*dest) {
          fclose(f);
          return makeError("Failed to allocate memory for a field.");
        }
        if (DEBUG_MODE)
          makeLog("Parsed key: %s, value: %s", key, value);
      }
    }
  }

  fclose(f);

  if (!langFound) {
    makeWarning("'%s' not found in language pack", lp->langCode);
    return makeError("The language pack does not contain your language.");
  }

  return 1;
}

void freeLanguagePack(LanguagePack *lp) {
  if (lp->langCode != NULL) {
    free(lp->langCode);
    lp->langCode = NULL;
  }

  if (lp->mainTitleSection != NULL) {
    free(lp->mainTitleSection);
    lp->mainTitleSection = NULL;
  }

  if (lp->mainButtonStart != NULL) {
    free(lp->mainButtonStart);
    lp->mainButtonStart = NULL;
  }

  if (lp->mainButtonContinue != NULL) {
    free(lp->mainButtonContinue);
    lp->mainButtonContinue = NULL;
  }

  if (lp->mainButtonSettings != NULL) {
    free(lp->mainButtonSettings);
    lp->mainButtonSettings = NULL;
  }

  if (lp->mainButtonExit != NULL) {
    free(lp->mainButtonExit);
    lp->mainButtonExit = NULL;
  }

  if (lp->readerTitleBook != NULL) {
    free(lp->readerTitleBook);
    lp->readerTitleBook = NULL;
  }

  if (lp->readerTitleChapter != NULL) {
    free(lp->readerTitleChapter);
    lp->readerTitleChapter = NULL;
  }

  if (lp->readerTitleVerse != NULL) {
    free(lp->readerTitleVerse);
    lp->readerTitleVerse = NULL;
  }
}
