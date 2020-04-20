#include "sort.h"

/**
 * Swaps the ith and the jth element of the score's array
 *
 * array: An array of integer
 * i: An index of the array
 * j: An index of the array
 */
void swapScore(int *array, int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

/**
 * Swaps the ith and the jth element of the letter's array
 *
 * array: An array of integer
 * i: An index of the array
 * j: An index of the array
 */
void swapLetter(char *array, int i, int j)
{
    char temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void quicksort(int *scoreArray, char *letterArray,
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
    int pivot = scoreArray[upperBound];

    while (1)
    {
        // From lowerBound, finds the first element >= pivot
        while (scoreArray[++i] < pivot)
            ;

        // From upperBound, finds the first element <= pivot
        while (pivot < scoreArray[--j])
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
        swapScore(scoreArray, i, j);
        swapLetter(letterArray, i, j);

        // Moves all same left occurences of pivot to beginning of partition
        // Counts occurences with p
        if (scoreArray[i] == pivot)
        {
            p++;

            // Swap elements p and i
            swapScore(scoreArray, p, i);
            swapLetter(letterArray, p, i);
        }

        // Moves all same right occurences of pivot to end of partition
        // Counts occurences with q
        if (scoreArray[j] == pivot)
        {
            q--;

            // Swap elements q and j
            swapScore(scoreArray, q, j);
            swapLetter(letterArray, q, j);
        }
    }

    // Swap elements i and upperBound
    swapScore(scoreArray, i, upperBound);
    swapLetter(letterArray, i, upperBound);

    // Moves all same left occurences from beginning to adjacent to ith element
    j = i - 1;
    for (int k = lowerBound; k < p; k++, j--)
    {
        // Swap elements k and j
        swapScore(scoreArray, k, j);
        swapLetter(letterArray, k, j);
    }

    // Moves all same right occurences from end to adjacent to ith element
    i = i + 1;
    for (int k = upperBound; k > q; k--, i++)
    {
        // Swap elements k and i
        swapScore(scoreArray, k, i);
        swapLetter(letterArray, k, i);
    }

    // Recursive call for the left partition
    quicksort(scoreArray, letterArray, lowerBound, j);

    // Recursive call for the right partition
    quicksort(scoreArray, letterArray, i, upperBound);
}
