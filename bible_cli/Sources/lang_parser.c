#include "lang_parser.h"

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
    char *line = (char *)malloc(1024 * sizeof(char));
    if (line == NULL) {
        return makeError("Failed to allocate memory for line.");
    }

    char *lang = (char *)malloc(50 * sizeof(char));
    if (lang == NULL) {
        makeErrorAndFreeString("Failed to allocate memory for lang.", 1, line);
    }
    lang[0] = '\0';
    FILE *f = fopen(lpPath, "r");
    if (f == NULL) {
        return makeErrorAndFreeString("Failed to open a language pack", 2, line, lang);
    }
    while (fgets(line, sizeof(line), f) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0 || line[0] == '*') continue;
        char *oBracket = strchr(line, '[');
        if (oBracket != NULL && strcmp(lang, lp->langCode) != 0) {
            char *cBracket = strchr(oBracket + 1, ']');
            if (cBracket != NULL) {
                if (DEBUG_MODE)
                    makeLog("LanguagePack: Running through %s", line);
                int len = cBracket - (oBracket + 1);
                strncpy(lang, oBracket + 1, len);
                lang[len] = '\0';
                if (DEBUG_MODE)
                    makeLog("Now lang is %s", lang);
            }
        }
    }
    free(line);
    
    if (strcmp(lang, lp->langCode) != 0) {
        makeWarning("'%s' isn't supported.", lp->langCode);
        return makeErrorAndFreeString("The language pack does not contain your language. Critical error.", 1, lang);
    }
    free(lang);
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
