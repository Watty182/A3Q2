//-----------------------------------------
// NAME: Ryan Watkins
// STUDENT NUMBER: 7691844
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: 3, QUESTION: 1
//
// REMARKS: This program will suggest the
//-----------------------------------------

#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int main(int argc, char *argv[])
{
#define WORD_SIZE 50
    if (argc < 2)
    {
        printf("You failed to enter a dictionary filename. :(\n");
        return 0;
    }

    char usrIn[WORD_SIZE];
    printf("What word should I check?\n");

    //get user input
    fgets(usrIn, WORD_SIZE, stdin);
    int i = 0;
    int j = 0;

    while (usrIn[i] != '\0')
    {
        if (isalpha(usrIn[i]))
        {
            usrIn[j++] = tolower(usrIn[i]);
        }
        i++;
    }
    usrIn[j] = '\0';
    //load up dictionary from cmd input and compare with user input
    char *best = loadDict(argv[1], usrIn);
    if (strcmp(usrIn, best) == 0)
    {
        printf("You can spell, configulations!\n");
    }
    else
    {
        int remaining = size();
        printf("You entered \"%s\"; did you mean \"%s\"\n", usrIn, best);
        printf("There are %d other words similar to \"%s\"\nWould you like to display them? y/n\n", remaining, usrIn);
        fgets(usrIn, WORD_SIZE, stdin);

        if (usrIn[0] == 'y')
        {
            while (remaining > 0)
            {
                int thisRnd = remaining > 10 ? 10 : remaining;
                printf("Press enter for the next %d entries of %d remaining", thisRnd, remaining);
                fgets(usrIn, WORD_SIZE, stdin);
                for(int k = 0; k < thisRnd; k++)
                {
                    char *word = firstItem();
                    if(word == NULL)
                        break;
                    printf("%s", word);
                    delete(word);
                    if(k < (remaining-1) && k < 9)
                        printf(", ");
                }
                printf("\n");
                remaining -= 10;
            }
        }
        else if(usrIn[0] != 'n')
        {
            printf("%s is an invalid input >.<!\n", usrIn);
        }
    }
}
