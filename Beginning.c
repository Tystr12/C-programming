// Name: Beginning.c
// Purpose: A simple C program that prints a famous quote to the console.
// Author: Ty Strong
// Date: 2025-11-13

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "todo.h"

void calculateBox()
{
    int height = 8;
    int length = 12;
    int width = 10;
    int volume = height * length * width;
    printf("Dimensions: %dx%dx%d\n", length, width, height);
    printf("Volume: %d\n", volume);
}

void customBox()
{
    int height, length, width, volume, weight;

    // remember to pass address of the variable to scanf
    printf("Enter height: ");
    scanf("%d", &height);
    printf("Enter length: ");
    scanf("%d", &length);
    printf("Enter width: ");
    scanf("%d", &width);

    volume = height * length * width;
    weight = (volume + 165) / 166;

    printf("Volume (cubic inches): %d\n", volume);
    printf("Dimensional weight (pounds): %d\n", weight);
}

char *createSentence()
{
    int MAX_SENTENCE_LENGTH;
    printf("Enter the maximum length of your sentence (including spaces): ");
    scanf("%d", &MAX_SENTENCE_LENGTH);

    // Clear leftover newline after the number
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        // just discard
    }

    char *sentence = malloc(MAX_SENTENCE_LENGTH);
    if (!sentence)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    printf("Enter a sentence of %d letters (use @ to stop early):\n",
           MAX_SENTENCE_LENGTH - 1);

    int i = 0;
    for (; i < MAX_SENTENCE_LENGTH - 1; i++)
    {
        printf("Enter letter %d: ", i + 1);
        char letter;

        // NOTE: space before %c → skips whitespace (like '\n')
        scanf("%c", &letter);

        if (letter == '@')
        {
            break; // stop input early
        }

        sentence[i] = letter;
    }

    // null-terminate at the actual length typed, not MAX_SENTENCE_LENGTH - 1
    sentence[i] = '\0';

    return sentence;
}

void printAllToDos(ToDo **toDos, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("---------------TODO--------------------\n");
        printf("Index: %d\n", i);
        printToDo(toDos[i]);
        printf("---------------TODO--------------------\n");
    }
}

void destroyAllToDos(ToDo **toDos, int count)
{
    for (int i = 0; i < count; i++)
    {
        destroyToDo(toDos[i]);
    }
}

int main()
{
    bool running = true;
    while (running == true)
    {
        printf("-----------------------------------\n");
        printf("What would you like to do?\n");
        printf("1. Calculate box volume\n");
        printf("2. Calculate custom box volume and weight\n");
        printf("3. Create a sentence\n");
        printf("4. Manage To-Do item\n");
        printf("5. Exit program\n");
        printf("-----------------------------------\n");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("RESULT:\n");
            calculateBox();
            break;
        case 2:
            printf("RESULT:\n");
            customBox();
            break;
        case 3:
        {
            printf("RESULT:\n");
            char *sentence = createSentence();
            printf("Your sentence: %s\n", sentence);
            free(sentence);
            break;
        }
        case 4:
        {
            bool ManageToDo = true;
            ToDo * arrayOfToDos[100];
            int toDoCount = 0;
                while (ManageToDo == true)
                {   printf("***********************************\n");
                    printf("To-Do Menu:\n");
                    printf("1. Create To-Do item\n");
                    printf("2. View all To-Do items\n");
                    printf("3. Mark To-Do item as complete\n");
                    printf("4. Back to main menu\n");
                    printf("***********************************\n");
                    int todoChoice;
                    scanf("%d", &todoChoice);
                    switch (todoChoice)
                    {
                        case 1:
                        {
                            ToDo *newToDo = createToDo();
                            arrayOfToDos[toDoCount++] = newToDo;
                            printf("To-Do item created.\n");
                            break;
                        }
                        case 2:
                        {
                            printf("All To-Do items:\n");
                            printAllToDos(arrayOfToDos, toDoCount);
                            break;
                        }
                        case 3:
                        {
                            printf("Enter the index of the To-Do item to mark as complete (0 to %d): ", toDoCount - 1);
                            int index;
                            scanf("%d", &index);
                            if (index >= 0 && index < toDoCount)
                            {
                                markToDoComplete(arrayOfToDos[index]);
                                printf("To-Do item marked as complete.\n");
                            }
                            else
                            {
                                printf("Invalid index.\n");
                            }
                            break;
                        }
                        case 4:
                        {   
                            printf("Destroying all To-Do items before exiting to main menu.\n");
                            destroyAllToDos(arrayOfToDos, toDoCount);
                            toDoCount = 0;
                            printf("Returning to main menu.\n");
                            ManageToDo = false;
                        }
                        default:
                            printf("Invalid choice\n");
                            break;
                        }
        }
            break;
        }
        case 5:
        {
            printf("RESULT:\n");
            printf("Exiting program.\n");
            running = false;
            return 0;
            break;
        }
        default:
            printf("Invalid choice\n");
            break;
        }
    }

    return 0;
}

