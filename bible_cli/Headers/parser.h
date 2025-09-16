#pragma once

#define INITIAL_ARRAY_CAPACITY 10000
#define MAX_LINE_LENGTH 1024

#include "logger.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *book;
  int chapter;
  int verseNumber;
  char *verseText;
} BibleVerse;

typedef struct {
  BibleVerse *verses;
  size_t count;
  size_t capacity;
} Bible;

void initBible(Bible *bible);
void addVerse(Bible *bible, char *bookName, int chapter, int verseNumber,
              char *verseText);
int parseBibleFile(const char *fileName, Bible *bible);
const char *getVerseText(Bible *bible, const char *book, int chapter,
                         int verseNumber);
// @TODO: Implement the searchVerseTextByQuery() function as well as the search
// system (a SearchResult struct and so on) with binary searching for
// performance
void freeBible(Bible *bible);
