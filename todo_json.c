// todo_json.c 

#include "todo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cJSON.h"
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

ToDo* createToDo(const char *description, int priority) 
{
    ToDo *todo = (ToDo *)malloc(sizeof(ToDo));
    if (!todo) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    todo->id = rand();  // Simple random ID generation
    todo->description = strdup(description);
    todo->priority = priority;
    todo->isComplete = false;
    todo->created_at = time(NULL);
    todo->updated_at = time(NULL);

    return todo;
}

cJSON *toDoToJSON(const ToDo *todo) 
{
    cJSON *json = cJSON_CreateObject();
    if (!json) {
        return NULL;
    }

    cJSON_AddNumberToObject(json, "id", todo->id);
    cJSON_AddStringToObject(json, "description", todo->description);
    cJSON_AddNumberToObject(json, "priority", todo->priority);
    cJSON_AddBoolToObject(json, "isComplete", todo->isComplete);
    cJSON_AddNumberToObject(json, "created_at", (double)todo->created_at);
    cJSON_AddNumberToObject(json, "updated_at", (double)todo->updated_at);

    return json;
}

ToDo *toDoFromJson(const cJSON *json) 
{
    if (!json) {
        return NULL;
    }

    ToDo *todo = (ToDo *)malloc(sizeof(ToDo));
    if (!todo) {
        return NULL;
    }

    todo->id = cJSON_GetObjectItem(json, "id")->valueint;
    const char *desc = cJSON_GetObjectItem(json, "description")->valuestring;
    todo->description = strdup(desc ? desc : "");
    todo->priority = cJSON_GetObjectItem(json, "priority")->valueint;
    todo->isComplete = cJSON_GetObjectItem(json, "isComplete")->valueint;
    todo->created_at = (time_t)cJSON_GetObjectItem(json, "created_at")->valuedouble;
    todo->updated_at = (time_t)cJSON_GetObjectItem(json, "updated_at")->valuedouble;

    return todo;
}

void freeToDo(ToDo *todo) 
{
    if (todo) {
        free(todo->description);
        free(todo);
    }
}

void printToDo(const ToDo *todo)
{
    if (!todo) return;

    printf("ID: %d\n", todo->id);
    printf("Description: %s\n", todo->description);
    printf("Priority: %d\n", todo->priority);
    printf("Completed: %s\n", todo->isComplete ? "Yes" : "No");
    printf("Created At: %s", ctime(&todo->created_at));
    printf("Updated At: %s", ctime(&todo->updated_at));
}

void printJson(const cJSON *json)
{
    if (!json) return;

    char *jsonString = cJSON_Print(json);
    if (jsonString) {
        printf("%s\n", jsonString);
        free(jsonString);
    }
}

// Notice the triple asterisk *** here
// Updated: use cJSON **out param (caller passes &jsonPtr)
void convertToDoListToJsonArray(ToDo **items, size_t count, cJSON **out_json_ptr)
{
    if (!out_json_ptr) return;
    *out_json_ptr = NULL;
    if (!items || count == 0) return;

    cJSON *jsonArray = cJSON_CreateArray();
    if (!jsonArray) return;
    
    for (size_t i = 0; i < count; i++) {
        if (!items[i]) continue;
        cJSON *todoJson = toDoToJSON(items[i]);
        if (todoJson) {
            cJSON_AddItemToArray(jsonArray, todoJson);
        }
    }

    *out_json_ptr = jsonArray;
}

void printJsonList(cJSON *jsonArray)
{
    if (!jsonArray) return;

    char *jsonString = cJSON_Print(jsonArray);
    if (jsonString) {
        printf("%s\n", jsonString);
        free(jsonString);
    }
}

void printToDoList(ToDo **items, size_t count)
{
    if (!items || count == 0) return;

    for (size_t i = 0; i < count; i++) {
        printToDo(items[i]);
        printf("--------------------\n");
    }
}

void addTodotolist(ToDo ***items, size_t *count, ToDo *newTodo)
{
    if (!items || !count || !newTodo) return;

    ToDo **temp = realloc(*items, sizeof(ToDo *) * (*count + 1));
    if (!temp) {
        printf("Memory allocation failed\n");
        return;
    }

    *items = temp;
    (*items)[*count] = newTodo;
    (*count)++;
}

int saveToDoList(ToDo **items, size_t count, const char *path)
{
    if (!path || !items || count == 0) return 0;

    cJSON *jsonArray = NULL;
    convertToDoListToJsonArray(items, count, &jsonArray);
    if (!jsonArray) return 0;

    char *jsonString = cJSON_Print(jsonArray);
    if (!jsonString) {
        cJSON_Delete(jsonArray);
        return 0;
    }

    FILE *file = fopen(path, "w");
    if (!file) {
        printf("Error opening file for writing: %s\n", path);
        free(jsonString);
        cJSON_Delete(jsonArray);
        return 0;
    }

    fprintf(file, "%s\n", jsonString);
    fclose(file);

    free(jsonString);
    cJSON_Delete(jsonArray);
    return 1;
}

ToDo **loadToDoListFromJSONFile(const char *path, size_t *out_count)
{
    if (!path || !out_count) return NULL;
    *out_count = 0;

    FILE *file = fopen(path, "r");
    if (!file) {
        printf("Error opening file for reading: %s\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fsize + 1);
    if (!buffer) {
        printf("Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, fsize, file);
    buffer[fsize] = '\0';
    fclose(file);

    cJSON *jsonArray = cJSON_Parse(buffer);
    free(buffer);
    if (!jsonArray) {
        printf("Error parsing JSON\n");
        return NULL;
    }

    size_t count = cJSON_GetArraySize(jsonArray);
    if (count == 0) {
        cJSON_Delete(jsonArray);
        return NULL;
    }

    ToDo **todoList = (ToDo **)malloc(sizeof(ToDo *) * count);
    if (!todoList) {
        printf("Memory allocation failed\n");
        cJSON_Delete(jsonArray);
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        cJSON *item = cJSON_GetArrayItem(jsonArray, i);
        if (item) {
            todoList[i] = toDoFromJson(item);
        }
    }

    *out_count = count;
    cJSON_Delete(jsonArray);
    return todoList;
}

bool fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }

    return false;

}

void createFile(const char *filename) {
    if (!fileExists(filename)) {
        FILE *file = fopen(filename, "w");
        if (file != NULL) {
            fclose(file);
        } else {
            printf("Error creating file: %s\n", filename);
        }   
    }
}

bool markToDoAsComplete(int id, ToDo **items, size_t count) {
    if (!items || count == 0) return false;

    for (size_t i = 0; i < count; i++) {
        if (items[i] && items[i]->id == id) {
            items[i]->isComplete = true;
            items[i]->updated_at = time(NULL);
            return true;
        }
    }

    return false;
}

bool deleteToDoById(int id, ToDo ***items, size_t *count) {
    if (!items || !*items || !count || *count == 0) return false;

    size_t index = SIZE_MAX;
    for (size_t i = 0; i < *count; i++) {
        if ((*items)[i] && (*items)[i]->id == id) {
            index = i;
            break;
        }
    }

    if (index == SIZE_MAX) {
        return false; // ID not found
    }

    freeToDo((*items)[index]);

    for (size_t i = index; i < *count - 1; i++) {
        (*items)[i] = (*items)[i + 1];
    }

    ToDo **temp = realloc(*items, sizeof(ToDo *) * (*count - 1));
    if (temp || *count - 1 == 0) {
        *items = temp;
        (*count)--;
        return true;
    } else {
        printf("Memory reallocation failed\n");
        return false;
    }
}

