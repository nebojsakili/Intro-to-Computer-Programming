/******************************************************************************
 * File: NK4192Lab4Part1.c
 * Author: Kili
 * Created on:  December 1, 2021, 03:15 AM
 *
 * UTA Student Name: Nebojsa Kilibarda
 * UTA ID: 1001934192
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define ROWS 25    //defining preprocessor constants ROWS & COLS to use for the array
#define COLS 4
#define AGECOLS 3
#define LENGTH 30
 
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

int happyBirthday(int day, int currentday, int month, int currentmonth);
int calculateAge(int day, int currentday, int month, int currentmonth, int year, int currentyear);
// LAB 3 FUNCTIONS
int wholeYearDays(int earlierYear, int laterYear);
int findAge(int day, int month, int year, int currentday, int currentmonth, int currentyear);
// int findOldest(float age[], int count);
int findOldest(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int currentday, int currentmonth, int currentyear, int count);
int daysSinceBday(int day, int month, int year, int currentday, int currentmonth, int currentyear);

void swap(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int rw, int cols, int dobcols);
void printTable(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int count);
void ageBubble(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int count);
void relBubble(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int count);
void nameBubble(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int count);
void birthdayBubble(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int count);
int binarySearch(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], char targetF[LENGTH], char targetL[LENGTH], int first, int last);
void printToFile(FILE *outFile, char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int count);

const int DY = 0;
const int MO = 1;
const int YR = 2;
const int REL = 0;
const int LAST = 1;
const int FIRST = 2;
const int GEN = 3;

int main(int argc, char *argv[])
{
    int currentday, currentmonth, currentyear;

    
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    currentday = local->tm_mday; // get day of month (1 to 31)
    currentmonth = local->tm_mon + 1;    // get month of year (0 to 11)
    currentyear = local->tm_year + 1900; // get year since 1900   
    printf("Today is : ");
    printSpaceDate(currentday, currentmonth, currentyear);
    blankLns(2);
    
    
    
    int dOfB[ROWS][AGECOLS];                 //dateOfBirth[25][3]
    float age[ROWS];                        
    char firstLastRel[ROWS][COLS][LENGTH]; //firstLastRelationship[25][4][30]
    char filenameB[50];                   //second file operated on
    int count = 0;

    printf("Please enter the name of the file: ");
    scanf("%[^\n]", filenameB);
    FILE *inFileB = fopen(filenameB, "r");
    
    if  (inFileB == NULL)
        printf("File could not be opened properly.\n\n");
    else 
    {
        while (!feof(inFileB))
        {
        fscanf(inFileB, "%s %f %s %d %d %d %[^,], %[^\n]", firstLastRel[count][REL], &age[count], firstLastRel[count][GEN],
            &dOfB[count][DY], &dOfB[count][MO], &dOfB[count][YR], firstLastRel[count][LAST], firstLastRel[count][FIRST]);
            
    if (checkDate(dOfB[count][DY],dOfB[count][MO],dOfB[count][YR]) == 0 && age[count] > 0 && //checking if the DOB is valid
        (firstLastRel[count][GEN][0] == 'F' || firstLastRel[count][GEN][0] == 'M' ||  //checking if the gender provided
         firstLastRel[count][GEN][0] == 'U' || firstLastRel[count][GEN][0] == 'N')   //fits one of the 4 available values
         && count < ROWS)   //make sure the # of lines in the file does not exceed arrays size
        count++;
        
        else
            printf("\nThe data on current line was not in the valid format, reading over.");
        }        
        printf("\n\nPrinting a table with valid information from the text file.");
        printTable(firstLastRel, age, dOfB, count);

        for (int k = 0; k < count; k++) //For loop to determine which members of the list passed away
        {
            if (findAge(dOfB[k][DY],dOfB[k][MO],dOfB[k][YR], currentday, currentmonth, currentyear) < age[k]-1 ||
               (findAge(dOfB[k][DY],dOfB[k][MO],dOfB[k][YR], currentday, currentmonth, currentyear) > age[k]+1))
               printf("\n%s %s, my %s, passed away at age %.0f.\n\n",firstLastRel[k][FIRST], firstLastRel[k][LAST], firstLastRel[k][REL], age[k]);
        }
        
        int oP = findOldest(firstLastRel, age, dOfB, currentday, currentmonth, currentyear, count); //Calling a function to find out who the oldest living person on file is
        printf("At age %.1f, %s %s was born on %d/%d/%d and is the oldest living person in the file.\n\n",age[oP], 
        firstLastRel[oP][FIRST], firstLastRel[oP][LAST], dOfB[oP][DY],dOfB[oP][MO],dOfB[oP][YR]);
        
        
        int mostRecent = 366;  //Printing out the most recent birthdate in the file
        int mrb = 0;          //Index for most recent birthdate
        for (int l = 0; l < count; l++)
        {
            if (mostRecent > daysSinceBday(dOfB[l][DY], dOfB[l][MO], dOfB[l][YR], 
            currentday, currentmonth, currentyear))
            {
                mostRecent = daysSinceBday(dOfB[l][DY], dOfB[l][MO], dOfB[l][YR], 
            currentday, currentmonth, currentyear);
            
                mrb = l;
            }
        }
        printf("Born on %2d/%2d/%2d, %s %s has the most recent birthdate in the file.", 
        dOfB[mrb][DY],dOfB[mrb][MO],dOfB[mrb][YR],
        firstLastRel[mrb][FIRST], firstLastRel[mrb][LAST]);    
    
    
    }
    FILE *outFile = fopen("L4OutNK4192.txt", "w+");
    fprintf(outFile, "Printing the valid values in a table format.\n\n");
    printToFile(outFile, firstLastRel, age, dOfB, count);
    
    ageBubble(firstLastRel, age, dOfB, count);
    
    fprintf(outFile, "\n\nSorting the ages in ascending order.\n\n");
    printToFile(outFile, firstLastRel, age, dOfB, count);
    printTable(firstLastRel, age, dOfB, count);
    
    relBubble(firstLastRel, age, dOfB, count);
    
    fprintf(outFile, "\n\nSorting relationships alphabetically.\n");
    printToFile(outFile, firstLastRel, age, dOfB, count);
    printTable(firstLastRel, age, dOfB, count);

    printf("\n\nSorting the last names alphabetically.");
    fprintf(outFile, "\n\nSorting the last names alphabetically.\n");
    nameBubble(firstLastRel, age, dOfB, count);
    
    printToFile(outFile, firstLastRel, age, dOfB, count);
    printTable(firstLastRel, age, dOfB, count);

    birthdayBubble(firstLastRel, age, dOfB, count);
    
    fprintf(outFile, "\n\nSorting birthdays from earliest to latest in a year.\n");
    printToFile(outFile, firstLastRel, age, dOfB, count);
    printTable(firstLastRel, age, dOfB, count);

    if (binarySearch(firstLastRel, age, dOfB, argv[1], argv[2], 0, count) == -1)
    {
        printf("\n\nBinary search for %s %s was unsuccessful.", argv[1], argv[2]);
    }
    else if (binarySearch(firstLastRel, age, dOfB, argv[1], argv[2], 0, count) == -2)
        {
            printf("\n\nError processing command line values.\n");
            printf("Please restart the program with valid input for the binary search.\n");
            printf("Remember to use double quotes for multiple-word names.\n");
        }
    else
    {
        printf("\n\nSorting the arrays alphabetically by name to perform a binary search for %s %s.\n", argv[1], argv[2]);
        printTable(firstLastRel, age, dOfB, count);
        printf("\n\nThe binary search succesfully located %s %s on row %d.", argv[1], argv[2], binarySearch(firstLastRel, age, dOfB, argv[1], argv[2], 0, count)+1);
    }
    
    char firstNm[LENGTH];
    char lastNm[LENGTH];
    
    printf("\n\nPlease input first and last name you want to perform a binary search on: ");
    scanf("%s %s", firstNm, lastNm);
    
    if (binarySearch(firstLastRel, age, dOfB, firstNm, lastNm, 0, count) == -1)
    {
        printf("\n\nBinary search for %s %s was unsuccessful.", firstNm, lastNm);
    }
    else if (binarySearch(firstLastRel, age, dOfB, firstNm, lastNm, 0, count) == -2)
        {
            printf("\n\nError processing command line values.\n");
            printf("Please restart the program with valid input for the binary search.\n");
            printf("Remember to use double quotes for multiple-word names.\n");
        }
    else
    {
        printf("\n\nThe binary search succesfully located %s %s on row %d.", firstNm, lastNm, binarySearch(firstLastRel, age, dOfB, firstNm, lastNm, 0, count)+1);
    }
    
    
    
    int day, month, year;
    int invalid = 0;    
    int format = 0;
    
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
    
    }  // end if valid
    
    return (EXIT_SUCCESS);
}

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
///////////////////////

int findAge(int day, int month, int year, int currentday, int currentmonth, int currentyear)
{
    int currentAge = 0 ;
    if (currentyear >= year)
    {
        if ((currentmonth < month) || ((currentmonth == month) && (currentday < day)))
        currentAge = currentyear-year-1;
        else
        currentAge = currentyear-year;
    }
    
    return currentAge;
}

int findOldest(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int currentday, int currentmonth, int currentyear, int count)
{
    float currentOldest = 0;
    int indexOldest = -1;
    for (int j = 0; j < count; j++)
        {
            if ((currentOldest < age[j]) && 
        (findAge(dOfB[j][DY],dOfB[j][MO],dOfB[j][YR], currentday, currentmonth, currentyear) > age[j]-1 &&
        (findAge(dOfB[j][DY],dOfB[j][MO],dOfB[j][YR], currentday, currentmonth, currentyear) < age[j]+1)))
            {
            currentOldest = age[j];
            indexOldest = j;
            }
        }
    return indexOldest;    
}

int daysSinceBday(int day, int month, int year, int currentday, int currentmonth, int currentyear)
{
    int daysSinceBday = 0;
    int daysToBday = priorMonthDays(month, year) + day;
    int daysToDate = priorMonthDays(currentmonth, currentyear) + currentday;
   
   if (daysToDate > daysToBday)
   {
       daysSinceBday = daysToDate - daysToBday;
   }
   else if (daysToDate < daysToBday)
   {
       daysSinceBday = daysToDate + (365 - daysToBday);
   }
   return daysSinceBday;
}






void swap(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int rw, int cols, int dobcols)
{
    for (int i = 0; i < cols; i++)
        {
            char tempWrd[LENGTH];
            strcpy(tempWrd, firstLastRel[rw][i]);
            strcpy(firstLastRel[rw][i], firstLastRel[rw+1][i]);
            strcpy(firstLastRel[rw+1][i], tempWrd);
        }
    for (int k = 0; k < dobcols; k++)
        {
           int tempDoB;
           tempDoB = dOfB[rw][k];
           dOfB[rw][k] = dOfB[rw+1][k];
           dOfB[rw+1][k] = tempDoB;
        }
        
        float tempAge;
        tempAge = age[rw];
        age[rw] = age[rw+1];
        age[rw+1] = tempAge;
}

void printTable(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int count)
{
    printf("\n\n");
    printf("\n%-25s %-20s %-10s %-20s %-10s %-20s\n\n", "First","Last", "Age", "Birthday", "Gender", "Relationship");
    printf("======================================================================================================\n\n");
        for (int i = 0; i < count; i++)  //For loop to print a formatted table containing all the information from file 
        {
        printf("%-25s %-20s %-10.2f %2d/%2d/%-14d %-10s %-20s\n", firstLastRel[i][FIRST], firstLastRel[i][LAST], age[i],
            dOfB[i][DY], dOfB[i][MO], dOfB[i][YR], firstLastRel[i][GEN], firstLastRel[i][REL]);    
        }
}
void printToFile(FILE *outFile, char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int count)
{
    fprintf(outFile, "\n%-25s %-20s %-10s %-20s %-10s %-20s\n", "First","Last", "Age", "Birthday", "Gender", "Relationship");
    fprintf(outFile, "======================================================================================================\n\n");
    for (int i= 0; i < count; i++)
    {
        fprintf(outFile, "%-25s %-20s %-10.2f %2d/%2d/%-14d %-10s %-20s\n", firstLastRel[i][FIRST], firstLastRel[i][LAST], age[i],
            dOfB[i][DY], dOfB[i][MO], dOfB[i][YR], firstLastRel[i][GEN], firstLastRel[i][REL]);
    }
}


void ageBubble(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int count)
{
    printf("\n\nSorting the ages in ascending order.");
    for (int i = 0; i < count - 1; i++)
    {
        for (int k = 0; k < count - 1; k++)
        {
            if(age[k] > age[k+1])
            swap(firstLastRel, age, dOfB, k, COLS, AGECOLS);
        }
    }
}

void relBubble(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int count)
{
    printf("\n\nSorting the relationships alphabetically.");
    for (int i = 0; i < count - 1; i++)
    {
        for (int k = 0; k < count -1; k++)
        {
            if (strcmp(firstLastRel[k][REL], firstLastRel[k+1][REL]) > 0)
            {
            swap(firstLastRel, age, dOfB, k, COLS, AGECOLS);
            }
        }        
    }
}
void nameBubble(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int count)
{
    // printf("\n\nSorting last names alphabetically.");
    for (int i = 0; i < count -1; i++)
    {
        for(int k = 0; k < count - 1; k++)
        {
            if ((strcmp(firstLastRel[k][LAST], firstLastRel[k+1][LAST]) > 0) || 
               ((strcmp(firstLastRel[k][LAST], firstLastRel[k+1][LAST]) == 0) && (strcmp(firstLastRel[k][FIRST], firstLastRel[k+1][FIRST]) > 0)))
            {
            swap(firstLastRel, age, dOfB, k, COLS, AGECOLS);
            }
        }
    }
}
void birthdayBubble(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], int count)
{
    printf("\n\nSorting from earliest to latest birthdays in a year.");
    for (int i = 0; i < count -1; i++)
    {
        for (int k = 0; k < count - 1; k++)
        {
            if ((dOfB[k][MO] > dOfB[k+1][MO]) || (dOfB[k][MO] == dOfB[k+1][MO] && dOfB[k][DY] > dOfB[k+1][DY]))
            {
            swap(firstLastRel, age, dOfB, k, COLS, AGECOLS);
            }
        }
    }
}
int binarySearch(char firstLastRel[ROWS][COLS][LENGTH], float age[ROWS], int dOfB[ROWS][AGECOLS], char targetF[LENGTH], char targetL[LENGTH], int first, int last)
{
    if ((targetF == NULL) || (targetL == NULL))
    {
        return -2;
    }
    nameBubble(firstLastRel, age, dOfB, last);
    if (first <= last)
    {
    int mid = (last + first)/2;
        if ((strcmp(firstLastRel[mid][LAST], targetL) == 0) && (strcmp(firstLastRel[mid][FIRST], targetF) == 0))
        {
            return mid;
        }
        else if ((strcmp(firstLastRel[mid][LAST], targetL) == 0) && (strcmp(firstLastRel[mid][FIRST], targetF) < 0))
            {
            binarySearch(firstLastRel, age, dOfB, targetF, targetL, mid+1, last);    
            }
        else if ((strcmp(firstLastRel[mid][LAST], targetL) == 0) && (strcmp(firstLastRel[mid][FIRST], targetF) > 0))
            {
            binarySearch(firstLastRel, age, dOfB, targetF, targetL, first, mid-1);
            }
        else if (strcmp(firstLastRel[mid][LAST], targetL) < 0)
            {
            binarySearch(firstLastRel, age, dOfB, targetF, targetL, mid+1, last);
            }
        else
            {
            binarySearch(firstLastRel, age, dOfB, targetF, targetL, first, mid-1);
            }
    }
    else
        return -1;
}




/*
Write a bubble sort function to sort the arrays by last name and then by first name in alphabetical 
order regardless of case.  This means, for example, that three people with last name of Patel should be 
sorted in order by first name.  The bubble sort function should call the swap function when a swap is 
needed.  Remember that all arrays must be passed in to the sort in order to pass them to the swap 
when needed.
*/

/*
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
*/





int happyBirthday(int day, int currentday, int month, int currentmonth)
{
    int hadBday = 0;
        if (currentmonth < month)
        printf("Happy future birthday!\n\n");
        
        else if ( currentmonth > month)
        {
        printf("Congratulations on having your birthday in 2021!\n\n");
        hadBday = 1;
        }
        else if (currentmonth == month)
        {
            if (currentday > day)
            {
            printf("Congratulations on having your birthday in 2021!\n\n");
            hadBday = 1;
            }
            if (currentday < day)
            printf("Your birthday is almost here!\n\n");
            if (currentday == day)
            {
            printf("HAPPY BIRTHDAY!!!\n\n");
            hadBday = 1;
            }
        return hadBday;    
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
            printf("\nError: Year is out of 4 digit range\n");
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