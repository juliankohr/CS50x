// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Define number of buckets in hash table
const unsigned int N = 5768;

// Hash table
node *table[N];

// Size of dictionary
int size_dict = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Initialize variable containing the bucket of the array, by hashing the word
    int bucket = hash(word);
    // Create a cursor pointing to the bucket in the table
    node *cursor = table[bucket];

    // While value of curser is != 0 compare word with word of the node, if its not there, iterate to the next node, if there, return true
    while (cursor != 0)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Initiate values for charsum and an indes for the word to be hashed
    int charsum = 0;
    int i = 0;
    // While NULL character is not reached, iterate further through lowered characters of the word and add ASCII values to charsum
    while (word[i] != '\0')
    {
        charsum += tolower(word[i]);
        i++;
    }
    // multiply charsum by 57 and then with 68
    charsum *= 57;
    charsum *= 68;
    // return charsum mod N as number of bucket inside the array
    return (charsum % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");

    // If file is NULL aka. error, return false
    if (file == NULL)
    {
        return false;
    }

    // Create array for word
    char wordarr[LENGTH + 1];
    // While file is not at end, store each word in a newly created node
    while (fscanf(file, "%s", wordarr) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, wordarr);
        n->next = NULL;
        int hashed = hash(n->word);
        // If bucket has noch chained links, create first and place NULL in n->next
        if (table[hashed] == NULL)
        {
            table[hashed] = n;
            n->next = NULL;
        }
        // If there are already some nodes, place new node between bucket and first node
        else
        {
            n->next = table[hashed];
            table[hashed] = n;
        }
        // Increment size_dict counter by 1
        size_dict++;
    }
    // Close file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return size_dict determined in load function
    return size_dict;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // For every bucket
    for (int i = 0; i < N; i++)
    {
        // Create initial pointers
        node *cursor = table[i];
        node *tmp = cursor;

        // While courser is != NULL
        while (cursor != NULL)
        {
            // Forward cursor to next node, free current node tmp is pointing to and set tmp equal to cursor
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
