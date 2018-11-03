#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "io.h"
#include "solve.h"
#include "plot.h"

//for testing
#include <math.h>


int main(int argc, char *argv[]) {
    char *input, prompt[3];
    int i;
    snprintf(prompt, sizeof(prompt), "> ");
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

        if (!strcmp(input, "clear"))
            clear();
        else if (!strcmp(input, "exit"))
            return 0;
        else if (!strcmp(input, "help"))
            help();
        else if (!strcmp(input, "plot")) {
            //for testing
            double y[100];
            for (i = 0; i < 100; ++i) {
                double x = (double) (i - 50) / 10;
                y[i] = sin(x);
            }
            plot(NULL, y, 100);
        }
        else
            printf(" =%f\n", solve(input, (int) strlen(input)));
        free(input);
    }
    return 0;
}
