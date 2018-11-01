//
// Created by Sebastian Hirnschall on 01.11.18.
//

#include "solve.h"

#include <stdlib.h>

#define DEFAULT_SIZE 20 //default vector length

int *mult = NULL;
int multc = DEFAULT_SIZE;
int *add = NULL;
int addc = DEFAULT_SIZE;

double solve(char *calc) {
    //if vectors are empty malloc
    if (!mult)
        mult = malloc(DEFAULT_SIZE * sizeof(int));
    if (!add)
        add = malloc(DEFAULT_SIZE * sizeof(int));

    //if vectors are longer than DEFAULT_SIZE realloc
    if (multc > DEFAULT_SIZE) {
        realloc(mult, DEFAULT_SIZE * sizeof(int));
        multc = DEFAULT_SIZE;
    }
    if (addc > DEFAULT_SIZE) {
        realloc(add, DEFAULT_SIZE * sizeof(int));
        addc = DEFAULT_SIZE;
    }
}

