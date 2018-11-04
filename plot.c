//
// Created by Sebastian Hirnschall on 02.11.18.
//

#include "plot.h"

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "resize.h"
#include "solve.h"

#define DEFAULT_SIZE 20 //default vector length

#define WIDTH 100
#define HEIGHT 30
#define Y_INTERVALL 5
#define X_INTERVALL 20


extern double x;

int plot(char *input, int start) {
    // parse input
    int i, j, k, argc = 0;
    double min = -10, max = 10, ymin = 9999, ymax = -9999, yIntervall, intervall;
    double y[WIDTH + 1];
    char tmp[20];
    int tmpi = -1;
    char *calc = malloc(DEFAULT_SIZE * sizeof(char));
    int calcc = DEFAULT_SIZE;
    int calci = -1;
    for (i = start; i < strlen(input); ++i) {
        if (argc == 0 && input[i] == ',') {
            calc[++calci] = '\0';
            ++argc;
        }
        else if (argc == 0) {
            calcc *= resizeString(&calc, calcc, calci);
            calc[++calci] = input[i];
        }
        else if (argc == 1 && input[i] == ':') {
            ++argc;
            tmp[++tmpi] = '\0';
            min = atof(tmp);
            tmpi = -1;
        }
        else if (argc == 1) {
            tmp[++tmpi] = input[i];
        }
        else if (argc == 2 && input[i] == ')') {
            tmp[++tmpi] = '\0';
            max = atof(tmp);
            break;
        }
        else if (argc == 2) {
            tmp[++tmpi] = input[i];
        }
    }

    intervall = (max - min) / (WIDTH);

    for (i = 0; i <= WIDTH; ++i) {
        x = min + i * intervall;
        y[i] = solve(calc, (int) strlen(calc));
    }

    for (i = 0; i <= WIDTH; ++i) {
        if (y[i] <= ymin)
            ymin = y[i];
        if (y[i] >= ymax)
            ymax = y[i];
    }
    if (ymax == ymin) {
        ymax = fabs(ymax) * 2;
        ymin = fabs(ymin) * -2;
        yIntervall = (ymax - ymin) / (HEIGHT);
    }
    else {
        yIntervall = (ymax - ymin) / (HEIGHT);
    }

    printf("y-intervall: %f\nx-intervall: %f\n", yIntervall * Y_INTERVALL, intervall * X_INTERVALL);


    for (i = 0; i <= HEIGHT; ++i) {
        for (j = 0; j <= WIDTH; ++j) {
            if (y[j] >= ymax - (i + 0.5) * yIntervall && y[j] <= ymax - (i - 0.5) * yIntervall) {
                //current point corresponds to a value in vector y
                printf("\x1b[34m*\x1b[0m");    //print * for now in blue color

            }
            else if (j == 0 || j == WIDTH) {            // draw vertical axes - y    // draw mark every 5 rows
                if (i % Y_INTERVALL == 0)
                    wprintf(L"%lc", 0x253C);
                else
                    wprintf(L"%lc", 0x250A);    //draw normal y axes
            }
            else if (i == 0 || i == HEIGHT) {           // draw horizontal axes - x
                if (j % X_INTERVALL == 0)
                    wprintf(L"%lc", 0x253C);    // draw mark at x axes
                else
                    wprintf(L"%lc", 0x2508);    // draw normal x axes
            }
            else if (j % X_INTERVALL == 0 && i % Y_INTERVALL == 0) // draw gray grid
                wprintf(L"%lc", 0x253C);
            else if (j % X_INTERVALL == 0)
                wprintf(L"%lc", 0x250A);
            else if (i % Y_INTERVALL == 0)
                wprintf(L"%lc", 0x2508);
            else
                printf(" ");

            if (i % Y_INTERVALL == 0 && j == WIDTH) // numbers for y axis
                wprintf(L"%.2f", ymax - i * yIntervall);

        }
        printf("\n");
    }
    free(calc);
    return 0;
}