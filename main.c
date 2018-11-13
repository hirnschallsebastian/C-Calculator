#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>

#include "io.h"
#include "solve.h"
#include "plot.h"

//for testing
#include <math.h>


int findFunction(char *);

int main(int argc, char *argv[]) {
    char *input;
    int i;


    //compile with -DCOMPATIBILITY if nerdfont is not installed on your system
#ifdef COMPATIBILITY
    char prompt[3] =  "> \0";
#else
    char prompt[6] = "\uf460 \0";
#endif

    using_history();

    for (i = 1; i < argc; ++i)   //parse commandline arguments
    {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 's':
                    printf("%f", solve(argv[i + 1], (int) strlen(argv[i + 1])));
                    return 0;
                    break;
                case 'h':
                default:
                    help();
                    return 1;
                    break;
            }
        }
    }

    while (1) {

        input = readline(prompt);
        if (!input)
            continue;
        add_history(input);

        if (!findFunction(input, (int) strlen(input)))
            printf(" =%f\n", solve(input, (int) strlen(input)));

        free(input);
    }

    return 0;
}

int findFunction(char *input) {
    if (startsWith(input, "clear")) {
        clear();
        return 1;
    }
    else if (startsWith(input, "exit"))
        exit(0);
    else if (startsWith(input, "help")) {
        help();
        return 1;
    }
    else if (startsWith(input, "plot(")) {
        plot(input, startsWith(input, "plot("));
        return 1;
    }
    return 0;
}
