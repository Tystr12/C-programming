#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h> // For stat() to check if it's a directory

// Function to search for a file
void find_file(const char *target_filename, const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat st;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &st) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(st.st_mode)) { // If it's a directory, search recursively
            find_file(target_filename, full_path);
        } else if (strcmp(entry->d_name, target_filename) == 0) { // If it's a file and matches
            printf("Found: %s\n", full_path);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    const char *filename_to_find = argv[1];
    const char *start_path = "."; // Search in current directory and subdirectories

    printf("Searching for '%s' starting from '%s'\n", filename_to_find, start_path);
    find_file(filename_to_find, start_path);

    return 0;
}