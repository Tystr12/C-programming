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

/* JSON (de)serialization */
cJSON *toDoToJSON(const ToDo *todo);
ToDo *toDoFromJson(const cJSON *json);

/* Convert full todo list to/from JSON string (caller frees returned char*) */
char *toDoListToString(ToDo **todos, size_t count);
ToDo **toDoListFromJsonString(const char *json, size_t *out_count);

/* File IO */
int saveToDoList(ToDo **items, size_t count, const char *path);
ToDo **loadToDoList(const char *path, size_t *out_count);

/* Memory helpers */
void freeToDo(ToDo *todo);
void free_todo_list(ToDo **todos, size_t count);

#endif // TODO_H