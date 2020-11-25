#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int count_files(char *dirname){
    DIR *d;
    d = opendir(dirname);
    int counter = 0;
    struct dirent *file;
    if (d)    {
        file = readdir(d);
        while (file != NULL)        {
            int c1 = strcmp(".", file->d_name);
            int c2 = strcmp("..", file->d_name);
            if (c1 != 0 && c2 != 0)            {
                counter++;
                char *prepend = strcpy(prepend, dirname);
                strcat(prepend, "/");
                strcat(prepend, file->d_name);
                printf("%s\n", prepend);
            }
            file = readdir(d);
        }
        closedir(d);
    }
    return counter;
};

int main(int argc, char **argv){
    printf("Number of files: %d\n", count_files(argv[1]));
    return EXIT_SUCCESS;
}