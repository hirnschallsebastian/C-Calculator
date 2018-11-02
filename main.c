#include <stdio.h>
#include <string.h>

#include "io.h"
#include "solve.h"

#define MAX_CALC_LENGTH 200

int main() {
    char calc[MAX_CALC_LENGTH];

    while (1) {
        scanf(" %[^\n]s", calc); //scan with whitespaces
        if (!strcmp(calc, "clear"))
            clear();
        else if (!strcmp(calc, "exit"))
            return 0;
        else
            printf("=%f\n", solve(calc, (int) strlen(calc)));
    }
    return 0;
}
