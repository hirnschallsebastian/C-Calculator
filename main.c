#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "io.h"
#include "solve.h"


int main(int argc, char *argv[]) {
    char *input, prompt[3];

    snprintf(prompt, sizeof(prompt), "> ");
    using_history();

    while (1) {
        input = readline(prompt);
        if (!input)
            continue;
        add_history(input);

        if (!strcmp(input, "clear"))
            clear();
        else if (!strcmp(input, "exit"))
            return 0;
        else
            printf(" =%f\n", solve(input, (int) strlen(input)));
        free(input);
    }
    return 0;
}
