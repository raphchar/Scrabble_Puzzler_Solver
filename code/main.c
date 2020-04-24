/**
 * Programming Techniques - Project 1
 *
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

void addFirst(ScoredLetter ***solutions, ScoredLetter letter)
{
	for (int i = 0; solutions[i]; i++)
	{
		int length = 0;
		for (int k = 0; solutions[i][0][k].letter != '\0'; k++)
		{
			length++;
		}
		length++;

		solutions[i][0] = realloc(solutions[i][0], (++length) * sizeof(ScoredLetter));
		for (int k = length - 1; k > 0; k--)
		{
			solutions[i][0][k] = solutions[i][0][k - 1];
		}
		solutions[i][0][0] = letter;
	}
}

ScoredLetter **concat(ScoredLetter **a, ScoredLetter **b)
{
	int nbWordsA;
	for (nbWordsA = 0; a[nbWordsA]; nbWordsA++)
		;

	int nbWordsB;
	for (nbWordsB = 0; b[nbWordsB]; nbWordsB++)
		;

	int resultSize = nbWordsA + nbWordsB + 1;
	ScoredLetter **result = malloc(resultSize * sizeof(ScoredLetter *));

	for (int i = 0; i < resultSize - 1; i++)
	{
		if (i < nbWordsA)
		{
			result[i] = a[i];
		}
		else
		{
			result[i] = b[i - nbWordsA];
		}
	}

	result[resultSize - 1] = NULL;

	return result;
}

ScoredLetter ***mergeSolutions(ScoredLetter ***solutions, ScoredLetter ***additions)
{
	int nbSolutions;
	for (nbSolutions = 0; solutions[nbSolutions]; nbSolutions++)
		;

	int nbAdditions;
	for (nbAdditions = 0; additions[nbAdditions]; nbAdditions++)
		;

	ScoredLetter ***result = malloc((nbSolutions * nbAdditions + 1) * sizeof(ScoredLetter **));

	for (int i = 0; i < nbSolutions; i++)
	{
		for (int j = 0; j < nbAdditions; j++)
		{
			result[nbAdditions * i + j] = concat(solutions[i], additions[j]);
		}
	}
	result[nbSolutions * nbAdditions] = NULL;

	return result;
}

ScoredLetter ***solverAux(TSTNode *dict, TSTNode *root, ScoredLetter *letters, int depth)
{
	// Solutions: Array of Array of Array of ScoredLetter
	// => Set of set of words
	ScoredLetter ***solutions = NULL;
	int nbSolutions = 0;

	int bestSolutions = 0;
	int bestScore = 0;

	// for (int k = 0; k < depth; k++)
	// {
	// 	printf("\t");
	// }
	// printf("Before Loop : ");
	// for (int i = 0; letters[i].letter != '\0'; i++)
	// {
	// 	printf("%c", letters[i].letter);
	// }

	// if (dict)
	// {
	// 	printf("\t|\tRoot : %c\n", dict->letter);
	// }
	// else
	// {
	// 	printf("\t|\tRoot : NULL\n");
	// }

	for (int i = 0; letters[i].letter != '\0'; i++)
	{
		ScoredLetter currentScoredLetter = letters[i];
		// for (int k = 0; k < depth; k++)
		// {
		// 	printf("\t");
		// }
		// printf("CURRENT LETTER : %c\n", currentScoredLetter.letter);

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
				int tmp = bestScore;

				if (!solutions)
				{
					// printf("\t\t\t\tEND OF WORD\n");
					currentNode->endOfWord -= 1;

					bestScore = currentScoredLetter.score;

					nbSolutions = 1;
					solutions = malloc((++nbSolutions) * sizeof(ScoredLetter **));
					solutions[0] = malloc(2 * sizeof(ScoredLetter *));
					solutions[0][0] = malloc(2 * sizeof(ScoredLetter));
					solutions[0][0][0] = currentScoredLetter;
					solutions[0][0][1] = NULLLETTER;
					solutions[0][1] = NULL;
					solutions[1] = NULL;
				}
				else if (bestScore < currentScoredLetter.score)
				{
					// printf("\t\t\t\tEND OF WORD\n");
					currentNode->endOfWord -= 1;

					bestScore = currentScoredLetter.score;

					solutions[0][0][0] = currentScoredLetter;
				}
				else if (bestScore == currentScoredLetter.score)
				{
					// printf("\t\t\t\tEND OF WORD\n");
					currentNode->endOfWord -= 1;

					solutions = realloc(solutions, (++nbSolutions) * sizeof(ScoredLetter **));
					solutions[nbSolutions - 2] = malloc(2 * sizeof(ScoredLetter *));
					solutions[nbSolutions - 2][0] = malloc(2 * sizeof(ScoredLetter));
					solutions[nbSolutions - 2][0][0] = currentScoredLetter;
					solutions[nbSolutions - 2][0][1] = NULLLETTER;
					solutions[nbSolutions - 2][1] = NULL;
					solutions[nbSolutions - 1] = NULL;
				}

				if (tmp < bestScore)
				{
					ScoredLetter *subLetters = NULL;

					// subLetters = removeElements(letters, &currentScoredLetter);
					subLetters = removeElementAt(letters, i);

					// for (int k = 0; k < depth; k++)
					// {
					// 	printf("\t");
					// }
					// printf("Remaining Letters [");
					// print(subLetters);
					// printf("]\n");

					// for (int k = 0; k < depth; k++)
					// {
					// 	printf("\t");
					// }
					// printf("############################# > \n");

					ScoredLetter ***subSolutions = solverAux(root, root, subLetters, depth + 1);

					if (subSolutions)
					{
						// printSolutions(solutions);
						// printf(" x ");
						// printSolutions(subSolutions);
						// printf(" = ");
						// printSolutions(mergeSolutions(solutions, subSolutions, j));
						solutions = mergeSolutions(solutions, subSolutions);
					}

					// free(subsubLetters);

					// for (int k = 0; k < depth; k++)
					// {
					// 	printf("\t");
					// }
					// printf(" < #############################\n");
				}
			}
			else
			{
				TSTNode *subDict = currentNode->middle;
				if (subDict)
				{
					ScoredLetter *subLetters = removeElementAt(letters, i);

					ScoredLetter ***auxSolutions = solverAux(subDict, root, subLetters, depth + 1);

					if (auxSolutions)
					{
						for (nbSolutions = 0; auxSolutions[nbSolutions]; nbSolutions++)
							;
						nbSolutions++;

						// for (int k = 0; k < depth; k++)
						// {
						// 	printf("\t");
						// }
						// printf("=> ");
						// printSolutions(auxSolutions);

						if (!solutions)
						{
							solutions = copySolutions(auxSolutions);

							addFirst(solutions, currentScoredLetter);

							bestSolutions = scoreOfSolutions(solutions);
						}
						else if (bestSolutions < scoreOfSolutions(auxSolutions))
						{
							solutions = copySolutions(auxSolutions);

							addFirst(solutions, currentScoredLetter);

							bestSolutions = scoreOfSolutions(solutions);
						}

						// for (int k = 0; k < depth; k++)
						// {
						// 	printf("\t");
						// }
						// printf("# %d => ", nbSolutions);
						// printSolutions(solutions);

						if (bestSolutions == 0)
						{
							solutions = realloc(solutions, (++nbSolutions) * sizeof(ScoredLetter **));
							solutions[nbSolutions - 2] = malloc(2 * sizeof(ScoredLetter *));
							solutions[nbSolutions - 2][0] = malloc(sizeof(ScoredLetter));
							solutions[nbSolutions - 2][0][0] = NULLLETTER;
							solutions[nbSolutions - 2][1] = NULL;
							solutions[nbSolutions - 1] = NULL;
						}

						// for (int k = 0; k < depth; k++)
						// {
						// 	printf("\t");
						// }
						// printf("# %d => ", nbSolutions);
						// printSolutions(solutions);

						// for (int k = 0; k < depth; k++)
						// {
						// 	printf("\t");
						// }
						// printf("# ");
						// printSolutions(auxSolutions);

						// for (int k = 0; k < depth; k++)
						// {
						// 	printf("\t");
						// }
						// printf("# ");
						// printSolutions(solutions);

						// for (int j = 0; auxSolutions[j]; j++)
						// {

						// }

						// for (int k = 0; k < depth; k++)
						// {
						// 	printf("\t");
						// }
						// printf("@ ");
						// printSolutions(solutions);
					}

					// free(subLetters);
				}
			}
		}
		// printf("---------------------------------------------------------------------------------------\n");
	}

	// for (int k = 0; k < depth; k++)
	// {
	// 	printf("\t");
	// }
	// printf("After Loop => %d\n", bestScore);
	if (solutions)
	{
		for (int k = 0; k < depth; k++)
		{
			printf("\t");
		}
		printf("§ ");
		displaySolutions(solutions);
	}

	return solutions;
}

void solver(TSTNode *dict, ScoredLetter *letters)
{
	// int resultScore = solverAux(dict, nbLetters, letters, 0);
	// ScoredLetter *result = solverAux(dict, nbLetters, letters, 0);
	ScoredLetter ***solutions = solverAux(dict, dict, letters, 0);

	displaySolutions(solutions);
	// printf("Score = %d\n", value(result, ));
	// printf("=> '%s'", result);
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
		int n = atoi(argv[4]);
		if (n <= 0)
		{
			fprintf(stderr, "ERROR: The number of repetitions must be greater than zero.\n");
			exit(-1);
		}
	}

	// Reads words
	TSTNode *dict = NULL;
	readWords(pathToWords, &dict, nbRepetitions);
	// int nbWords = readWords(pathToWords, &dict);
	// printf("%zu words found\n", nbWords);

	// Reads letters
	char *letters = NULL;
	int nbLetters = readLetters(pathToLetters, &letters);
	// printf("%zu letters found\n", nbLetters);

	// Reads scores
	int *scores = NULL;
	int nbScores = readScores(pathToScores, &scores);
	// printf("%zu scores found\n", nbScores);

	if (nbScores != nbLetters)
	{
		fprintf(stderr,
				"ERROR: Letters and scores files don't have the same size.");
		exit(-1);
	}

	// Creates the ScoredLetter object
	ScoredLetter *scoredLetters = malloc(nbLetters * sizeof(ScoredLetter));
	for (int i = 0; i < nbLetters; i++)
	{
		scoredLetters[i] = newScoredLetter(letters[i], scores[i]);
	}

	free(scores);
	free(letters);

	// printf("LETTERS BEFORE : \n");
	// for (int i = 0; i < nbLetters; i++)
	// {
	// 	printf("[%c - %d]", scoredLetters[i].letter, scoredLetters[i].score);
	// }
	// printf("\n");

	// Sorts the letter according to the scores
	quicksort(scoredLetters, 0, nbLetters - 1);

	scoredLetters = realloc(scoredLetters, (++nbLetters) * sizeof(ScoredLetter));
	scoredLetters[nbLetters - 1] = NULLLETTER;

	// printf("LETTERS AFTER : \n");
	// for (int i = 0; i < nbLetters; i++)
	// {
	// 	printf("[%c : %d]", scoredLetters[i].letter, scoredLetters[i].score);
	// }
	// printf("\n");

	// Solves
	solver(dict, scoredLetters);

	return 0;
}
