// todo.h
#ifndef TODO_H
#define TODO_H

#include <stdbool.h>
#include <time.h>
#include <stddef.h>   // size_t
#include "cJSON.h"    // ensure cJSON.h (case-sensitive) is available in project

typedef struct {
    int id;
    char *description;    // malloc'd
    int priority;         // 1-5
    bool isComplete;
    time_t created_at;
    time_t updated_at;
} ToDo;

// Create a new ToDo item
ToDo* createToDo(const char *description, int priority);
// Free a ToDo item
void freeToDo(ToDo *todo);
// Convert ToDo item to JSON object
cJSON *toDoToJSON(const ToDo *todo);
// Parse JSON object into ToDo item
ToDo *toDoFromJson(const cJSON *json);
// Convert array of ToDo items to JSON string
int saveToDoList(ToDo **items, size_t count, const char *path);
// Load JSON from file
ToDo **loadToDoListFromJSONFile(const char *path, size_t *out_count);
void printToDo(const ToDo *todo);
void printJson(const cJSON *json);
void addTodotolist(ToDo ***items, size_t *count, ToDo *newTodo);
// todo.h (Corrected Prototype)
void printToDoList(ToDo **items, size_t count);
// Make sure the signature matches your implementation exactly:
void convertToDoListToJsonArray(ToDo **items, size_t count, cJSON **out_json_ptr);
bool markToDoAsComplete(int id, ToDo **items, size_t count);
void printJsonList(cJSON *jsonArray);
bool fileExists(const char *filename);
void createFile(const char *filename);
bool deleteToDoById(int id, ToDo ***items, size_t *count);


#endif // TODO_H