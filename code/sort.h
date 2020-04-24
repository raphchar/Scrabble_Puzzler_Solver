/**
 * sort.h
 *
 * Header of the implémentaion of a quicksort over an array of ScoredLetter
 *
 */

#ifndef SORT_H
#define SORT_H

#include "scoredLetter.h"

/**
 * Sorts the array of ScoredLetter
 *
 * scoredLetters: An array of ScoredLetter
 * lowerBound: The left most index of the considered partition
 * upperBound: The right most index of the considered partition
 */
void quicksort(ScoredString scoredLetters, int lowerBound, int upperBound);

#endif // SORT_H
