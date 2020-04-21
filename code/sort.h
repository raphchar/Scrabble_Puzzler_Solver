#ifndef SORT_H
#define SORT_H

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

/**
 * Sorts the array of letter given an array of score
 *
 * Applies the QuickSort algorithm to the scoreArray and reflects the change
 * to the letterArray
 *
 * scoreArray: An array of integer representing the letters' scores
 * letterArray: An array of letter
 * lowerBound: The left most index of the considered partition
 * upperBound: The right most index of the considered partition
 */
void quicksort(struct ScoredLetter *scoredletters,
               int lowerBound, int upperBound);

#endif // SORT_H
