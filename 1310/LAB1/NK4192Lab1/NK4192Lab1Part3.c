/******************************************************************************
 * File: NK4192Lab1Part3.c
 * Author: Kili
 * Created on: 09/11/2021
 *
 * UTA Student Name: Nebojsa Kilibarda
 * UTA ID: 1001934192
*******************************************************************************/
#include <stdio.h>

int main(int argc, char** argv)
{ //Correctly find the sum of two fractions

    int a = 3;
    int b = 4;
    int c = 1;
    int d = 2;
    
    printf("Original fractions are ");
    printf("%d/%d and %d/%d\n",a,b,c,d);
    
    int quoNum = a * d;
    int quoDenom = b * c;
    printf("The term in the numerator is ");
    printf("%d and the denominator is %d\n",quoNum, quoDenom);
    
    double fractionQuotient = (quoNum)/(double)quoDenom;
    printf("The equation for the quotient of two fractions is ");
    printf("(%d * %d)/(%d * %d) = %d/%d\n",a,d,b,c, quoNum, quoDenom);
    
    printf("The quotient of the two fractions is %f\n",fractionQuotient);
  
    return 0;
}

