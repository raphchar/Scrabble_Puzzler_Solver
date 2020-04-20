#include "tst.h"

struct TSTNode *newNode(char letter)
{
    struct TSTNode *node = (struct TSTNode *)malloc(sizeof(struct TSTNode));
    node->letter = letter;
    node->endOfWord = 0;
    node->left = NULL;
    node->middle = NULL;
    node->right = NULL;
    return node;
}

void insertTST(struct TSTNode *root, char *word)
{
    // If root is null, the subtree is empty
    if (!root)
    {
        // Creates node
        root = newNode(*word);
    }

    // If fist character of word is smaller than the root's character
    if (*word < root->letter)
    {
        // Inserts in the left child
        insertTST(root->left, word);
    }
    // If fist character of word is greater than the root's character
    else if (*word > root->letter)
    {
        // Inserts in the right child
        insertTST(root->right, word);
    }
    else
    {
        // If it is the end of the word
        if (!*(word + 1))
        {
            // Sets end of word
            root->endOfWord = 1;
        }
        else
        {
            // Inserts in the middle child
            insertTST(root->middle, word + 1);
        }
    }
}

unsigned searchTST(struct TSTNode *root, char *word)
{
    // If root is NULL, the subtree is empty
    if (!root)
    {
        // There is no hit
        return 0;
    }

    // If fist character of word is smaller than the root's character
    if (*word < root->letter)
    {
        // Searches in the left child
        return searchTST(root->left, word);
    }
    // If fist character of word is greater than the root's character
    else if (*word > root->letter)
    {
        // Searches in the right child
        return searchTST(root->right, word);
    }
    else
    {
        // If it is the end of the word
        if (*(word + 1) == '\0')
        {
            // Returns the node's endOfWord
            return root->endOfWord;
        }
        else
        {
            // Searches in the middle child
            return searchTST(root->middle, word + 1);
        }
    }
}
