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

    FILE *f = fopen(lpPath, "r");
    if (f == NULL) {
        return makeErrorAndFreeString("Failed to open a language pack", 1, line);
    }

    char *lang;
    
    int langFound = 0;
    while (fgets(line, MAX_LINE_LENGTH, f) != NULL && langFound != 1) {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0 || line[0] == '*') continue; // * for comments
        char *oBracket = strchr(line, '[');
        if (oBracket != NULL) {
            char *cBracket = strchr(oBracket + 1, ']');
            if (cBracket != NULL) {
                size_t len = cBracket - (oBracket + 1);
                if (len >= MAX_LANG_LENGTH) {
                    fclose(f);
                    return makeErrorAndFreeString("Language code is too long.", 1, line);
                }
                lang = (char *)malloc(len + 1);
                if (lang == NULL) {
                    fclose(f);
                    return makeErrorAndFreeString("Lang can't be allocated.", 1, line);
                }
                strncpy(lang, oBracket + 1, len);
                lang[len] = '\0';
                if (DEBUG_MODE)
                    makeLog("LanguagePack: Running through '%s'", lang);
                char *trimmed = trim(lang);
                if (trimmed == NULL) {
                    fclose(f);
                    return makeErrorAndFreeString("Trimmed text can't be allocated.", 2, line, lang);
                }
                if (strlen(trimmed) == 0) {
                    free(lang);
                    continue;
                }
                strcpy(lang, trimmed);
                if (strcmp(lang, lp->langCode) == 0) langFound = 1;
            }
        }
    }
    free(line);
    
    if (!langFound) {
        fclose(f);
        makeWarning("'%s' isn't supported.", lp->langCode);
        return makeError("The language pack does not contain your language. Critical error.");
    }
    fclose(f);
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
