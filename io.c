//
// Created by Sebastian Hirnschall on 02.11.18.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void clear() {
    //clear the screen
    //needs to be adjusted depending on os
    system("clear");
}

void help() {
    printf("C-Calculator v1\n"
           "Written by Sebastian Hirnschall 2018\n"
           "Contact - sebastian@hirnschall.net\n\n"
           "Usage: ./ccalc <options>\n\n"
           "Options:\n"
           "-h\t\tshow this screen\n"
           "-s <calc>\tprint result of calculation and exit\n");
}

int startsWith(char *input, char *start) {
    int i, j = 0, len = (int) strlen(start);

    for (i = 0; i < (int) strlen(input); ++i) {
        if (input[i] == ' ')
            ++j;
        else if (i - j == len)
            return i; //when we reach this point input starts with start
        else if (input[i] != start[i - j])
            return 0;   //the chars do not match => input does not start with start
    }
    //loop ended without return => input = start
    return 1;
}