#ifndef SCORED_LETTER_H
#define SCORED_LETTER_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Special ScoredLetter that will act as an end guard in ScoredString.
 *
 * Usage similar to '\0' in regular string.
 */
#define NULLLETTER newScoredLetter('\0', 0);

typedef struct ScoredLetter ScoredLetter;
typedef ScoredLetter *ScoredString;
typedef ScoredLetter **Solution;
typedef ScoredLetter ***ListOfSolution;

struct ScoredLetter
{
    char letter;
    int score;
};

/**
 * Creates a new ScoredLetter
 */
ScoredLetter newScoredLetter(char letter, int score);

/**
 * Finds the index of the letter in the array
 */
int indexOf(ScoredString array, ScoredLetter letter);

/**
 * Removes the ith element of the array
 */
ScoredString removeElementAt(ScoredString array, int index);

/**
 * Removes all the given letters from the array
 */
ScoredString removeElements(ScoredString array, ScoredString letters);

/**
 * Computes the score associated to the given ScoredString
 */
int scoreOfString(ScoredString scoredLetters);

/**
 * Computes the score associated to one of the solutions
 */
int scoreOfSolutions(ListOfSolution solutions);

/**
 * Prints the solutions in the structured output format
 */
void displaySolutions(ListOfSolution solutions);

/**
 * Returns a deep copy of the given ListOfSolution
 */
ListOfSolution copySolutions(ListOfSolution solutions);

#endif // SCORED_LETTER_H
