/******************************************************************************
 * File: NK4192Lab1Part1.c
 * Author: Kili
 * Created on: 09/02/2021
 *
 * UTA Student Name: Nebojsa Kilibarda
 * UTA ID: 1001934192
******************************************************************************/

#include <stdio.h>
/*
    Testing string output and arithmetic
*/
int main(int argc, char** argv)
{
    printf("Testing string output and arithmetic with negative numbers\n");
    printf("%d\n", 12);
    printf("%d\n", -6);
    printf("%d - %d\n", 12, -6);
    printf("%d\n",12- -6);
    printf("Testing more output and arithmetic\n");
    printf("12 + 3 = \n");
    printf("%d\n", 12 + 3);
    printf("12 + 3 = ");
    printf("%d\n", 12 + 3);
    printf("12 + 3 = \t");
    printf("%d\n", 12 + 3);
    printf("12.0 + 3.0 = \n");
    printf("%f\n", 12.0 + 3.0);
    printf("12 + 3 = ");
    printf("%d", 12 + 3);
    printf("%f\n", 12.0 + 3.0);
    printf("\n");
    printf("Mathematically 12 + 3 = %d and %f\n", (12+3), (12.0+3.0));
    
    return 0;
}







