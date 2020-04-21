/*
	Programming Techniques - Project 1

	main.c


*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "tst.h"

#define LINELENGTH 128

/**
 * Reads the given path and inserts the words in the TST.
 * Returns the number of words read.
 */
size_t readWords(const char *path, TSTNode **root)
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
	size_t counter = 0;

	// Reads LINELENGTH char for each line
	while (fgets(line, LINELENGTH, file))
	{
		for (int i = 0; line[i]; i++)
		{
			line[i] = tolower(line[i]);
		}

		// Inserts in TST
		const char newline[2] = "\n";
		insertTST(root, strtok(line, newline));

		// Increments counter
		counter++;
	}

	return counter;
}

/**
 * Reads the given path and inserts the letters in the given array.
 * Returns the number of letters read.
 */
size_t readLetters(const char *path, char **letters)
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
	size_t counter = 0;

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
size_t readScores(const char *path, int **scores)
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
	size_t counter = 0;

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

ScoredLetter *removeElement(ScoredLetter *array, size_t size, size_t index)
{
	ScoredLetter *result = malloc((size - 1) * sizeof(ScoredLetter));

	// If malloc fails
	if (result == NULL)
	{
		fprintf(stderr,
				"ERROR: Could not reallocate memory for the scores.\n");
		exit(-1);
	}

	size_t j = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (i != index)
		{
			result[j++] = array[i];
		}
	}

	return result;
}

int solverAux(TSTNode *dict, size_t nbLetters,
			  ScoredLetter *letters, char *word, int depth)
{
	int maxScore = 0;

	printf("Before Loop :\n");
	for (size_t i = 0; i < nbLetters; i++)
	{
		printf("%c", letters[i].letter);
	}
	printf("\n");

	for (size_t i = 0; i < nbLetters; i++)
	{
		for (int k = 0; k < depth; k++)
		{
			printf("\t");
		}
		printf("CURRENT LETTER : %c\n", letters[i].letter);

		int score = 0;

		char currentLetter[2];
		currentLetter[0] = letters[i].letter;
		currentLetter[1] = '\0';

		TSTNode *currentNode = searchTST(dict, currentLetter);

		// If there is a hit for that letter
		if (currentNode)
		{
			// End of a word
			if (currentNode->endOfWord)
			{
				printf("END OF WORD : (%c - %d)\n", letters[i].letter, letters[i].score);
				currentNode->endOfWord = 0;
				return letters[i].score; // NOT RETURN BUT ADD TO A LIST
			}
			else
			{
				TSTNode *subDict = currentNode->middle;
				ScoredLetter *subLetters = removeElement(letters, nbLetters, i);
				// printf("Score before = %d\n", score);
				score = letters[i].score + solverAux(subDict, nbLetters - 1,
													 subLetters, word, depth + 1);
				// printf("Score after = %d\n", score);

				maxScore += score;
			}
		}
	}

	return maxScore;
}

void solver(TSTNode *dict, size_t nbLetters, ScoredLetter *letters)
{
	char *word = NULL;
	int resultScore = solverAux(dict, nbLetters, letters, word, 0);

	printf("Score = %d\n", resultScore);
	// printf("=> '%s'", result);
}

int main(int argc, char const *argv[])
{
	//
	// Arguments parsing
	//
	if (argc != 4)
	{
		fprintf(stderr, "ERROR: Wrong number of arguments.\n");
		exit(-1);
	}

	const char *pathToWords = argv[1];
	const char *pathToLetters = argv[2];
	const char *pathToScores = argv[3];

	// Reads words
	TSTNode *dict = NULL;
	size_t nbWords = readWords(pathToWords, &dict);
	printf("%zu words found\n", nbWords);

	// Reads letters
	char *letters = NULL;
	size_t nbLetters = readLetters(pathToLetters, &letters);
	printf("%zu letters found\n", nbLetters);

	// Reads scores
	int *scores = NULL;
	size_t nbScores = readScores(pathToScores, &scores);
	printf("%zu scores found\n", nbScores);

	if (nbScores != nbLetters)
	{
		fprintf(stderr,
				"ERROR: Letters and scores files don't have the same size.");
		exit(-1);
	}

	// Creates the ScoredLetter object
	ScoredLetter scoredLetters[nbLetters];
	for (size_t i = 0; i < nbLetters; i++)
	{
		scoredLetters[i] = newScoredLetter(letters[i], scores[i]);
	}

	free(scores);
	free(letters);

	printf("LETTERS BEFORE : \n");
	for (size_t i = 0; i < nbLetters; i++)
	{
		printf("[%c - %d]", scoredLetters[i].letter, scoredLetters[i].score);
	}
	printf("\n");

	// Sorts the letter according to the scores
	quicksort(scoredLetters, 0, nbLetters - 1);

	printf("LETTERS AFTER : \n");
	for (size_t i = 0; i < nbLetters; i++)
	{
		printf("[%c - %d]", scoredLetters[i].letter, scoredLetters[i].score);
	}
	printf("\n");

	// Solves
	solver(dict, nbLetters, scoredLetters);

	return 0;
}
