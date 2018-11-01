//
// Created by Sebastian Hirnschall on 01.11.18.
//

#include "solve.h"

#include <stdlib.h>

#define DEFAULT_SIZE 20 //default vector length

double solve(char *calc, int calcc) {
    //vectors to store numbers and arithmetic operations
    int *mult = malloc(DEFAULT_SIZE * sizeof(int));
    int multc = DEFAULT_SIZE;
    int multi = -1;
    int *add = malloc(DEFAULT_SIZE * sizeof(int));
    int addc = DEFAULT_SIZE;
    int addi = -1;
    double *numbers = malloc(DEFAULT_SIZE * sizeof(double));
    int numbersc = DEFAULT_SIZE;
    int numbersi = -1;  //index of last element in vector
    char *tmp = malloc(DEFAULT_SIZE * sizeof(char));
    int tmpc = DEFAULT_SIZE;
    int tmpi = -1;

    int i, j, k;



    //parse calc from right to left to accommodate for adding a negative number
    for (i = calcc - 1; i >= 0; --i) {
        //if calc[i] is number or . add it to tmp for conversion to double
        if ((calc[i] < 58 && calc[i] > 47) || calc[i] == 46) {
            tmpc *= resizeString(tmp, tmpc, tmpi);
            tmp[++tmpi] = calc[i];
        } else {
            //if the tmp array is not empty but the current
            //char is no number convert tmp to double and reset it
            if (tmpi >= 0) {
                tmp[tmpi + 1] = '\0';
                numbersc *= resizeDouble(numbers, numbersc, numbersi);
                reverse(tmp, tmpi);
                numbers[++numbersi] = atof(tmp);
                tmpi = -1;
            }

            switch (calc[i]) {
                case 45: // - mult last number with (-1) and do case 43 (+)
                    numbers[numbersi] *= -1;
                case 43: // + add current number index to add vector
                    addc *= resizeInt(add, addc, addi);
                    add[++addi] = numbersi;
                    break;
                case 47: // / replace last number with 1/number and do case 42 (*)
                    numbers[numbersi] = 1 / numbers[numbersi];
                case 42:
                    multc *= resizeInt(mult, multc, multi);
                    mult[++multi] = numbersi;
                    break;
                case 41:    // )
                    // find matching ( and call solve function for (...)
                    for (j = 0; j < i; ++j) {
                        if (calc[j] == 40) {
                            for (k = j + 1; k < i; ++k) {
                                tmpc *= resizeString(tmp, tmpc, tmpi);
                                tmp[++tmpi] = calc[k];
                            }
                            numbersc *= resizeDouble(numbers, numbersc, numbersi);
                            numbers[++numbersi] = solve(tmp, tmpi);

                            break; //quit loop
                        }
                    }
                    break;
                case 40:    // (
                    break;
                default:
                    return 0; // when the current char is nor supported return 0
            }
        }


    }
    if (tmpi >= 0) {
        tmp[tmpi + 1] = '\0';
        numbersc *= resizeDouble(numbers, numbersc, numbersi);
        reverse(tmp, tmpi);
        numbers[++numbersi] = atof(tmp);
    } else {
        return 0; // return 0 when calc ends with arithmetic operation
    }


    //free allocated memory
    free(mult);
    free(add);
    free(numbers);
    free(tmp);

    return 0;
}

void reverse(char *str, int len) {
    int i;
    char tmp;
    for (i = 0; i < (len + 1) / 2; ++i) {
        tmp = str[i];
        str[i] = str[len - i];
        str[len - i] = tmp;
    }
}


int resizeInt(int *ptr, int ptrc, int ptri) {
    //if ptr is too small double its size
    if (ptri == ptrc - 1) {
        if (!realloc(ptr, 2 * ptrc * sizeof(int))) //double tmp size
            return 0;
        return 2;
    }
    return 1;
}

int resizeDouble(double *ptr, int ptrc, int ptri) {
    //if ptr is too small double its size
    if (ptri == ptrc - 1) {
        if (!realloc(ptr, 2 * ptrc * sizeof(double))) //double tmp size
            return 0;
        return 2;
    }
    return 1;
}

int resizeString(char *ptr, int ptrc, int ptri) {
    //if ptr is too small double its size
    if (ptri == ptrc - 2) { //-2 to add '\0' to char array
        if (!realloc(ptr, 2 * ptrc * sizeof(char))) //double tmp size
            return 0;
        return 2;
    }
    return 1;
}