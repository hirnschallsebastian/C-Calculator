#include <stdio.h>
#include <string.h>

#include "solve.h"

#define MAX_CALC_LENGTH 200

int main() {
    char calc[200];

    scanf("%s", calc);
    printf("=%f", solve(calc, strlen(calc)));

    return 0;
}