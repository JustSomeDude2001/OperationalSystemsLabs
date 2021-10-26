#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string.h>     
#include <memory.h>

#include <dirent.h>

#define BUFFER_SIZE 4096

int main() {
    DIR *directory;

    struct dirent *directory_data;
    
    directory = opendir("./tmp");
    
    while ((directory_data = readdir(directory)) != NULL) {
        printf("%s ", directory_data -> d_name);
    }

    closedir(directory);
    return(0);
}