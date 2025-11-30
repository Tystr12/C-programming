// Name: main.c
// Purpose: A todo terminal application built in C using cJSON for JSON handling
// Author: Ty Strong
// Date: 2025-11-13

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "todo.h"
#include "cJSON.h"

// Global variables for signal handler
ToDo **g_todoList = NULL;
size_t g_todoCount = 0;
cJSON *g_jsonList = NULL;

// Signal handler for CTRL+C
void handleSigint(int sig) {
    printf("\n\n--------------------\n");
    printf("CTRL+C detected.\n");
    printf("Exiting without saving.\n");
    printf("Your changes have NOT been saved.\n");
    printf("--------------------\n");
    
    // Free all ToDo items
    for (size_t i = 0; i < g_todoCount; i++) {
        freeToDo(g_todoList[i]);
    }
    free(g_todoList);
    
    // Free the JSON list
    if (g_jsonList) {
        cJSON_Delete(g_jsonList);
    }
    
    printf("Application exited.\n");
    exit(0);
}

// Safe helpers for reading lines and integers
static int readLine(char *buf, size_t size) {
    if (!fgets(buf, size, stdin)) return 0;
    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';
    return 1;
}

static int promptInt(const char *prompt, int *out) {
    char buf[128];
    if (prompt) printf("%s", prompt);
    if (!readLine(buf, sizeof(buf))) return 0;
    char *end = NULL;
    errno = 0;
    long val = strtol(buf, &end, 10);
    if (errno != 0 || end == buf || *end != '\0') return 0;
    *out = (int)val;
    return 1;
}

int main(void)
{
    srand(time(NULL));
    
    // Register signal handler for CTRL+C
    signal(SIGINT, handleSigint);
    
    ToDo **todoList = NULL;
    size_t todoCount = 0;
    cJSON *jsonList = NULL;
    bool running = true;
    FILE *fileptr;

    if (fileExists("todos.json")) {
        printf("Save File exists.\n");
    } else {
        printf("File does not exist. Creating file.\n");
        createFile("todos.json");
    }

    // Load todos from file on startup
    todoList = loadToDoListFromJSONFile("todos.json", &todoCount);
    g_todoList = todoList;  // Update global pointer
    g_todoCount = todoCount;
    
    if (todoList && todoCount > 0) {
        printf("Loaded %zu todos from file.\n", todoCount);
    }

    while (running) 
    { 
        printf("--------------------\n");
        printf("Todo Application\n");
        printf("1. Add Todo\n");
        printf("2. View Todos\n");
        printf("3. Exit and Save List\n");
        printf("4. Mark Todo as Complete\n");
        printf("--------------------\n");

        int choice;
        if (!promptInt("Choose an option: ", &choice)) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) 
        {
            case 1:
            {
                bool runningTodo = true;
                while (runningTodo) {
                    printf("Add Todo selected.\n");
                    printf("--------------------\n");
                    printf("Enter description: ");

                    char desc[256];
                    if (!readLine(desc, sizeof(desc))) {
                        printf("Failed to read description.\n");
                        break;
                    }

                    int priority;
                    while (!promptInt("Enter priority (1-5): ", &priority)) {
                        printf("Invalid priority. Enter a number 1-5.\n");
                    }

                    ToDo *newTodo = createToDo(desc, priority);
                    printToDo(newTodo);

                    cJSON *json = toDoToJSON(newTodo);
                    printJson(json);

                    addTodotolist(&todoList, &todoCount, newTodo);
                    g_todoList = todoList;  // Update global pointer
                    g_todoCount = todoCount;
                    
                    convertToDoListToJsonArray(todoList, todoCount, &jsonList);
                    g_jsonList = jsonList;  // Update global pointer

                    printf("Current ToDo List:\n");
                    printToDoList(todoList, todoCount);
                    printJsonList(jsonList);

                    cJSON_Delete(json);

                    printf("Todo added successfully!\n");
                    printf("--------------------\n");

                    int addMore;
                    while (!promptInt("Add another todo? (1 = yes, 0 = no): ", &addMore)) {
                        printf("Please enter 1 or 0.\n");
                    }
                    if (addMore == 0) {
                        runningTodo = false;
                    }
                }
                break;
            }
            case 2:
            {
                bool runningViewTodo = true;
                while (runningViewTodo) {
                    printf("View Todos selected.\n");
                    printf("**************************\n");
                    printToDoList(todoList, todoCount);
                    printJsonList(jsonList);
                    printf("**************************\n");
                    int returnMain;
                    while (!promptInt("Return to main menu? (1 = yes, 0 = no): ", &returnMain)) {
                        printf("Please enter 1 or 0.\n");
                    }
                    if (returnMain == 1) {
                        runningViewTodo = false;
                    }
                }
                break;
            }
            case 3:
                running = false;
                printf("Exiting application.\n");
                
                // Save todos to file before exit
                if (saveToDoList(todoList, todoCount, "todos.json")) {
                    printf("Todos saved to file.\n");
                } else {
                    printf("Failed to save todos.\n");
                }
                
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
            case 4:
            {
                printf("Mark todo as complete selected.\n");
                int id;
                while (!promptInt("Enter the ID of the todo to mark as complete: ", &id)) {
                    printf("Invalid ID. Please enter a numeric ID.\n");
                }
                if (markToDoAsComplete(id, todoList, todoCount)) {
                    printf("Todo with ID %d marked as complete.\n", id);
                    
                    // Rebuild JSON array after marking complete
                    if (jsonList) cJSON_Delete(jsonList);
                    convertToDoListToJsonArray(todoList, todoCount, &jsonList);
                    g_jsonList = jsonList;  // Update global pointer
                    
                } else {
                    printf("Todo with ID %d not found.\n", id);
                }
                printf("--------------------\n");
                printf("Current ToDo List:\n");
                printToDoList(todoList, todoCount);
                printf("--------------------\n");
                int deleteChoice;
                while (!promptInt("Would you like to delete the todo that is completed? (1 = yes, 0 = no): ", &deleteChoice)) {
                    printf("Please enter 1 or 0.\n");
                }
                if (deleteChoice == 1) {
                    if (deleteToDoById(id, &todoList, &todoCount)) {
                        printf("Todo with ID %d deleted successfully.\n", id);
                        g_todoList = todoList;  // Update global pointer
                        g_todoCount = todoCount;
                        
                        if (jsonList) cJSON_Delete(jsonList);
                        convertToDoListToJsonArray(todoList, todoCount, &jsonList);
                        g_jsonList = jsonList;  // Update global pointer
                        
                    } else {
                        printf("Failed to delete todo with ID %d.\n", id);
                    }
                }
                break;
            }

            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }
    printf("Application exited.\n");
    return 0;
}

