
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "levenshtein.c/levenshtein.h"

typedef enum BOOL { false,
                    true } Boolean;

// Linked list node definition
typedef struct NODE Node;

struct NODE
{
    char *string;
    Node *next;
};

static Node *top = NULL;
static int numNodes = 0;

// used to track where we are for the list traversal methods
static Node *traverseNode = NULL;

int size()
{
    return numNodes;
}

// add an element to the beginning of the linked list
Boolean insert(char const *const new_string)
{
    Boolean rc = true;
    Node *newNode = NULL;

#ifndef NDEBUG
    assert(new_string != NULL);
    assert(strcmp("", new_string) != 0); // ensures the string inserted will not be NULL
#endif

    if (new_string != NULL && strcmp("", new_string) != 0)
    {
        newNode = (Node *)malloc(sizeof(Node));

#ifndef NDEBUG
        assert(newNode != NULL);
#endif

        if (newNode != NULL)
        {
            newNode->next = top;
            top = newNode;

            // note that we need to have space for the string as well!
            newNode->string = (char *)malloc(strlen(new_string) + 1);

#ifndef NDEBUG
            assert(newNode->string != NULL);
#endif

            if (newNode->string != NULL)
            {
                strcpy(newNode->string, new_string);
                top = newNode;
                numNodes++;
            }
        }
    }
    else
    {
        free(newNode);
        rc = false;
    }

    return rc;
}

// remove an element with the given string
Boolean delete (char const *const target)
{
    Boolean deleted = false;
    Node *curr = top;
    if (curr != NULL)
    {
        Node *prev = NULL;

#ifndef NDEBUG
        assert(target != NULL);
        assert(strcmp("", target) != 0);
#endif

        if (target != NULL && strcmp("", target) != 0)
        {
            while (curr != NULL && strcmp(target, curr->string) != 0)
            {
                prev = curr;
                curr = curr->next;
            }

            if (curr != NULL)
            {
                if (prev != NULL)
                    prev->next = curr->next;
                else
                    top = curr->next;

                free(curr->string);

                free(curr);

                deleted = true;
                numNodes--;
            }
        }
    }
    return deleted;
}

// tells us whether or not the given string is in the list
Boolean search(char const *const target)
{
    Boolean found = false;
    Node *curr = top;

    if (curr != NULL && target != NULL)
    {
#ifndef NDEBUG
        assert(curr != NULL);
        assert(target != NULL);
#endif

        while (curr != NULL && !found)
        {

#ifndef NDEBUG
            assert(curr->string != NULL);
#endif

            if (strcmp(target, curr->string) == 0)
            {
                found = true;
            }

            // else if levenshtein of two targets, less than 5, then insert into list

            else
            {
                curr = curr->next;
            }
        }
    }
    return found;
}

// starts a list traversal by getting the data at top
char *firstItem()
{
    char *item = NULL;

    if (top != NULL)
    {
        traverseNode = top->next;
        item = top->string;
    }

    return item;
}

// gets the data at the current traversal node and increments the traversal
char *nextItem()
{
    char *item = NULL;

    // no need to go past the end of the list...
    if (traverseNode != NULL)
    {
        item = traverseNode->string;

#ifndef NDEBUG
        assert(item != NULL);
#endif
        traverseNode = traverseNode->next;
    }

    return item;
}

//will clean the entire list
void wipeTable()
{
    Node *curr = top;

    while (top != NULL && numNodes >= 0)
    {
        top = top->next;
        free(curr->string);

        curr->string = NULL;
        free(curr);

        curr = top;

        numNodes--;
    }
}
// read from standard input, tokenize and insert words into a linked list
// note that we must ensure that there are no duplicates in our list
char *loadDict(char *fileName, char const *const target)
{
#define LINE_SIZE 256

    FILE *dictFile = fopen(fileName, "r");
    if (dictFile == NULL)
        return NULL;

    char input[LINE_SIZE];
    char *token = NULL;
    char *suggested = malloc(sizeof(char) * 50);
    suggested[0] = '\0';

    unsigned int shortest = 6;
    unsigned int currDist;

    while (fgets(input, LINE_SIZE, dictFile))
    {
        // parse the data into separate elements
        token = strtok(input, " \t\r\f\n");

        while (token)
        {
            currDist = levenshtein(target, token);

            if (!search(token) && (currDist <= 5))
            { //ensures words added into the list are only 5 steps away from the searched word.
                char *temp = malloc(sizeof(char) * strlen(token) + 1);
                strcpy(temp, token);
                int i = 0, j = 0;
                while (temp[i] != '\0')
                {
                    if (isalpha(temp[i]))
                    {
                        temp[j++] = tolower(temp[i]);
                    }
                    i++;
                }
                temp[j] = '\0';
                if (strcmp(temp, "") != 0)
                {
                    insert(temp);
                    if (currDist <= shortest)
                    {
                        shortest = currDist;
                        strcpy(suggested, temp);
                    }
                }
                free(temp);
            }
            token = strtok(NULL, " \t\r\f\n");
        }
    }

    return suggested;
}
