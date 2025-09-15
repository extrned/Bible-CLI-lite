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
  if (lp == NULL) {
    return makeError("LanguagePack pointer is NULL.");
  }
  if (strlen(lpPath) == 0) {
    return makeError("LanguagePack path is empty");
  }
  char *line = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
  if (line == NULL) {
    return makeError("Failed to allocate memory for line.");
  }
  char *lang = (char *)malloc(MAX_LANG_LENGTH * sizeof(char));
  if (lang == NULL) {
    return makeError("Failed to allocate memory for lang.");
  }

  FILE *f = fopen(lpPath, "r");
  if (f == NULL) {
    return makeErrorAndFreeString("Failed to open a language pack", 1, line);
  }

  int langFound = 0;
  while (fgets(line, MAX_LINE_LENGTH, f) != NULL) {
    line[strcspn(line, "\n")] = '\0';
    if (strlen(line) == 0 || line[0] == '*')
      continue; // * for comments
    char *oBracket = strchr(line, '[');
    if (oBracket != NULL) {
      if (langFound)
        break;
      char *cBracket = strchr(oBracket + 1, ']');
      if (cBracket != NULL) {
        int len = cBracket - (oBracket + 1);
        if (len >= MAX_LANG_LENGTH) {
          fclose(f);
          return makeErrorAndFreeString("Language code is too long.", 1, line);
        }
        strncpy(lang, oBracket + 1, len);
        lang[len] = '\0';

        char *trimmed = trim(lang);
        size_t trimmedLen = strlen(trimmed);
        if (trimmedLen >= MAX_LANG_LENGTH) {
          fclose(f);
          return makeErrorAndFreeString("Trimmed Language code is too long.", 1,
                                        line);
        }
        strcpy(lang, trimmed);
        if (DEBUG_MODE)
          makeLog("LanguagePack: Running through '%s'", lang);
        langFound = (strcmp(lang, lp->langCode) == 0);
        continue;
      }
    }

    if (langFound) {
      char *key = trim(line);
      char *space = strchr(key, ' ');
      if (space == NULL)
        continue;
      *space = '\0';
      char *value = trim(space + 1);
      if (strlen(value) == 0)
        continue;

      if (strcmp(key, "main-title-section") == 0) {
        lp->mainTitleSection = strdup(value);
        if (lp->mainTitleSection == NULL) {
          fclose(f);
          return makeErrorAndFreeString(
              "Failed to allocate memory for mainTitleSection.", 2, line, lang);
        }
      } else if (strcmp(key, "main-button-start") == 0) {
        lp->mainButtonStart = strdup(value);
        if (lp->mainButtonStart == NULL) {
          fclose(f);
          return makeErrorAndFreeString(
              "Failed to allocate memory for mainButtonStart.", 2, line, lang);
        }
      } else if (strcmp(key, "main-button-continue") == 0) {
        lp->mainButtonContinue = strdup(value);
        if (lp->mainButtonContinue == NULL) {
          fclose(f);
          return makeErrorAndFreeString(
              "Failed to allocate memory for mainButtonContinue.", 2, line,
              lang);
        }
      } else if (strcmp(key, "main-button-settings") == 0) {
        lp->mainButtonSettings = strdup(value);
        if (lp->mainButtonSettings == NULL) {
          fclose(f);
          return makeErrorAndFreeString(
              "Failed to allocate memory for mainButtonSettings.", 2, line,
              lang);
        }
      } else if (strcmp(key, "main-button-exit") == 0) {
        lp->mainButtonExit = strdup(value);
        if (lp->mainButtonExit == NULL) {
          fclose(f);
          return makeErrorAndFreeString(
              "Failed to allocate memory for mainButtonExit.", 2, line, lang);
        }
      } else if (strcmp(key, "reader-title-book") == 0) {
        lp->readerTitleBook = strdup(value);
        if (lp->readerTitleBook == NULL) {
          fclose(f);
          return makeErrorAndFreeString(
              "Failed to allocate memory for readerTitleBook.", 2, line, lang);
        }
      } else if (strcmp(key, "reader-title-chapter") == 0) {
        lp->readerTitleChapter = strdup(value);
        if (lp->readerTitleChapter == NULL) {
          fclose(f);
          return makeErrorAndFreeString(
              "Failed to allocate memory for readerTitleChapter.", 2, line,
              lang);
        }
      } else if (strcmp(key, "reader-title-verse") == 0) {
        lp->readerTitleVerse = strdup(value);
        if (lp->readerTitleVerse == NULL) {
          fclose(f);
          return makeErrorAndFreeString(
              "Failed to allocate memory for readerTitleVerse.", 2, line, lang);
        }
      }
      if (DEBUG_MODE) {
        makeLog("Parsed key: %s, value: %s", key, value);
      }
    }
  }
  free(line);
  free(lang);

  fclose(f);

  if (!langFound) {
    makeWarning("'%s' isn't supported", lp->langCode);
    return makeError(
        "The language pack does not contain your language. Critical error.");
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
