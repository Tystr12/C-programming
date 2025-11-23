// Name: main.c
// Purpose: A todo terminal application built in C using cJSON for JSON handling
// Author: Ty Strong
// Date: 2025-11-13

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "todo.h"
#include "cJSON.h"



int main()
{
    bool running = true;
    while (running) 
    { 
        printf("Todo Application\n");
        printf("1. Add Todo\n");
        printf("2. View Todos\n");
        printf("3. Exit\n");
        printf("Choose an option: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Add Todo selected.\n");
                todo_add();
                break;
            case 2:
                printf("View Todos selected.\n");
                // View todos logic here
                break;
            case 3:
                running = false;
                printf("Exiting application.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }

    return 0;
}

