#include "scoredLetter.h"

ScoredLetter newScoredLetter(char letter, int score)
{
    ScoredLetter *newElement = malloc(sizeof(ScoredLetter));
    newElement->letter = letter;
    newElement->score = score;
    return *newElement;
}

int indexOf(ScoredString array, ScoredLetter letter)
{
    for (int i = 0; array[i].letter != '\0'; i++)
    {
        if (array[i].letter == letter.letter && array[i].score == letter.score)
        {
            return i;
        }
    }

    return -1;
}

ScoredString removeElementAt(ScoredString array, int index)
{
    int size = 0;
    for (size = 0; array[size].letter != '\0'; size++)
        ;

    // If out of bounds
    if (index > size)
    {
        return array;
    }

    ScoredString result = malloc((size) * sizeof(ScoredLetter));

    // If malloc fails
    if (result == NULL)
    {
        fprintf(stderr, "ERROR: Could not reallocate memory for the scores.\n");
        exit(-1);
    }

    int j = 0;
    for (int i = 0; i < size + 1; i++)
    {
        if (i != index)
        {
            result[j++] = array[i];
        }
    }

    return result;
}

ScoredString removeElements(ScoredString array, ScoredString letters)
{
    ScoredString result = array;

    for (int i = 0; letters[i].letter != '\0'; i++)
    {
        int index = indexOf(array, letters[i]);
        if (index != -1)
        {
            result = removeElementAt(result, index);
        }
    }

    return result;
}

int scoreOfString(ScoredString scoredLetters)
{
    // Cumulative sum of the letters'score
    int sum = 0;
    for (size_t i = 0; scoredLetters[i].letter != '\0'; i++)
    {
        sum += scoredLetters[i].score;
    }

    return sum;
}

int scoreOfSolutions(ListOfSolution solutions)
{
    if (!solutions)
    {
        return 0;
    }

    // Cumulative sum of the words'value of one of the solutions
    int score = 0;
    for (int j = 0; solutions[0][j]; j++)
    {
        score += scoreOfString(solutions[0][j]);
    }
    return score;
}

void displaySolutions(ListOfSolution solutions)
{
    // If there isn't any solution
    if (!solutions)
    {
        printf("[] : 0\n");
        return;
    }

    int score = scoreOfSolutions(solutions);

    printf("[ ");
    for (int i = 0; solutions[i]; i++)
    {
        if (i != 0)
        {
            printf(" ");
        }
        printf("[ ");

        for (int j = 0; solutions[i][j]; j++)
        {
            if (j != 0 && solutions[i][j][0].letter != '\0')
            {
                printf(" ");
            }

            for (int k = 0; solutions[i][j][k].letter != '\0'; k++)
            {
                printf("%c", solutions[i][j][k].letter);
            }
        }

        printf(" ]");
    }

    printf(" ] : %d\n", score);
}

ListOfSolution copySolutions(ListOfSolution solutions)
{
    ListOfSolution copy;

    // Allocate solutions
    int nbSolutions;
    for (nbSolutions = 0; solutions[nbSolutions]; nbSolutions++)
        ;

    copy = malloc((nbSolutions + 1) * sizeof(Solution));

    for (int i = 0; i < nbSolutions; i++)
    {
        // Allocate words
        int nbWords;
        for (nbWords = 0; solutions[i][nbWords]; nbWords++)
            ;

        copy[i] = malloc((nbWords + 1) * sizeof(ScoredString));

        for (int j = 0; j < nbWords; j++)
        {
            // Allocate letters
            int nbLetters;
            for (nbLetters = 0;
                 solutions[i][j][nbLetters].letter != '\0';
                 nbLetters++)
                ;

            copy[i][j] = malloc((nbLetters + 1) * sizeof(ScoredLetter));

            for (int k = 0; k < nbLetters; k++)
            {
                copy[i][j][k] = solutions[i][j][k];
            }

            // Set end of string guard
            copy[i][j][nbLetters] = NULLLETTER;
        }

        // Set end of solution guard
        copy[i][nbWords] = NULL;
    }

    // Set end of list guard
    copy[nbSolutions] = NULL;

    return copy;
}

void freeSolution(Solution solution)
{
    for (int i = 0; solution[i]; i++)
    {
        free(solution[i]);
    }
    free(solution);
}

void freeSolutions(ListOfSolution solutions)
{
    for (int i = 0; solutions[i]; i++)
    {
        free(solutions[i]);
    }
    free(solutions);
}
