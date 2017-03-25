#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"

static int testsPassed = 0;
static int testsFailed = 0;
void testDictSingle(char *fileName, char *test, char *expected);
void testDictResultList(char *fileName, char *test, char **expectedLst, int expectedLen);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You failed to enter a dictionary filename. :(\n");
        return 0;
    }

    testDictSingle(argv[1], "restarded", "retarded");
    testDictSingle(argv[1], "quolm", "qualm");
    testDictSingle(argv[1], "pome", "tome");
    testDictSingle(argv[1], "neccesary", "necessary");
    testDictSingle(argv[1], "lactoast", "lactose");
    testDictSingle(argv[1], "intodlerant", "intolerant");

    testDictSingle(argv[1], "brain", "brain");

    char * expectLst[] = {"stringed", "stridden", "stepladder", "stench", "stein", "stained", "standard"};
    testDictResultList(argv[1], "steinddddh", expectLst, 7);

    printf("Tests passed: %d\n", testsPassed);
    printf("Tests failed: %d\n", testsFailed);

    printf("Program completed successfully.\n");
}

void testDictSingle(char *fileName, char *test, char *expected)
{
    char *result = loadDict(fileName, test);
    if (strcmp(result, expected) != 0)
    {
        printf("Failed: expected %s, got %s\n", expected, result);
        testsFailed++;
    }
    else
    {
        testsPassed++;
    }
    wipeTable();
}

void testDictResultList(char *fileName, char *test, char **expectedLst, int expectedLen)
{
    char *result = loadDict(fileName, test);
    if (strcmp(result, expectedLst[0]) != 0)
    {
        printf("Failed: expected %s, got %s\n", expectedLst[0], result);
        testsFailed++;
    }
    else
    {
        int currExp = 0;
        char *word = NULL;
        do
        {
            word = firstItem();
            if (word != NULL)
            {
                if (strcmp(word, expectedLst[currExp++]) != 0)
                {
                    printf("Failed: expected %s, got %s\n", expectedLst[currExp++], word);
                    testsFailed++;
                    break;
                }
                delete (word);
            }
        } while (word != NULL);
        if (word == NULL)
            testsPassed++;
    }
    wipeTable();
}