#include "scoredLetter.h"

struct ScoredLetter newScoredLetter(char letter, int score)
{
    struct ScoredLetter *newElement = malloc(sizeof(struct ScoredLetter));
    newElement->letter = letter;
    newElement->score = score;
    return *newElement;
}

char *print(ScoredLetter *scoredLetters, size_t nbScoredLetters)
{
    char *word = malloc(nbScoredLetters * sizeof(char));

    if (word)
    {
        for (size_t i = 0; i < nbScoredLetters; i++)
        {
            word[i] = scoredLetters[i].letter;
        }
    }

    return word;
}

int value(ScoredLetter *scoredLetters, size_t nbScoredLetters)
{
    int sum = 0;
    for (size_t i = 0; i < nbScoredLetters; i++)
    {
        sum += scoredLetters[i].score;
    }

    return sum;
}
