// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1170;
bool loaded = false;
int wordCount = 0;
// Hash table
node *table[N];


bool strcmpy(const char *word1, const char *word2)
{
    int i = 0;
    while (word1[i] != '\0' && word2[i] != '\0')
    {
        if (word1[i] != word2[i])
        {
            return false;
        }
    }
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int wordHash = hash(word);
    node *n = table[wordHash];
    if (n != NULL)
    {

    }
    if (n != NULL)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
        while (n->next != NULL)
        {
            if (strcasecmp(n->word, word) == 0)
            {
                return true;
            }
            else
            {
                n = n->next;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int returnHash = 0;
    int p = 0;
    while (word[p] != '\0')
    {
        returnHash = returnHash + tolower(word[p]) % 96 ;
        p++;
    }
    return returnHash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO:
    /* iterate through file named in the string char *dictionary, adding each to list at table[hash(dictionary)]
    */
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    FILE *D = fopen(dictionary, "r");
    if (D ==  NULL)
    {
        printf("Couldn't open file.\n");
        return false;
    }
    int index = 0;
    int h = 0;
    char word[45 + 1];
    node *n = malloc(sizeof(node));
    for (int c = fgetc(D); c != EOF; c = fgetc(D))
    {
        if (n == NULL)
        {
            return false;
        }
        n->next = NULL;
        if (c != '\n')//no new word
        {
            n->word[index] = c;
            word[index] = c;
            index++;
        }
        else
        {//found '\n'!
            n->word[index] = '\0';
            word[index] = '\0';
            for(int i = 0; i < 46; i++)
            {
                n->word[i] = word[i];
            }
            //  printf("%s,", n->word);
            //add word to list at hash of word
            h = hash(word);
            index = 0;
            if (table[h] == NULL) // there is no list here, create it
            {
                table[h] = n;
            }
            else{//there is a list, add it to the beginning
                n->next = table[h];
                table[h] = n;
            }
           // wordCount = wordCount + 1;
            /*to insert at beginning of list
            n->next = list;//this node points to what was the first node
            list = n;*/
            n = malloc(sizeof(node));
        }
    }
    free(n);
    fclose(D);
    /*while(fread(buffer, sizeof(char), 1, D) == 1)
    {
        if( buffer[0] == '\n')
        {

        }
    }deprecated?*/
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (!loaded)
    {
        return 0;
    }
    for (int i = 0 ; i < N; i++)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            wordCount = wordCount + 1;
            //printf("%s,", tmp->word);
        }
    }
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *e = NULL;
    node *j = NULL;
    for (int i = 0; i < N; i++)
    {
        j = table[i];
        while (j != NULL)
        {
            e = j;
            j = j->next;
            free(e);
        }
    }
    return true;
}
