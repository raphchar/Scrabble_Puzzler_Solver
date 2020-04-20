/*
	Programming Techniques - Project 1

	main.c


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Reads the file from the given path and returns an array of letter
 */
char *readLetters(const char *path)
{
	// Opens file
	FILE *file = fopen(path, "r");

	// If open fails
	if (file == NULL)
	{
		printf("ERROR: Could not open the letters file.\n");
		exit(-1);
	}

	size_t lineLength = 4;
	char line[lineLength];
	char *letters = NULL;
	int counter = 0;

	// Reads 1 char for each line
	while (fgets(line, lineLength, file))
	{
		// Allocate memory
		letters = realloc(letters, (counter+1) * sizeof(char));

		// Copies the read letter into the array
		letters[counter] = line[0];

		// Increments counter
		counter++;
	}

	return letters;
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
	// const char *pathToScores = argv[3];

	char *letters = readLetters(pathToLetters);

	printf("Letters : %s\n", letters);

	return 0;
}
