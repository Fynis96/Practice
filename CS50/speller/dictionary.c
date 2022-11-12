// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


//Global counter variable to determine size
int counter = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 924513;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Set temp node to buckets first value, if first value isnt the word, and theres a next pointer, go to next value and repeat until word matches
    for (node *tmp = table[hash(word)]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // This has function takes the ASCII value of the first 3 letters, subtracts by 59, and the squares the numbers based on placement to avoid collisions.
    char l0 = toupper(word[0]);
    char l1 = toupper(word[1]);
    char l2 = toupper(word[2]);

    int sqr = (l1 - 59) * (l1 - 59);
    int sqr2 = (l2 - 59) * (l2 - 59) * (l2 - 59);
    //Check for how many letters in word, only need first three for bucket placement and math.
    if (!(isalpha(word[2])) && !(isalpha(word[1])))
    {
        return l0 - 59;
    }
    else if (!(isalpha(word[2]) && (isalpha(word[1]))))
    {
        return (l0 - 59) + sqr;
    }
    else if (isalpha(word[2]) && isalpha(word[1]))
    {
        return (l0 - 59) + sqr + sqr2;
    }
    else
    {
        return 0;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Check base case
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        printf("Failed to open dictionary\n");
        fclose(input);
        return false;
    }

    // Create temp string for each of inputs words
    char *word = malloc(LENGTH + 1);
    if (word == NULL)
    {
        free(word);
        return false;
    }
    // Scan through file for formatted data, such as an end of string, pop into proper bucket, and increase word counter
    while (fscanf(input, "%s", word) != EOF)
    {
        // Allocate memory for temporary buffer nodes
        node *buffer = malloc(sizeof(node));
        // Handle base case
        if (buffer == NULL)
        {
            free(word);
            return false;
        }

        // Store hash value for word so as to not call the function every time we need its value
        int hashword = hash(word);
        strcpy(buffer->word, word);
        if (table[hashword] == NULL)
        {
            buffer->next = NULL;
        }
        // If bucket already has a node, pop new node into start of linked list
        else
        {
            buffer->next = table[hashword];
        }
        table[hashword] = buffer;
        counter++;
    }
    fclose(input);
    free(word);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return size variable
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through entirety of table[], if element in table[] isn't null, set tmp to next value, free current node in table, set next back to tmp until next is null
    for (int i = 0; i < N - 1; i ++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}

