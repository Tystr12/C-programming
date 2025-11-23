// todo_json.c 

#include "todo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cJSON.h"
#include <time.h>
#include <stdbool.h>


void freeToDo(ToDo *todo) {
    if (todo) {
        free(todo->description);
        free(todo);
    }
}


cJSON *toDoToJSON(const ToDo *todo) {
    if (!todo) return NULL;

    cJSON *json = cJSON_CreateObject();
    if (!json) return NULL;

    cJSON_AddNumberToObject(json, "id", todo->id);
    cJSON_AddStringToObject(json, "description", todo->description);
    cJSON_AddNumberToObject(json, "priority", todo->priority);
    cJSON_AddBoolToObject(json, "isComplete", todo->isComplete);
    cJSON_AddNumberToObject(json, "created_at", (double)todo->created_at);
    cJSON_AddNumberToObject(json, "updated_at", (double)todo->updated_at);

    return json;
}

ToDo *toDoFromJson(const cJSON *json) {
    if (!json) return NULL;

    ToDo *todo = malloc(sizeof(ToDo));
    if (!todo) return NULL;

    cJSON *idItem = cJSON_GetObjectItemCaseSensitive(json, "id");
    cJSON *descItem = cJSON_GetObjectItemCaseSensitive(json, "description");
    cJSON *priorityItem = cJSON_GetObjectItemCaseSensitive(json, "priority");
    cJSON *isCompleteItem = cJSON_GetObjectItemCaseSensitive(json, "isComplete");
    cJSON *createdAtItem = cJSON_GetObjectItemCaseSensitive(json, "created_at");
    cJSON *updatedAtItem = cJSON_GetObjectItemCaseSensitive(json, "updated_at");

    if (cJSON_IsNumber(idItem)) todo->id = idItem->valueint;
    if (cJSON_IsString(descItem) && (descItem->valuestring != NULL)) {
        todo->description = strdup(descItem->valuestring);
    } else {
        todo->description = strdup("");
    }
    if (cJSON_IsNumber(priorityItem)) todo->priority = priorityItem->valueint;
    if (cJSON_IsBool(isCompleteItem)) todo->isComplete = cJSON_IsTrue(isCompleteItem);
    if (cJSON_IsNumber(createdAtItem)) todo->created_at = (time_t)createdAtItem->valuedouble;
    if (cJSON_IsNumber(updatedAtItem)) todo->updated_at = (time_t)updatedAtItem->valuedouble;

    return todo;
}

char *toDoListToString(const ToDo **todos, int count) {
    cJSON *jsonArray = cJSON_CreateArray();
    if (!jsonArray) return NULL;

    for (int i = 0; i < count; i++) {
        cJSON *todoJson = toDoToJSON(todos[i]);
        if (todoJson) {
            cJSON_AddItemToArray(jsonArray, todoJson);
        }
    }

    char *jsonString = cJSON_PrintUnformatted(jsonArray);
    cJSON_Delete(jsonArray);
    return jsonString;
}

// Parse JSON string into heap array of ToDo* (caller must free each and array)
ToDo **toDoListFromJsonString(const char *json, size_t *out_count) {
    if (!json) { *out_count = 0; return NULL; }
    cJSON *arr = cJSON_Parse(json);
    if (!arr || !cJSON_IsArray(arr)) { if (arr) cJSON_Delete(arr); *out_count = 0; return NULL; }

    size_t n = cJSON_GetArraySize(arr);
    ToDo **list = calloc(n, sizeof(ToDo*));
    if (!list) { cJSON_Delete(arr); *out_count=0; return NULL; }

    size_t idx = 0;
    cJSON *it = NULL;
    cJSON_ArrayForEach(it, arr) {
        ToDo *t = todo_from_json(it);
        list[idx++] = t;
    }
    cJSON_Delete(arr);
    *out_count = idx;
    return list;
}

int saveToDoList(ToDo **items, size_t count, const char *path) {
    char *json = todo_list_to_json_string(items, count);
    if (!json) return -1;
    char tmp[1024];
    snprintf(tmp, sizeof(tmp), "%s.tmp", path);
    FILE *f = fopen(tmp, "wb");
    if (!f) { free(json); return -2; }
    size_t written = fwrite(json, 1, strlen(json), f);
    fclose(f);
    free(json);
    if (written == 0) return -3;
    if (rename(tmp, path) != 0) return -4;
    return 0;
}

ToDo **loadToDoList(const char *path, size_t *out_count) {
    FILE *f = fopen(path, "rb");
    if (!f) { *out_count = 0; return NULL; }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (sz <= 0) { fclose(f); *out_count=0; return NULL; }

    char *buf = malloc(sz + 1);
    if (!buf) { fclose(f); *out_count=0; return NULL; }
    fread(buf, 1, sz, f);
    buf[sz] = '\0';
    fclose(f);

    ToDo **list = todo_list_from_json_string(buf, out_count);
    free(buf);
    return list;
}