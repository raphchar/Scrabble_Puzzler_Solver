#ifndef SCORED_LETTER_H
#define SCORED_LETTER_H

#include <stdlib.h>

typedef struct ScoredLetter ScoredLetter;

struct ScoredLetter
{
    char letter;
    int score;
};

/**
 * Creates a new ScoredLetter
 */
struct ScoredLetter newScoredLetter(char letter, int score);

char *print(ScoredLetter *scoredLetters, size_t nbScoredLetters);

int value(ScoredLetter *scoredLetters, size_t nbScoredLetters);

#endif // SCORED_LETTER_H