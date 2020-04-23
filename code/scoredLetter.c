#include "scoredLetter.h"

struct ScoredLetter newScoredLetter(char letter, int score)
{
    struct ScoredLetter *newElement = malloc(sizeof(struct ScoredLetter));
    newElement->letter = letter;
    newElement->score = score;
    return *newElement;
}

void print(ScoredLetter *scoredLetters)
{
    for (size_t i = 0; scoredLetters[i].letter != '\0'; i++)
    {
        printf("%c", scoredLetters[i].letter);
    }
}

int value(ScoredLetter *scoredLetters)
{
    int sum = 0;
    for (size_t i = 0; scoredLetters[i].letter != '\0'; i++)
    {
        sum += scoredLetters[i].score;
    }

    return sum;
}
