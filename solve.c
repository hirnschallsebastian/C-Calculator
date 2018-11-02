//
// Created by Sebastian Hirnschall on 01.11.18.
//

#include "solve.h"
#include "resize.h"
#include <stdlib.h>

#define DEFAULT_SIZE 20 //default vector length

double solve(char *calc, int calcc) {
    //vectors to store numbers and arithmetic operations
    //naming:
    //  *ptr  ... vector
    //   ptrc ... length of vector
    //   ptri ... index of last element in vector
    int *mult = malloc(DEFAULT_SIZE * sizeof(int));
    int multc = DEFAULT_SIZE;
    int multi = -1;
    int *add = malloc(DEFAULT_SIZE * sizeof(int));
    int addc = DEFAULT_SIZE;
    int addi = -1;
    double *numbers = malloc(DEFAULT_SIZE * sizeof(double));
    int numbersc = DEFAULT_SIZE;
    int numbersi = -1;
    char *tmp = malloc(DEFAULT_SIZE * sizeof(char));
    int tmpc = DEFAULT_SIZE;
    int tmpi = -1;
    //for loops
    int i, j, k;
    // result to return
    double result;

    //parse calc from right to left to accommodate for adding a negative number
    for (i = calcc - 1; i >= 0; --i) {
        //if calc[i] is number or . add it to tmp for conversion to double
        if ((calc[i] < 58 && calc[i] > 47) || calc[i] == 46) {
            tmpc *= resizeString(&tmp, tmpc, tmpi);
            tmp[++tmpi] = calc[i];
        } else {
            //if the tmp array is not empty but the current
            //char is no number convert tmp to double and reset it
            if (tmpi >= 0) {
                tmp[tmpi + 1] = '\0';
                numbersc *= resizeDouble(&numbers, numbersc, numbersi);
                reverse(tmp, tmpi);
                numbers[++numbersi] = atof(tmp);
                tmpi = -1;
            }

            switch (calc[i]) {
                case 45: // - mult last number with (-1) and do case 43 (+)
                    numbers[numbersi] *= -1;
                case 43: // + add current number index to add vector
                    addc *= resizeInt(&add, addc, addi);
                    add[++addi] = numbersi;
                    break;
                case 47: // / replace last number with 1/number and do case 42 (*)
                    numbers[numbersi] = 1 / numbers[numbersi];
                case 42:
                    multc *= resizeInt(&mult, multc, multi);
                    mult[++multi] = numbersi;
                    break;
                case 41:    // )
                    // find matching ( and call solve function for (...)
                    for (j = 0; j < i; ++j) {
                        if (calc[j] == 40) {
                            for (k = j + 1; k < i; ++k) {
                                tmpc *= resizeString(&tmp, tmpc, tmpi);
                                tmp[++tmpi] = calc[k];
                            }
                            numbersc *= resizeDouble(&numbers, numbersc, numbersi);
                            numbers[++numbersi] = solve(tmp, tmpi + 1);

                            break; //quit loop
                        }
                    }
                    //skip rest of (...)
                    i -= tmpi + 2;
                    tmpi = -1;
                    break;
                case 40:    // ignore (
                case 32:    // ignore space
                    break;
                default:
                    return 0; // when the current char is nor supported return 0
            }
        }
    }
    //convert current tmp to number at the end of calc
    if (tmpi >= 0) {
        tmp[tmpi + 1] = '\0';
        numbersc *= resizeDouble(&numbers, numbersc, numbersi);
        reverse(tmp, tmpi);
        numbers[++numbersi] = atof(tmp);
    }


    //calculate result from left to right. mult before add
    //this is somewhat complicated since we parsed the string from right to left
    //so all indices get smaller from left to right and the mult/add vector stores the value of the next
    //(right) number
    //we store each result inplace of the right number. the left one stays as it is
    for (i = multi; i >= 0; --i) {
        numbers[mult[i]] *= numbers[mult[i] + 1];
    }
    for (i = addi; i >= 0; --i) {
        if (i > 0 && add[i - 1] != add[i] - 1) // next is *
        {   //since * was done first and the result is always stored in the number to the right of the operation
            //the number to the right of this + is not the correct result of the * it should be so we have to find
            //the correct result and work with it like normal.
            //the correct number is left of the next +
            numbers[add[i - 1] + 1] += numbers[add[i] + 1];
        }
        else if (i == 0) {
            // if the current + is the last one the number to the right is either num[0]
            // or the correct value from * is stored in num[0]
            numbers[0] += numbers[add[i] - 1];
        }
        else {   // nothing special just add the two numbers around the +
            numbers[add[i]] += numbers[add[i] + 1];
        }
    }

    result = numbers[0];

    //free allocated memory
    free(mult);
    free(add);
    free(numbers);
    free(tmp);
    return result;
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