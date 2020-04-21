/*
	Programming Techniques - Project 1

	main.c


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINELENGTH 128

/**
 * Reads the file from the given path and returns an array of letter
 */
size_t readLetters(const char *path, char *letters)
{
	// Opens file
	FILE *file = fopen(path, "r");

	// If open fails
	if (file == NULL)
	{
		printf("ERROR: Could not open the letters file.\n");
		exit(-1);
	}

	char line[LINELENGTH];
	size_t counter = 0;

	// Reads LINELENGTH char for each line
	while (fgets(line, LINELENGTH, file))
	{
		// Allocate memory
		letters = realloc(letters, (counter + 1) * sizeof(char));

		// Copies the read letter into the array
		letters[counter] = line[0];

		// Increments counter
		counter++;
	}

	return counter;
}

/**
 * Reads the file from the given path and returns an array of score
 */
size_t readScores(const char *path, int *scores)
{
	// Opens file
	FILE *file = fopen(path, "r");

	// If open fails
	if (file == NULL)
	{
		printf("ERROR: Could not open the score file.\n");
		exit(-1);
	}

	char line[LINELENGTH];
	size_t counter = 0;

	// Reads LINELENGTH char for each line
	while (fgets(line, LINELENGTH, file))
	{
		// Allocate memory
		scores = realloc(scores, (counter + 1) * sizeof(int));

		// Copies the read letter into the array
		scores[counter] = atoi(line);

		// Increments counter
		counter++;
	}

	return counter;
}

int main(int argc, char const *argv[])
{
	if (argc != 4)
	{
		printf("ERROR: Wrong number of arguments.\n");
		exit(-1);
	}

	// const char *pathToWords = argv[1];
	const char *pathToLetters = argv[2];
	const char *pathToScores = argv[3];

	// Reads letters
	char *letters = NULL;
	size_t nbLetters = readLetters(pathToLetters, letters);
	printf("Letters : %s\n", letters);
	printf("NB Letters : %zu\n", nbLetters);

	// Reads scores
	int *scores = NULL;
	size_t nbScores = readScores(pathToScores, scores);
	printf("NB Scores : %zu\n", nbScores);

	return 0;
}
