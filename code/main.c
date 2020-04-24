/**
 * main.c
 *
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scoredLetter.h"
#include "sort.h"
#include "tst.h"

#define LINELENGTH 128

/**
 * Reads the given path and inserts the words in the TST.
 * Returns the number of words read.
 */
int readWords(const char *path, TSTNode **root, int nbRepetitions)
{
	// Opens file
	FILE *file = fopen(path, "r");

	// If open fails
	if (file == NULL)
	{
		fprintf(stderr, "ERROR: Could not open the words file.\n");
		exit(-1);
	}

	char line[LINELENGTH];
	int counter = 0;

	// Reads LINELENGTH char for each line
	while (fgets(line, LINELENGTH, file))
	{
		for (int i = 0; line[i]; i++)
		{
			line[i] = tolower(line[i]);
		}

		// Inserts in TST
		const char newline[2] = "\n";
		char *word = strtok(line, newline);
		insertTST(root, word, nbRepetitions);

		// Increments counter
		counter++;
	}

	return counter;
}

/**
 * Reads the given path and inserts the letters in the given array.
 * Returns the number of letters read.
 */
int readLetters(const char *path, char **letters)
{
	// Opens file
	FILE *file = fopen(path, "r");

	// If open fails
	if (file == NULL)
	{
		fprintf(stderr, "ERROR: Could not open the letters file.\n");
		exit(-1);
	}

	char line[LINELENGTH];
	int counter = 0;

	// Reads LINELENGTH char for each line
	while (fgets(line, LINELENGTH, file))
	{
		// Allocate memory
		*letters = realloc(*letters, (counter + 1) * sizeof(char));

		// If realloc fails
		if (letters == NULL)
		{
			fprintf(stderr,
					"ERROR: Could not reallocate memory for the letters.\n");
			exit(-1);
		}

		// Copies the read letter into the array
		(*letters)[counter] = tolower(line[0]);

		// Increments counter
		counter++;
	}

	return counter;
}

/**
 * Reads the given path and inserts the scores in the given array.
 * Returns the number of scores read.
 */
int readScores(const char *path, int **scores)
{
	// Opens file
	FILE *file = fopen(path, "r");

	// If open fails
	if (file == NULL)
	{
		fprintf(stderr, "ERROR: Could not open the scores file.\n");
		exit(-1);
	}

	char line[LINELENGTH];
	int counter = 0;

	// Reads LINELENGTH char for each line
	while (fgets(line, LINELENGTH, file))
	{
		// Allocate memory
		*scores = realloc(*scores, (counter + 1) * sizeof(int));

		// If realloc fails
		if (scores == NULL)
		{
			fprintf(stderr,
					"ERROR: Could not reallocate memory for the scores.\n");
			exit(-1);
		}

		// Copies the read letter into the array
		(*scores)[counter] = atoi(line);

		// Increments counter
		counter++;
	}

	return counter;
}

/**
 * Adds the given letter at the beginning of the first word of every solution
 */
void addFirst(ListOfSolution solutions, ScoredLetter letter)
{
	// Loops through every solution
	for (int i = 0; solutions[i]; i++)
	{
		// Computes first word length
		int length = 0;
		for (int k = 0; solutions[i][0][k].letter != '\0'; k++)
		{
			length++;
		}
		length++;

		// Reallocates to add one letter
		solutions[i][0] = realloc(solutions[i][0],
								  (++length) * sizeof(ScoredLetter));

		// Shifts every letters one cell to the right
		for (int k = length - 1; k > 0; k--)
		{
			solutions[i][0][k] = solutions[i][0][k - 1];
		}

		// Adds the letter at the first position
		solutions[i][0][0] = letter;
	}
}

/**
 * Concatenates two solutions into a new one
 */
Solution concatenate(Solution a, Solution b)
{
	// Computes a's length
	int nbWordsA;
	for (nbWordsA = 0; a[nbWordsA]; nbWordsA++)
		;

	// Computes b's length
	int nbWordsB;
	for (nbWordsB = 0; b[nbWordsB]; nbWordsB++)
		;

	// Allocate new solution
	int resultSize = nbWordsA + nbWordsB + 1;
	Solution result = malloc(resultSize * sizeof(ScoredString));

	for (int i = 0; i < resultSize - 1; i++)
	{
		// Copies a's elements
		if (i < nbWordsA)
		{
			result[i] = a[i];
		}
		// Copies b's elements
		else
		{
			result[i] = b[i - nbWordsA];
		}
	}

	result[resultSize - 1] = NULL;

	return result;
}

/**
 * Merges two lists of solutions into a new one.
 *
 * Concatenates every elements of the second to every element of the first one.
 */
ListOfSolution mergeSolutions(ListOfSolution a,
							  ListOfSolution b)
{
	// Computes solutions length
	int aSize;
	for (aSize = 0; a[aSize]; aSize++)
		;

	// Computes additions length
	int bSize;
	for (bSize = 0; b[bSize]; bSize++)
		;

	// Allocates new list of solutions
	ListOfSolution result = malloc((aSize * bSize + 1) * sizeof(Solution));

	// Fills new list
	for (int i = 0; i < aSize; i++)
	{
		for (int j = 0; j < bSize; j++)
		{
			result[bSize * i + j] = concatenate(a[i], b[j]);
		}
	}
	result[aSize * bSize] = NULL;

	return result;
}

ListOfSolution solverAux(TSTNode *dict, TSTNode *root, ScoredString letters)
{
	// Returned variable
	ListOfSolution solutions = NULL;

	// Number of registered solutions
	int nbSolutions = 0;

	// Score of the best solution found so far
	int bestScoreSolutions = -999;

	// Loops every letters
	for (int i = 0; letters[i].letter != '\0'; i++)
	{
		ScoredLetter currentScoredLetter = letters[i];

		char currentLetter[2];
		currentLetter[0] = currentScoredLetter.letter;
		currentLetter[1] = '\0';

		TSTNode *currentNode = searchTST(dict, currentLetter);

		// If there is a hit for that letter
		if (currentNode)
		{
			// End of a word
			if (currentNode->endOfWord)
			{
				ScoredString subLetters = NULL;

				currentNode->endOfWord -= 1;

				// Reove the current letter from the available letters
				subLetters = removeElementAt(letters, i);

				// Calls itself recursively
				// from the root of the tree with rhe remaining letters
				ListOfSolution subSolutions = solverAux(root,
														root,
														subLetters);

				ScoredString emptyWord = malloc(sizeof(ScoredLetter));
				emptyWord[0] = NULLLETTER;

				Solution emptySolution = malloc(2 * sizeof(ScoredString));
				emptySolution[0] = emptyWord;
				emptySolution[1] = NULL;

				ListOfSolution emptyList = malloc(2 * sizeof(Solution));
				emptyList[0] = emptySolution;
				emptyList[1] = NULL;

				int subScore = scoreOfSolutions(subSolutions);
				int score = currentScoredLetter.score + subScore;

				if (score < 0)
				{
					subSolutions = emptyList;
				}

				if (bestScoreSolutions <= score)
				{

					// Adds the letter to a new word in the solution
					if (bestScoreSolutions < score)
					{
						bestScoreSolutions = score;
						nbSolutions = 0;
						solutions = NULL;
					}

					nbSolutions = nbSolutions ? nbSolutions : 1;

					int size = ++nbSolutions;
					solutions = realloc(solutions, size * sizeof(Solution));
					solutions[size - 2] = malloc(2 * sizeof(ScoredString));
					solutions[size - 2][0] = malloc(2 * sizeof(ScoredLetter));
					solutions[size - 2][0][0] = currentScoredLetter;
					solutions[size - 2][0][1] = NULLLETTER;
					solutions[size - 2][1] = NULL;
					solutions[size - 1] = NULL;

					if (subSolutions)
					{
						solutions = mergeSolutions(solutions, subSolutions);
					}
					else
					{
						solutions = solutions;
					}
				}
			}
			// Not end of word
			else
			{
				TSTNode *subDict = currentNode->middle;
				if (subDict)
				{
					// Removes the current letter from the available ones
					ScoredString subLetters = removeElementAt(letters, i);

					// Calls itself recursively
					// from the middle'ssubtree with rhe remaining letters
					ListOfSolution auxSolutions = solverAux(subDict,
															root,
															subLetters);

					// If there is a result from the recursive call
					if (auxSolutions)
					{

						for (nbSolutions = 0; auxSolutions[nbSolutions]; nbSolutions++)
							;
						nbSolutions++;

						int recursiveScore = currentScoredLetter.score +
											 scoreOfSolutions(auxSolutions);

						if (!solutions)
						{
							solutions = copySolutions(auxSolutions);

							addFirst(solutions, currentScoredLetter);

							bestScoreSolutions = scoreOfSolutions(solutions);
						}
						else if (bestScoreSolutions < recursiveScore)
						{
							solutions = copySolutions(auxSolutions);

							addFirst(solutions, currentScoredLetter);

							bestScoreSolutions = scoreOfSolutions(solutions);
						}

						// If the recursive call found a solution
						// with a zero score, adds the empty word
						if (bestScoreSolutions == 0)
						{
							int size = ++nbSolutions;
							solutions = realloc(solutions,
												size * sizeof(Solution));
							solutions[size - 2] = malloc(2 * sizeof(ScoredString));
							solutions[size - 2][0] = malloc(sizeof(ScoredLetter));
							solutions[size - 2][0][0] = NULLLETTER;
							solutions[size - 2][1] = NULL;
							solutions[size - 1] = NULL;
						}
					}
				}
			}
		}
	}

	return solutions;
}

void solver(TSTNode *dict, ScoredString letters)
{
	ListOfSolution solutions = solverAux(dict, dict, letters);

	displaySolutions(solutions);
}

int main(int argc, char const *argv[])
{
	//
	// Arguments parsing
	//
	if (argc != 4 && argc != 5)
	{
		fprintf(stderr, "ERROR: Wrong number of arguments.\n");
		exit(-1);
	}

	const char *pathToWords = argv[1];
	const char *pathToLetters = argv[2];
	const char *pathToScores = argv[3];

	int nbRepetitions = 1;

	if (argc == 5)
	{
		nbRepetitions = atoi(argv[4]);
		if (nbRepetitions <= 0)
		{
			fprintf(stderr,
					"ERROR: The number of repetitions must be greater than zero.\n");
			exit(-1);
		}
	}

	// Reads words
	TSTNode *dict = NULL;
	readWords(pathToWords, &dict, nbRepetitions);

	// Reads letters
	char *letters = NULL;
	int nbLetters = readLetters(pathToLetters, &letters);

	// Reads scores
	int *scores = NULL;
	int nbScores = readScores(pathToScores, &scores);

	// Checks matching sizes
	if (nbScores != nbLetters)
	{
		fprintf(stderr,
				"ERROR: Letters and scores files don't have the same size.");
		exit(-1);
	}

	// Creates a ScoredString with the letters and their score
	ScoredString scoredLetters = malloc(nbLetters * sizeof(ScoredLetter));
	for (int i = 0; i < nbLetters; i++)
	{
		scoredLetters[i] = newScoredLetter(letters[i], scores[i]);
	}

	free(scores);
	free(letters);

	// Sorts the letter according to the scores
	quicksort(scoredLetters, 0, nbLetters - 1);

	scoredLetters = realloc(scoredLetters,
							(++nbLetters) * sizeof(ScoredLetter));
	scoredLetters[nbLetters - 1] = NULLLETTER;

	// Solves
	solver(dict, scoredLetters);

	return 0;
}
