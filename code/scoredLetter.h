#ifndef SCORED_LETTER_H
#define SCORED_LETTER_H

#include <stdio.h>
#include <stdlib.h>

#define NULLLETTER newScoredLetter('\0', 0);

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

void print(ScoredLetter *scoredLetters);

int value(ScoredLetter *scoredLetters);

#endif // SCORED_LETTER_H
