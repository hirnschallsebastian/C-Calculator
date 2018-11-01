#include <stdio.h>
#include <string.h>

#include "solve.h"

#define MAX_CALC_LENGTH 200

int main() {
    char calc[200];

    while (1) {
        scanf(" %[^\n]s", calc);
        printf("=%f\n", solve(calc, (int) strlen(calc)));
    }
    return 0;
}