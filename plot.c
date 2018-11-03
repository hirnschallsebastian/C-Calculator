//
// Created by Sebastian Hirnschall on 02.11.18.
//

#include "plot.h"

#include <stdio.h>
#include <wchar.h>

#define WIDTH 100
#define HEIGHT 30
#define Y_INTERVALL 3
#define X_INTERVALL 10

int plot(double *x, double *y, int len) {
    //wprintf(L"\n\n%lc",0x250C);
    //wprintf(L"%lc",0x2500);
    //wprintf(L"%lc\n",0x2510);

    //wprintf(L"%lc ",0x2502);
    //wprintf(L"%lc\n",0x2502);

    //wprintf(L"%lc",0x2514);
    //wprintf(L"%lc",0x2500);
    //wprintf(L"%lc\n\n",0x2518);

    //todo: interpolate the input arrays if too small. use x with length 100 for now

    int i, j, k;
    double min = 99999, max = -99999, yIntervall;
    //find max y for scaling axes

    for (i = 0; i < len; ++i) {
        if (y[i] <= min)
            min = y[i];
        if (y[i] >= max)
            max = y[i];
    }

    yIntervall = (max - min) / HEIGHT;


    int lastJ = -WIDTH / 2;
    for (i = HEIGHT / 2; i >= -HEIGHT / 2; --i) {
        for (j = -WIDTH / 2; j < WIDTH / 2; ++j) {
            if (y[j + WIDTH / 2] <= (i + 0.5) * yIntervall && y[j + WIDTH / 2] >= (i - 0.5) * yIntervall) {
                //current point corresponds to a value in vector y
                printf("\x1b[34m*\x1b[0m");    //print * for now in blue color

            }
            else if (i == 0 && j == 0)      // cross at origin
                wprintf(L"%lc", 0x254B);
            else if (j == 0) {            // draw vertical axes - y
                if (i % Y_INTERVALL == 0)
                    wprintf(L"%lc", 0x2524);    // draw mark every 3 rows
                else
                    wprintf(L"%lc", 0x250A);    //draw normal y axes
            }
            else if (i == 0) {           // draw horizontal axes - x
                if (j % X_INTERVALL == 0)
                    wprintf(L"%lc", 0x252C);    // draw mark at x axes
                else
                    wprintf(L"%lc", 0x2508);    // draw normal x axes
            }
            else
                printf(" ");


        }
        printf("\n");
    }
}