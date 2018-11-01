//
// Created by Sebastian Hirnschall on 01.11.18.
//
#include <stdlib.h>
#include "resize.h"

//each function takes a pointer to a pointer(vector) and doubles its size

int resizeInt(int **ptr, int ptrc, int ptri) {
    //if ptr is too small double its size
    if (ptri == ptrc - 1) {
        *ptr = realloc(*ptr, 2 * ptrc * sizeof(int));
        if (!*ptr)
            return 0;
        return 2;
    }
    return 1;
}

int resizeDouble(double **ptr, int ptrc, int ptri) {
    //if ptr is too small double its size
    if (ptri == ptrc - 1) {
        *ptr = realloc(*ptr, 2 * ptrc * sizeof(double));
        if (!*ptr)
            return 0;
        return 2;
    }
    return 1;
}

int resizeString(char **ptr, int ptrc, int ptri) {
    //if ptr is too small double its size
    if (ptri == ptrc - 2) { //-2 to add '\0' to char array
        *ptr = realloc(*ptr, 2 * ptrc * sizeof(char));
        if (!*ptr)
            return 0;
        return 2;
    }
    return 1;
}