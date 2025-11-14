#include <stdio.h>
#include <stdlib.h>
#include "todo.h"


char* createToDoSentence()
{
    int MAX_SENTENCE_LENGTH;
    printf("Enter the maximum length of your sentence (including spaces): ");
    scanf("%d", &MAX_SENTENCE_LENGTH);

    // Clear leftover newline after the number
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // just discard
    }

    char* sentence = malloc(MAX_SENTENCE_LENGTH);
    if (!sentence) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    printf("Enter a sentence of %d letters (use @ to stop early):\n",
           MAX_SENTENCE_LENGTH - 1);

    int i = 0;
    for (; i < MAX_SENTENCE_LENGTH - 1; i++) {
        printf("Enter letter %d: ", i + 1);
        char letter;

        // NOTE: space before %c → skips whitespace (like '\n')
        scanf("%c", &letter);

        if (letter == '@') {
            break;  // stop input early
        }

        sentence[i] = letter;
    }

    // null-terminate at the actual length typed, not MAX_SENTENCE_LENGTH - 1
    sentence[i] = '\0';

    return sentence;
}


int setPriority() 
{
    int priority;
    printf("Enter priority (1-5): ");
    scanf("%d", &priority);
    return priority;
}

ToDo* createToDo() 
{
    ToDo* newToDo = (ToDo*)malloc(sizeof(ToDo)); // allocate memory for new ToDo
    if (newToDo == NULL) 
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newToDo->priority = setPriority(); // set priority
    newToDo->isComplete = false; // set completion status
    newToDo->description = createToDoSentence(); // set description
    return newToDo; // return pointer to new ToDo
}

void printToDo(ToDo* todo) 
{
    if (todo != NULL) 
    {
        printf("To-Do: %s\n", todo->description);
        printf("Priority: %d\n", todo->priority);
        printf("Status: %s\n", todo->isComplete ? "Complete" : "Incomplete");
    }
}

void markToDoComplete(ToDo* todo) 
{
    if (todo != NULL) 
    {
        todo->isComplete = true; // mark as complete
    }
}

void destroyToDo(ToDo* todo) 
{
    if (todo != NULL) 
    {
        free(todo->description); // free description memory
        free(todo); // free ToDo memory
    }
}

