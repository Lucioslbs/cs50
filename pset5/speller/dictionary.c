#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 65536

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Hash table
node *table[HASHTABLE_SIZE];

// Number of words loaded in the dictionary
unsigned int loaded_words = 0;

// Hash function (djb2)
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c);
    }

    return hash % HASHTABLE_SIZE;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open dictionary.\n");
        return false;
    }

    // Initialize hash table
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        table[i] = NULL;
    }

    // Buffer to store each word read from dictionary
    char word[LENGTH + 1];

    // Read each word from dictionary and add to hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for the word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            fprintf(stderr, "Could not allocate memory.\n");
            return false;
        }

        // Copy word into the node
        strcpy(new_node->word, word);

        // Get hash value for the word
        int index = hash(word);

        // Insert the node into the hash table
        new_node->next = table[index];
        table[index] = new_node;

        // Increment the count of loaded words
        loaded_words++;
    }

    // Close dictionary file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return loaded_words;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get hash value for the word
    int index = hash(word);

    // Traverse the linked list at table[index]
    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        // Compare word with the word in the current node
        int strcasecmp(const char *s1, const char *s2);
        {
            return true; // Word found
        }
    }

    return false; // Word not found
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Free memory for each node in the hash table
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}
