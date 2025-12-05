#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int fileExists(const char *filepath) 
{
    struct stat buffer;
    return (stat(filepath, &buffer) == 0); // 0 on success, -1 on failure
}


int main(void) 
{
    // WITH POINTERS

    char *filename = malloc(256);
    char *directory = malloc(512);
    if (!filename || !directory) {
        fprintf(stderr, "Allocation failed\n");
        free(filename);
        free(directory);
        return 1;
    }

    printf("Enter the directory you want to search: \n");
    scanf("%511s", directory);

    printf("Enter the filename you wish to find: \n");
    scanf("%255s", filename);

    char fullPath[1024];
    snprintf(fullPath, sizeof(fullPath), "%s%s", directory, filename);

    if (fileExists(fullPath))
    {
        printf("File '%s' exists in '%s'\n", filename, directory);
    }
    else {
        printf("File '%s' does NOT exist in '%s'\n", filename, directory);
    }

    free(filename);
    free(directory);

    // WITHOUT POINTERS

    char file[256];
    char dir[512];

    printf("Enter the directory you want to search: \n");
    scanf("%511s", dir);

    printf("Enter the filename you wish to find: \n");
    scanf("%255s", file);

    char fPath[1024];
    snprintf(fPath, sizeof(fPath), "%s%s", dir, file);

    if (fileExists(fPath))
    {
        printf("File '%s' exists in '%s'\n", file, dir);
    }
    else {
        printf("File '%s' does NOT exist in '%s'\n", file, dir);
    }

    return 0;

}