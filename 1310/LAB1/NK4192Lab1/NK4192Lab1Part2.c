/******************************************************************************
 * File: NK4192Lab1Part2.c
 * Author: Kili
 * Created on: 09/11/2021
 *
 * UTA Student Name: Nebojsa Kilibarda
 * UTA ID: 1001934192
*******************************************************************************/
#include <stdio.h>
/*
Assigning values to variables and performing integer and mixed division
*/
int main(int argc, char** argv) // OnlineGDB defaults to int main()
{
   int date1 = 28;   // date1,date2,date3,and date4 are variables.
   int date2;
   int date3 = 21, date4; // they hold INTeger values
   date4 = 6;
   
   printf("Printing variable values:\n"); //This prints a title for the output
   printf("date1 = %d\ndate2 = %d\n", date1, date2);
   printf("date3 = ");
   printf("%d\n",date3);
   printf("date4 = %d\n",date4);
   
   date2 = 9;
   
   printf("new value of date2 = %d\n\n",date2);
   printf("Product of date1 & date2 = %d\n",(date1 * date2));
   printf("Quotient of date1 & date2 = %d :Remember that the variables are int\n",(date1 / date2));
   printf("Remainder of date1 & date2 = %d :Remember the variables are int\n",(date1 % date2));
   printf("\n"); //prints a blank line
   printf("Giving date4 the value of date3 minus date1 so ");
   printf("%d - %d = ",date3, date1);
   
   date4 = date3 - date1;
   
   printf("%d\n",date4);
   printf("\ndate1 = %d and date2 = %d\n",date1, date2);
   date4 = date1 / date2; //Using integer variables;
   printf("\nUsing integer variables:\n\tQuotient of %d & %d = %d\n",date1, date2, date4);
   double date5 = date1 / date2; //Using floating point variables
   printf("Using int division assigned to floating point variables:\n\tQuotient of %d & %d = %f\n",date1,date2,date5);
   date5 = date1 / (double) date2; // Using floating point with cast:
   printf("Using mixed division with cast assigned to floating point variables: \n\tQuotient of %d & (double)%d = %f\n\n",date1,date2,date5);

    return 0;
}


