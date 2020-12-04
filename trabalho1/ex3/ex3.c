#include "helpers.h"

int main(int argc, char **argv){
    printf("Number of files: %d\n", count_files(argv[1]));
    return EXIT_SUCCESS;
}