// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

//loops through linked list
int counter=0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index;
    index = hash(word);
    node *temp=table[index];
    while(temp!= NULL){
        if(strcasecmp(word,temp->word)==0){
            return true;
        }
        temp = temp->next;
    }
        return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++))){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    unsigned int index = hash % N;
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)

{
    //read every word in dictionary while loading
    FILE *file = fopen(dictionary, "r");
    if(file ==NULL){
        printf("Error");
        return false;
    }
    char myword[LENGTH + 1];
    for (int i = 0;; i++)
    {
        if(fscanf(file, "%s", myword)!=EOF){
            node *temp = (node *)malloc(sizeof(node));
            strcpy(temp->word, myword);
            int index = hash(myword);
            temp->next=NULL;
            if (table[index] == NULL)
            {
                table[index] = temp;
                counter++;
            }
            else
            {
                temp->next = table[index]->next;
                table[index]->next = temp;
                counter++;
            }
        } else{
            fclose(file);
            return true;
        }
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++) {
        node *temp = table[i];
        while(temp != NULL){
            node *deleted = temp;
            temp=temp->next;
            free(deleted);
        }
    }
        return true;
}
