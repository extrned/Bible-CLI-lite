// THE BIBLE PARSER
// MADE ONLY FOR OPENBIBLE VERSIONS

#include "parser.h"

void initBible(Bible *bible) {
  bible->capacity = INITIAL_ARRAY_CAPACITY;
  bible->verses = malloc(bible->capacity * sizeof(BibleVerse));
  bible->count = 0;
}

void addVerse(Bible *bible, const char *bookName, int chapter, int verseNumber,
              const char *verseText) {
  if (bible->count >= bible->capacity) {
    bible->capacity *= 2;
    bible->verses =
        realloc(bible->verses, bible->capacity * sizeof(BibleVerse));
  }
  BibleVerse *verse = &bible->verses[bible->count];
  verse->book = strdup(bookName);
  verse->chapter = chapter;
  verse->verseNumber = verseNumber;
  verse->verseText = strdup(verseText);

  bible->count++;
}

int parseBibleFile(const char *fileName, Bible *bible) {
  FILE *f = fopen(fileName, "r");
  if (f == NULL)
    return makeError("Cannot open your Bible plain text.");
  char line[MAX_LINE_LENGTH];
  while (fgets(line, MAX_LINE_LENGTH, f) != NULL) {
    line[strcspn(line, "\n")] = '\0';
    char book[50];
    int chapter, verseNumber;
    char *verseText = NULL;

    char *spacePtr = strchr(line, ' ');
    if (spacePtr == NULL)
      continue;
    *spacePtr = '\0';
    strcpy(book, line);

    char *colonPtr = strchr(spacePtr + 1, ':');
    if (colonPtr == NULL)
      continue;
    *colonPtr = '\0';
    chapter = atoi(spacePtr + 1);
    verseNumber = atoi(colonPtr + 1);

    verseText = colonPtr + 1;
    while (*verseText == ' ')
      verseText++;

    addVerse(bible, book, chapter, verseNumber, verseText);
  }
  fclose(f);
  return 1;
}

void freeBible(Bible *bible) {
  for (size_t i = 0; i < bible->count; i++) {
    free(bible->verses[i].book);
    free(bible->verses[i].verseText);
  }
  free(bible->verses);
}
