/******************************************************************************
 * File: NK4192Lab3Part1.c
 * Author: Kili
 * Created on:  November 11, 2021, 11:00 PM
 *
 * UTA Student Name: Nebojsa Kilibarda
 * UTA ID: 1001934192
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

 #define ROWS 25    //defining preprocessor constants ROWS & COLS to use for the array
 #define COLS 3
/*
 * CSE1310 Fall 2021
 * Dr. J. Carter M. Tiernan
 * Dr T given code for Lab 2 - dates section
 */
int checkDate(int day, int month, int year);
int checkLeap(int yr);
void errorMsgs(int flag);
void printAmerDate( int day, int month, int year);
void printEuroDate( int day, int month, int year);
void printISODate( int day, int month, int year);
void printSpaceDate( int day, int month, int year);
void blankLn(void);
void blankLns(int n);
int addYear(int year);
int priorMonthDays(int month, int year);
void printDateAEI(int day, int month, int year);
// Add any new function declaration headers below this comment
int happyBirthday(int day, int currentday, int month, int currentmonth);
int calculateAge(int day, int currentday, int month, int currentmonth, int year, int currentyear);
// LAB 3 FUNCTIONS
int wholeYearDays(int earlierYear, int laterYear);
/*
 * Dr T given code for Lab 2 - dates section
 * Use all of this given code, then add the code as directed for Lab 2
 */
 const int DY = 0;
 const int MO = 1;
 const int YR = 2;

 
 

int main(int argc, char *argv[])
{

    int dates[ROWS][COLS];  //declaring a 2d array to store dates from a file
    int rows = 0;
    char filename[50];
    
    strcpy(filename, argv[1]);
    FILE *inFile = fopen(filename, "r");
    
    while ((!feof(inFile)) && (inFile != NULL))
       {
        fscanf(inFile, "%d %d %d", &dates[rows][DY], &dates[rows][MO], &dates[rows][YR]);
        if (checkDate(dates[rows][DY], dates[rows][MO], dates[rows][YR]) == 0)
            rows++; //only increment the row if the date read is valid
       }
    printf("\nThese are the valid dates from %s\n\n", filename);
       
        for (int r=0; r < rows; r++)  //printing different formats depending on the row
        {
            if (r % 4 == 0)
                printAmerDate(dates[r][DY], dates[r][MO], dates[r][YR]);
            else if (r % 4 == 1)
                printEuroDate(dates[r][DY], dates[r][MO], dates[r][YR]);
            else if (r % 4 == 2)
                printISODate(dates[r][DY], dates[r][MO], dates[r][YR]);
            else 
                printSpaceDate(dates[r][DY], dates[r][MO], dates[r][YR]);
              printf("\n\n");
        }
        
        int earlier = 0;
        int later = 0;
        
        for (int i=0; i < rows-1; i++)
        {
         if (dates[i][YR] == dates[i+1][YR] && dates[i][MO] == dates[i+1][MO] && dates[i][DY] == dates[i+1][DY])
            {
                printf("Both dates are %d.%d.%d, and there are no days inbetween\n", dates[i][DY],dates[i][MO],dates[i][YR]);
            }
        else 
        {
            if ((dates[i][YR] < dates[i+1][YR])
            || (dates[i][YR] == dates[i+1][YR] && dates[i][MO] < dates[i+1][MO])
            || (dates[i][YR] == dates[i+1][YR] && dates[i][MO] == dates[i+1][MO] && dates[i][DY] < dates[i+1][DY]))
            {
                earlier = i;
                later = i+1;
            }
            else
            {
                earlier = i+1;
                later = i;
            }
            printf("The dates are %d.%d.%d and %d.%d.%d, the earlier of the two is %d.%d.%d\n", 
                dates[i][DY],dates[i][MO],dates[i][YR],dates[i+1][DY],dates[i+1][MO],dates[i+1][YR],
                dates[earlier][DY],dates[earlier][MO],dates[earlier][YR]);
        }        
        int latterDate = priorMonthDays(dates[later][MO],dates[later][YR]) + dates[later][DY];
        int priorDate = priorMonthDays(dates[earlier][MO],dates[earlier][YR]) + dates[earlier][DY];
        
        if (checkLeap(dates[earlier][YR]) == 0)
            {
            priorDate = 365 - (priorMonthDays(dates[earlier][MO],dates[earlier][YR]) + dates[earlier][DY]);
            }
        else
            {
            priorDate = 366 - (priorMonthDays(dates[earlier][MO],dates[earlier][YR]) + dates[earlier][DY]);
            }
            printf("The number of days from the earlier date %d.%d.%d to the later date %d.%d.%d is %d\n\n",
            dates[earlier][DY],dates[earlier][MO],dates[earlier][YR],
            dates[later][DY],dates[later][MO],dates[later][YR],
            priorDate+latterDate+wholeYearDays(dates[earlier][YR],dates[later][YR]));
        }

  
  






   
   
   
   
    // alialumary@gmails.com
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
  
   
    // Do not change any of the given code in main
    // Add your new code after the comment marked with ***
    int day, month, year;
    int invalid = 0;    // used as a boolean flag
    int format = 0;
    
    int currentday, currentmonth, currentyear;
    
//    printf("Welcome to the date calculation program");
//    blankLns(2);
    
    // From https://www.techiedelight.com/print-current-date-and-time-in-c/
        // time_t is arithmetic time type declared in header file time.h  
        time_t now;
        // Obtain current time
        // time() returns the current time of the system as a time_t value
        time(&now);
        // Convert to local time format and print to stdout
        //printf("Today is : %s", ctime(&now));
        
        // localtime converts a time_t value to calendar time and
        // returns a pointer to a tm structure with its members
        // filled with the corresponding values
        struct tm *local = localtime(&now);
        currentday = local->tm_mday; // get day of month (1 to 31)
        currentmonth = local->tm_mon + 1;    // get month of year (0 to 11)
        currentyear = local->tm_year + 1900; // get year since 1900   
    //    printf("Today is : ");
     //   printSpaceDate(currentday, currentmonth, currentyear);
     //   blankLns(2);
    
    //End section from https://www.techiedelight.com/print-current-date-and-time-in-c/
    /*
    printf("Please enter three numbers separated by spaces \n");
    printf("that represent the day, the month, and \n");
    printf("the year (4 digits) of your birth: ");
    scanf("%d %d %d",&day, &month, &year);
    */
    invalid = checkDate(day, month, year);
    if (!invalid)
    {
        printDateAEI(day, month, year);
    } 
    else 
    {
      //  printf("INVALID: Your input date was invalid and cannot be printed\n");
    }
    
    blankLn();
   
    
    /*
    // if date is valid, 
    //   determine number of days between current date y2-m2-d2 and input date y1-m1-d1 
    // 
     * Algorithm:
     * Calculate the remaining days in the year of the given date. In other words, 
     * calculate the difference of y1-m1-d1 until y1-12-31. 
     * Count the whole years between both dates and get the number of days.
     * Calculate the outstanding days in the current year, y2-1-1 until y2-m2-d2
     * 
     *    input date----| | | | | |----current date (today)
     * 
     * */
    if (!invalid)
    {
    // Calculate from a date to Dec 31 of same year 
    // Find out how many days from Jan 1 to current date and subtract from 365/366
    int sum = priorMonthDays(month, year) + day; // from Jan 1 to user's input date
    //printf("From Jan 1 to your given date of that year is %d days\n",sum);
    
   if (currentyear > year) // ****
    {
        sum = addYear(year) - sum;
        //printf("From your given date to Dec 31 of that year is %d days\n",sum);
        // At this point sum has the number of days from given date to Dec 31 of given year
    }
    
    // To get the sum of the days in the intervening years, there are multiple approaches:
    // 1) Subtract current year minus given year * 365 + extra Feb 29s that are in between
    // 2) Loop from given year to current year and add correct 365/366 for each year
    // 3) ??
    
    int countYr = year + 1;
    while (countYr < currentyear)
    {
        sum += addYear(countYr);
        //printf("Added year %d\n",countYr);
        countYr++;
    }
    
    int thisYear = priorMonthDays(currentmonth, currentyear) + currentday;
    //printf("From Jan 1 to the current date of this year is %d days\n",thisYear);
    
    // Handle dates in current year
    if (currentyear == year)   
    {
        sum = thisYear - sum;   
    }
    else     
    {
        sum = sum + thisYear;
    }
    
    printf("\nThe number of days from the entered date to the current date is %d\n\n", sum);
    
    // *** START THE LAB2 MAIN FUNCTION CODE THAT YOU ARE ADDING HERE ***
    int monthsFromDate = sum/31;
    printf("The number of months from the entered date to the current date is %d\n\n", monthsFromDate);
    
    int leapYr = checkLeap(year);
    if (leapYr == 0)
        {
        printf("The given date was not in a leap year.\n\n");
        }
        else
        {
        printf("The given date was in a leap year.\n\n");
        }
        
    happyBirthday(day, currentday, month, currentmonth);
    
    int currentAge = calculateAge(day, currentday, month, currentmonth, year, currentyear);
    printf("In the US, at age %d you are:\n", currentAge);
    
    if (currentAge < 18)
    printf("Not old enough to vote.\n");
    
    if (currentAge >= 16)
    printf("Usually old enough to get a driver's licence\n");
    
    if ( (currentAge >= 17) && (currentAge <= 42) )
    printf("Old enough to enroll in the military\n");
    
    if ( (currentAge >= 18) && (currentAge <= 30) )
    printf("Old enough to become an air traffic controller\n");
    
    if (currentAge >= 21)
    printf("Old enough to drink nationally\n");
    
    if (currentAge >= 25)
    printf("Old enough to be in the Congress\n");
    
    if (currentAge >= 28)
    printf("Too old to enlist in the Marines\n");
    
    if (currentAge >= 30)
    printf("Old enough to be in the Senate\n");
    
    if (currentAge > 30)
    printf("Too old to start as an air traffic controller\n");
    
    if (currentAge >= 35)
    printf("Old enough to be elected President\n");
    
    if (currentAge > 42)
    printf("Too old to enlist in any branch of the military\n");
    
    if (currentAge >= 56)
    printf("Too old to remain an air traffic controller\n");
    
    if (currentAge >= 67)
    printf("Old enough to collect full Social Security benefits\n");
    
    
    }  // end if valid
    return (EXIT_SUCCESS);
}
// *** PUT YOUR NEW FUNCTION(S) FOR LAB2 HERE AFTER MAIN ***
// Don't forget to put your function declaration header(s) up before main
// ALL FUNCTIONS BELOW HERE SHOULD BE THE FUNCTIONS GIVEN BY DR T.  
// DO NOT CHANGE ANY OF THE GIVEN FUNCTIONS BELOW 
// BUT YOU CAN ADD SIMILAR FUNCTIONS ABOVE IF NEEDED

int wholeYearDays(int earlierYear, int laterYear)
{
    int sum = 0;
    for (int j = earlierYear+1; j < laterYear; j++)
        {
        sum += addYear(j);
        }
        if (earlierYear == laterYear)
        {
        return 0;
        }
    return sum;    
}        






































int happyBirthday(int day, int currentday, int month, int currentmonth)
{
        if (currentmonth < month)
        printf("Happy future birthday!\n\n");
        
        else if ( currentmonth > month)
        printf("Congratulations on having your birthday in 2021!\n\n");
        
        else if (currentmonth == month)
        {
            if (currentday > day)
            printf("Congratulations on having your birthday in 2021!\n\n");
            if (currentday < day)
            printf("Your birthday is almost here!\n\n");
            if (currentday == day)
            printf("HAPPY BIRTHDAY!!!\n\n");
        }
}
int calculateAge(int day, int currentday, int month, int currentmonth, int year, int currentyear)
{
    int currentAge = 0;
    if (currentyear >= year)
    {
            if ( (currentmonth < month) || ((currentmonth == month) && (currentday < day)) )
            currentAge = currentyear-year-1;
            
            else if ( (currentmonth > month) || ((currentmonth == month) && (currentday >= day)) )
            currentAge = currentyear-year;
    }
printf("Your current age is %d\n\n", currentAge);
return currentAge;    
}
        
int addYear(int year)
{
    if (checkLeap(year) == 1)
        return 366;
    else 
        return 365;    
}
int priorMonthDays(int month, int year)
{
    // days in whole months
    int sum = 0;
    int lastm = month-1;
    
    if (lastm == 11)
        sum = sum + 30;
    if (lastm >= 10)
        sum = sum + 31;
    if (lastm >= 9)
        sum = sum + 30;
    if (lastm >= 8)
        sum += 31;
    if (lastm >= 7)
        sum += 31;
    if (lastm >= 6)
        sum += 30;   
    if (lastm >= 5)
        sum += 31;  
    if (lastm >= 4)
        sum += 30;  
    if (lastm >= 3)
        sum += 31;   
    if (lastm >= 2)
        if (checkLeap(year) == 1)  // checks user input year
            sum += 29;
        else
            sum += 28;
    if (lastm >= 1)
        sum += 31;
        
    // sum will be all the days in the months PRIOR to the current month in this year
    return sum;           
}
void printDateAEI(int day, int month, int year)
{
    int format = 1;
    blankLn();
    printf("What format would you like your output?\n");
    printf("1 = American (MDY), 2 = European (DMY), 3 = ISO (YMD), 4 = Spaces only (DMY)\n");
    printf("Enter the number for your format:\n");
    scanf("%d",&format);
    if (format == 1)
    {
        // print date in American format   7/4/2000
        printf("Your date in American format (MDY) is ");
        printAmerDate( day, month, year);
        blankLn();        
    }
    else if (format == 2)  //Error was in this line because format was assigned 2 (format = 2)
    {
        // print date in European format 
        printf("Your date in European format (DMY) is ");
        printEuroDate( day, month, year);
        blankLn();
    }  
    else if (format == 3)
    {
        // print date in ISO format 
        printf("Your date in ISO format (YMD) is ");
        printISODate( day, month, year);
        blankLn(); 
    }    
    else if (format == 4)
    {
        // print date in Spaces  format 
        printf("Your date in DMY spaces-only format is ");
        printSpaceDate( day, month, year);
        blankLn(); 
    } 
    else
    { 
        printf("Your format choice was not valid \n");
        printf("but your date in American format is ");
        printAmerDate( day, month, year);
        blankLn();
    }
}
void blankLn(void)
{
    printf("\n");
}
void blankLns(int n)
{
    for (int k = 0; k < n; k++)
        printf("\n");
}
int checkDate(int day, int month, int year)
{
    int dateInvalid = 0;  // dateValid will keep track of errors; 0 value indicateserror
    
    if ((year < 1000) || (year > 9999))
        dateInvalid = 1;
    
    else if ((month < 1) || (month > 12))
        dateInvalid = 2;
    
    else if ((day < 1) || (day > 31))
        dateInvalid = 3;
       
    /* 
     * At this point, if dateInvalid 1= 0, then there is an error
     * Therefore, we only want to continue if there are no errors
     * At this point, we now need to check if days and months are valid with each other
     * For example, we can't have Sept 31 or Feb 30
     */
    
    if (!dateInvalid)  // This is equivalent to saying (dateInvalid == 0)
    {
        if ( ((month == 4) || (month == 6) || (month == 9) || (month == 11)) &&
                (day > 30))
            dateInvalid = 4;
           
        else if (month == 2)
        {
            if (checkLeap(year) == 0)  // if it is NOT equal to a leap year 
                if (day > 28)
                    dateInvalid = 5;
            if (checkLeap(year) == 1)  // it is a leap year
                if (day > 29)
                    dateInvalid = 6;
        }
    }
   errorMsgs(dateInvalid);
    return dateInvalid;
}

void errorMsgs(int flag)
{
    switch (flag)
    {
        case 1: 
 //           printf("\nError: Year is out of 4 digit range\n");
            break;
        case 2:
            printf("\nError: Month is out of valid range\n");
            break;    
        case 3:
            printf("\nError: Day is out of valid range\n");
            break; 
        case 4:
            printf("\nError: Day is out of range for given month with 30 days\n");
            break; 
        case 5:
            printf("\nError: Day is out of range for given month and year\n");
            break; 
        case 6:
            printf("\nError: Day is out of range for given month and leap year\n");
            break;  
        default:
            break;             
    }
    
}
int checkLeap(int yr)
{
    /*
     * A year is a leap year if 
     * it is divisible by 4 and NOT divisible by 100 
     * UNLESS it is divisible by 400
     */
    int leap = 0;
    if ((yr % 4) != 0)  // yr % 4 - has possible answers of? 0, 1, 2, 3
        leap = 0;
    else if ((yr % 400) == 0)
        leap = 1;
    else if ((yr % 100) == 0)
        leap = 0;
    else
        leap = 1;
    
    return leap;
}
void printSpaceDate( int day, int month, int year)
{
    printf("%d %d %d", day, month, year);
    return;
}
void printAmerDate( int day, int month, int year)
{
    printf("%d/%d/%d",month, day, year);
    return;
}
void printEuroDate( int day, int month, int year)
{
    printf("%d.%d.%d",day,month, year);
    return;
}
void printISODate( int day, int month, int year)
{
    printf("%d-%d-%d",year, month, day);
    return;
}