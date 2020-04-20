#ifndef SORT_H
#define SORT_H

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
void quicksort(int *scoreArray, char *letterArray,
               int lowerBound, int upperBound);

#endif // SORT_H