#include "sort.h"

/**
 * Swaps the ith and the jth element of the ScoredLetter's array
 *
 * array: An array of ScoredLetter
 * i: An index of the array
 * j: An index of the array
 */
void swap(struct ScoredLetter *array, int i, int j)
{
    struct ScoredLetter temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void quicksort(struct ScoredLetter *scoredletters,
               int lowerBound, int upperBound)
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
    int pivot = scoredletters[upperBound].score;

    while (1)
    {
        // From lowerBound, finds the first element >= pivot
        while (scoredletters[++i].score > pivot)
            ;

        // From upperBound, finds the first element <= pivot
        while (pivot > scoredletters[--j].score)
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
        swap(scoredletters, i, j);

        // Moves all same left occurences of pivot to beginning of partition
        // Counts occurences with p
        if (scoredletters[i].score == pivot)
        {
            p++;

            // Swap elements p and i
            swap(scoredletters, p, i);
        }

        // Moves all same right occurences of pivot to end of partition
        // Counts occurences with q
        if (scoredletters[j].score == pivot)
        {
            q--;

            // Swap elements q and j
            swap(scoredletters, q, j);
        }
    }

    // Swap elements i and upperBound
    swap(scoredletters, i, upperBound);

    // Moves all same left occurences from beginning to adjacent to ith element
    j = i - 1;
    for (int k = lowerBound; k < p; k++, j--)
    {
        // Swap elements k and j
        swap(scoredletters, k, j);
    }

    // Moves all same right occurences from end to adjacent to ith element
    i = i + 1;
    for (int k = upperBound; k > q; k--, i++)
    {
        // Swap elements k and i
        swap(scoredletters, k, i);
    }

    // Recursive call for the left partition
    quicksort(scoredletters, lowerBound, j);

    // Recursive call for the right partition
    quicksort(scoredletters, i, upperBound);
}
