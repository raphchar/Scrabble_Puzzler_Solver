/**
 * sort.c
 *
 * Implémentaion of a quicksort over an array of ScoredLetter
 *
 */

#include "sort.h"

/**
 * Swaps the ith and the jth element of the ScoredLetter's array
 *
 * array: An array of ScoredLetter
 * i: An index of the array
 * j: An index of the array
 */
void swap(ScoredString array, int i, int j)
{
    struct ScoredLetter tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

void quicksort(ScoredString scoredLetters, int lowerBound, int upperBound)
{
    if (upperBound <= lowerBound)
    {
        return;
    }

    int i = lowerBound - 1;
    int j = upperBound;
    int p = lowerBound - 1;
    int q = upperBound;

    // Sets pivot as the last element of the partition
    int pivot = scoredLetters[upperBound].score;

    while (1)
    {
        // From lowerBound, finds the first element <= pivot
        while (scoredLetters[++i].score > pivot)
            ;

        // From upperBound, finds the first element >= pivot
        while (pivot > scoredLetters[--j].score)
        {
            if (j == lowerBound)
            {
                break;
            }
        }

        // If i and j cross, done partitioning
        if (i >= j)
        {
            break;
        }

        // Swap elements i and j
        swap(scoredLetters, i, j);

        // Moves all same left occurences of pivot to beginning of partition
        // Counts occurences with p
        if (scoredLetters[i].score == pivot)
        {
            p++;

            // Swap elements p and i
            swap(scoredLetters, p, i);
        }

        // Moves all same right occurences of pivot to end of partition
        // Counts occurences with q
        if (scoredLetters[j].score == pivot)
        {
            q--;

            // Swap elements q and j
            swap(scoredLetters, q, j);
        }
    }

    // Swap elements i and upperBound
    swap(scoredLetters, i, upperBound);

    // Moves all same left occurences from beginning to adjacent to ith element
    j = i - 1;
    for (int k = lowerBound; k < p; k++, j--)
    {
        // Swap elements k and j
        swap(scoredLetters, k, j);
    }

    // Moves all same right occurences from end to adjacent to ith element
    i = i + 1;
    for (int k = upperBound - 1; k > q; k--, i++)
    {
        // Swap elements k and i
        swap(scoredLetters, k, i);
    }

    // Recursive call for the left partition
    quicksort(scoredLetters, lowerBound, j);

    // Recursive call for the right partition
    quicksort(scoredLetters, i, upperBound);
}
