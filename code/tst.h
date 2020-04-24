#ifndef TST_H
#define TST_H

#include <stdlib.h>

typedef struct TSTNode TSTNode;

/**
 * Represents a node of a Ternary Search Trie
 */
struct TSTNode
{
    char letter;
    unsigned endOfWord;
    struct TSTNode *left;
    struct TSTNode *middle;
    struct TSTNode *right;
};

/**
 * Creates a new TSTNode
 *
 * letter: the letter to put in the new node
 *
 * return: A pointer to the new node
 */
struct TSTNode *newNode(char letter);

/**
 * Inserts a word in the TST
 *
 * root: A pointer to the root node of the TST
 * word: A string representing the word to insert
 * n: An integer representing the number of time a word can be used
 */
void insertTST(struct TSTNode **root, char *word, int n);

/**
 * Searches a given word in a given TST
 *
 * root: A pointer to the root node of the TST
 * word: A string representing the word to insert
 *
 * return: A pointer to the node at the end of the word
 * or NULL is the word is not in the TST
 */
struct TSTNode *searchTST(struct TSTNode *root, char *word);

#endif // TST_H
