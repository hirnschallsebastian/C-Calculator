//
// Created by Sebastian Hirnschall on 02.11.18.
//

#include "plot.h"

#include <stdio.h>
#include <wchar.h>

#define WIDTH 100
#define HEIGHT 30

int plot(double *x, double *y) {
    //wprintf(L"\n\n%lc",0x250C);
    //wprintf(L"%lc",0x2500);
    //wprintf(L"%lc\n",0x2510);

    //wprintf(L"%lc ",0x2502);
    //wprintf(L"%lc\n",0x2502);

    //wprintf(L"%lc",0x2514);
    //wprintf(L"%lc",0x2500);
    //wprintf(L"%lc\n\n",0x2518);
    int i, j;

    for (i = 0; i < HEIGHT; ++i) {
        for (j = 0; j < WIDTH; ++j) {
            if (i == HEIGHT - 3 && j == 3)
                wprintf(L"%lc", 0x254B);
            else if (j == 5 && i < HEIGHT - 3) {
                if (i % 3 == 0)
                    wprintf(L"%lc", 0x2524);
                else
                    wprintf(L"%lc", 0x250A); //y axes
            }
            else if (i == HEIGHT - 3) {
                if (j % 10 == 0)
                    wprintf(L"%lc", 0x252C);
                else
                    wprintf(L"%lc", 0x2508); //x axes
            }
            else if (i == HEIGHT - 1 && j % 10 == 0)
                printf("%d", j);
            else if (j == 0 && i % 3 == 0)
                printf("%d", HEIGHT - i);
            else
                printf(" ");


        }
        printf("\n");
    }
}