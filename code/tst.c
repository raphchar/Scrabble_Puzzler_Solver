#include <stdlib.h>
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
        root = newNode(*word);
    }

    // If fist character of word is smaller than the root's character
    if (*word < root->letter)
    {
        insertTST(root->left, word);
    }
    // If fist character of word is greater than the root's character
    else if (*word > root->letter)
    {
        insertTST(root->right, word);
    }
    else
    {
        // If it is the end of the word
        if(!*(word+1))
        {
            root->endOfWord = 1;
        }
        else
        {
            insertTST(root->middle, word + 1);
        }
    }
}

unsigned searchTST(struct TSTNode *root, char *word)
{
    // If root is NULL, the subtree is empty
    if (!root)
    {
        return 0;
    }

    // If fist character of word is smaller than the root's character
    if (*word < root->letter)
    {
        return searchTST(root->left, word);
    }
    // If fist character of word is greater than the root's character
    else if (*word > root->letter)
    {
        return searchTST(root->right, word);
    }
    else
    {
        // If it is the end of the word
        if (*(word + 1) == '\0')
        {
            return root->endOfWord;
        }
        else
        {
            return searchTST(root->middle, word + 1);
        }
    }
}
