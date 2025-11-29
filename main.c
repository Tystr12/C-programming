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
    ToDo **todoList = NULL;
    size_t todoCount = 0;
    cJSON *jsonList = NULL;
    bool running = true;
    while (running) 
    { 
        printf("--------------------\n");
        printf("Todo Application\n");
        printf("1. Add Todo\n");
        printf("2. View Todos\n");
        printf("3. Exit\n");
        printf("--------------------\n");
        printf("Choose an option: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
            bool runningTodo = true;
            while (runningTodo) {
                printf("Add Todo selected.\n");
                printf("--------------------\n");
                printf("Enter description: ");

                char desc[256];
                scanf(" %[^\n]", desc);
                printf("Enter priority (1-5): ");
                int priority;
                scanf("%d", &priority);
                ToDo *newTodo = createToDo(desc, priority);
                printToDo(newTodo);

                // Use a cJSON* (do not copy by value)
                cJSON *json = toDoToJSON(newTodo);
                printJson(json);

                // Add to todoList BEFORE freeing the ToDo (list will own the pointer)
                addTodotolist(&todoList, &todoCount, newTodo);

                convertToDoListToJsonArray(todoList, todoCount, &jsonList);

                printf("Current ToDo List:\n");
                printToDoList(todoList, todoCount);
                printJsonList(jsonList);

                cJSON_Delete(json);

                printf("Todo added successfully!\n");
                printf("--------------------\n");
                printf("Add another todo? (1 = yes, 0 = no): ");
                int addMore;
                scanf("%d", &addMore);
                if (addMore == 0) {
                    runningTodo = false;
                }
            }
                

                // free the jsonList created for the full list (owned by us here)
                //if (jsonList) { cJSON_Delete(jsonList); jsonList = NULL; }

                // Do NOT free(newTodo) here — it is stored in todoList and should be freed
                // when removing items or at program exit.
                break;
            case 2:
            bool runningViewTodo = true;
            while (runningViewTodo) {

                printf("View Todos selected.\n");
                printf("**************************\n");
                printToDoList(todoList, todoCount);
                printJsonList(jsonList);
                printf("**************************\n");
                printf("Return to main menu? (1 = yes, 0 = no): ");
                int returnMain;
                scanf("%d", &returnMain);
                if (returnMain == 1) {
                    runningViewTodo = false;
                }
            }
                break;
            case 3:
                running = false;
                printf("Exiting application.\n");
                // Free all ToDo items
                for (size_t i = 0; i < todoCount; i++) {
                    freeToDo(todoList[i]);
                }
                free(todoList);
                // Free the JSON list
                if (jsonList) {
                    cJSON_Delete(jsonList);
                }
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }

    return 0;
}

