//
// Created by Sebastian Hirnschall on 01.11.18.
//

#include "solve.h"
#include "resize.h"
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "io.h"

#define DEFAULT_SIZE 20 //default vector length

double x;

double solve(char *calc, int calcc) {
    //vectors to store numbers and arithmetic operations
    //naming:
    //  *ptr  ... vector
    //   ptrc ... length of vector
    //   ptri ... index of last element in vector
    int *power = malloc(DEFAULT_SIZE * sizeof(int));
    int powerc = DEFAULT_SIZE;
    int poweri = -1;

    int *mult = malloc(DEFAULT_SIZE * sizeof(int));
    int multc = DEFAULT_SIZE;
    int multi = -1;

    int *add = malloc(DEFAULT_SIZE * sizeof(int));
    int addc = DEFAULT_SIZE;
    int addi = -1;

    int *minus = malloc(DEFAULT_SIZE * sizeof(int));    //for multiple - in a row to support pow
    int minusc = DEFAULT_SIZE;
    int minusi = -1;

    double *numbers = malloc(DEFAULT_SIZE * sizeof(double));
    int numbersc = DEFAULT_SIZE;
    int numbersi = -1;

    char *tmp = malloc(DEFAULT_SIZE * sizeof(char));
    int tmpc = DEFAULT_SIZE;
    int tmpi = -1;

    //for loops
    int i, j, k, l, type = 0; // type 0=default, -1= text, 1=number

    // result to return
    double result;



    //parse calc from right to left to accommodate for adding a negative number
    for (i = calcc - 1; i >= 0; --i) {
        //if calc[i] is number or . add it to tmp for conversion to double
        if ((calc[i] < 58 && calc[i] > 47) || calc[i] == 46) {
            if (type == -1)
                return 0; //error mixed numbers and text
            tmpc *= resizeString(&tmp, tmpc, tmpi);
            tmp[++tmpi] = calc[i];
            type = 1;
        }//if calc[i] is a...z add to tmp
        else if (calc[i] > 96 && calc[i] < 123) {
            if (type == 1)
                return 0; //error mixed numbers and text
            tmpc *= resizeString(&tmp, tmpc, tmpi);
            tmp[++tmpi] = calc[i];
            type = -1;
        }
        else {
            //if the tmp array is not empty but the current
            //char is no number convert tmp to double and reset it
            if (tmpi >= 0) {
                tmp[tmpi + 1] = '\0';
                numbersc *= resizeDouble(&numbers, numbersc, numbersi);
                reverse(tmp, tmpi);
                if (type == 1) {
                    double test = atof(tmp);
                    numbers[++numbersi] = atof(tmp);
                }
                else if (type == -1) {
                    if (startsWith(tmp, "x") == 1) // tmp = x
                    {
                        numbers[++numbersi] = x;
                    }
                    else if (startsWith(tmp, "sin")) {
                        numbers[numbersi] = sin(numbers[numbersi]);
                        // when () are used it is replaces with the result before sin() is called
                    }
                }
                type = 0;
                tmpi = -1;
            }

            switch (calc[i]) {
                case '^': // ^
                    powerc *= resizeInt(&power, powerc, poweri);
                    power[++poweri] = numbersi;
                    break;
                case 45: // - mult last number with (-1) and do case 43 (+)
                    if (numbers[numbersi] >= 0)
                        numbers[numbersi] *= -1;
                    else {
                        minusc *= resizeInt(&minus, minusc, minusi);  //save and * with minus one later
                        minus[++minusi] = addi + 1;
                    }
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
                    l = 0; //number of ) before mathing (
                    for (j = i; j >= 0; --j) {
                        if (calc[j] == ')')
                            ++l;
                        else if (calc[j] == 40) {
                            if (--l == 0) {  //check to see if the ( found is the right one
                                for (k = j + 1; k < i; ++k) {
                                    tmpc *= resizeString(&tmp, tmpc, tmpi);
                                    tmp[++tmpi] = calc[k];
                                }
                                tmp[tmpi + 1] = '\0';
                                numbersc *= resizeDouble(&numbers, numbersc, numbersi);
                                numbers[++numbersi] = solve(tmp, tmpi + 1);
                                tmpi = -1;
                                i = j + 1;
                                break; //quit loop
                            }
                        }
                    }
                    //skip rest of (...)
                    i -= tmpi + 2;
                    tmpi = -1;
                    break;
                case 44:    // ignore ,
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
        if (type == 1) {
            numbers[++numbersi] = atof(tmp);
        }
        else if (type == -1) {
            if (startsWith(tmp, "x") == 1) // tmp = x
            {
                numbers[++numbersi] = x;
            }
            else if (startsWith(tmp, "sin")) {
                numbers[numbersi] = sin(numbers[numbersi]);
                // when () are used it is replaces with the result before sin() is called
            }
        }
    }


    //calculate result from left to right. pow before mult before add
    //this is somewhat complicated since we parsed the string from right to left
    //so all indices get smaller from left to right and the power/mult/add vector stores the value of the next
    //(right) number
    //we store each result inplace of the right number. the left one stays as it is
    for (i = poweri; i >= 0; --i) {
        double complex ctmp = cpow(numbers[power[i] + 1], numbers[power[i]]);

        if (fabs(cimag(ctmp)) > 10e-7) //check if ctmp is a complex number
            return NAN;
        else
            numbers[power[i]] = creal(ctmp);
    }
    for (i = multi; i >= 0; --i) {
        k = 0; // k != 0 <=> next op is pow
        //check if pow was done first and result is not where it should be
        for (j = poweri; j >= 0; --j) {
            if (power[j] == mult[i] - 1) // next op is pow
            {
                k = 1;
            }
            else if (k > 0 && power[j] == mult[i] - 1 - k) {
                ++k;
            }
            else if (k > 0 && power[j] != mult[i] - 1 - k) {
                break;
            }
        }
        if (k > 0) {
            numbers[power[j + 1]] *= numbers[mult[i] + 1];
        }
        else {
            numbers[mult[i]] *= numbers[mult[i] + 1];
        }
    }
    for (i = addi; i >= 0; --i) {
        //check if there is a minus left:
        int neg = 0;
        for (j = 0; j <= minusi; ++j) {
            if (minus[j] == i) {
                neg = 1;
                break;
            }
        }
        if (numbersi >= add[i] + 1 && i > 0 && add[i - 1] != add[i] - 1) // next is *
        {   //since * was done first and the result is always stored in the number to the right of the operation
            //the number to the right of this + is not the correct result of the * it should be so we have to find
            //the correct result and work with it like normal.
            //the correct number is left of the next +
            if (neg)
                numbers[add[i - 1] + 1] *= -1;
            numbers[add[i - 1] + 1] += numbers[add[i] + 1];
        }
        else if (numbersi >= add[i] + 1 && i == 0) {
            // if the current + is the last one the number to the right is either num[0]
            // or the correct value from * is stored in num[0]
            if (neg)
                numbers[0] *= -1;
            numbers[0] += numbers[add[i] + 1];
        }
        else if (numbersi >= add[i] + 1) {   // nothing special just add the two numbers around the +
            if (neg)
                numbers[add[i]] *= -1;
            numbers[add[i]] += numbers[add[i] + 1];
        }
        else if (neg)
            numbers[0] *= -1;
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