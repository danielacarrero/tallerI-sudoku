#include <stdio.h>
#include <string.h>
#include "utils.h"


void split(const char *string, char delim) {
    char *ptr;

    ptr = strtok(string, delim);

    while(ptr != NULL) {
        printf("'%s'\n", ptr);
        ptr = strtok(NULL, delim);
    }
}