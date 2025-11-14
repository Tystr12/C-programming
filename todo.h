#ifndef TODO_H
#define TODO_H

typedef struct ToDo
{
    char *description;
    int priority;
    bool isComplete; 
} ToDo;

ToDo* createToDo();
void markToDoComplete(ToDo* todo);
void printToDo(ToDo* todo);
void destroyToDo(ToDo* todo);
#endif