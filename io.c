//
// Created by Sebastian Hirnschall on 02.11.18.
//
#include <stdlib.h>
#include <stdio.h>

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