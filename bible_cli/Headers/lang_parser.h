#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *langCode;
    char *mainTitleSection;
    char *mainButtonStart;
    char *mainButtonContinue;
    char *mainButtonSettings;
    char *mainButtonExit;
    char *readerTitleBook;
    char *readerTitleChapter;
    char *readerTitleVerse;
} LanguagePack;

int initLanguagePack(LanguagePack *lp, char *langName);
int processLanguagePack(LanguagePack *lp, const char *lpPath);
void freeLanguagePack(LanguagePack *lp);
