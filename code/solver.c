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
size_t readWords(const char *path, TSTNode *root)
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
			line[i] =tolower(line[i]);
		}

		// Inserts in TST
		insertTST(root, line);

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

		// Copies the read letter into the array
		(*scores)[counter] = atoi(line);

		// Increments counter
		counter++;
	}

	return counter;
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
	TSTNode *root = NULL;
	size_t nbWords = readWords(pathToWords, root);
	printf("%zu words found\n", nbWords);

	// Reads letters
	char *letters = NULL;
	size_t nbLetters = readLetters(pathToLetters, &letters);
	printf("%zu letters found\n", nbLetters);
	// printf("LETTERS BEFORE : %s\n", letters);

	// Reads scores
	int *scores = NULL;
	size_t nbScores = readScores(pathToScores, &scores);
	printf("%zu scores found\n", nbScores);

	if (nbScores != nbLetters)
	{
		fprintf(stderr, "ERROR: Letters and scores files don't have the same size.");
		exit(-1);
	}

	// Sorts the letter according to the scores
	// quicksort(scores, letters, 0, nbScores - 1);

	// printf("LETTERS AFTER : %s\n", letters);

	return 0;
}
