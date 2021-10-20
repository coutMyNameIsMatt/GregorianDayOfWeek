//Author:		Matthew Lowrie, mcl5645
//Class:		CMPSC 121
//Lab:		    9
//File:			C:\Users\lowri\OneDrive\Documents\School\CMPSC\Experiments\Lab9\Lab9.cpp
//Purpose:		Gregorian day of the week calculator with functions to check leap year and necessary calculation values
/********************************************************************\
* Academic Integrity Affidavit:                                      *                                                                                                                                                     *                                                                    *
* I certify that, this program code is my work.  Others may have     *
* assisted me with planning and concepts, but the code was written,  *
* solely, by me.                                                     *                                                                                  *                                                                    *
* I understand that submitting code which is totally or partially    *
* the product of other individuals is a violation of the Academic    *
* Integrity Policy and accepted ethical precepts. Falsified          *
* execution results are also results of improper activities. Such    *
* violations may result in zero credit for the assignment, reduced   *
* credit for the assignment, or course failure.                      *
\********************************************************************/
// Sources of logic assistance: N/A
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
bool isLeapYear(int year); //function prototypes - define type of return & type(s) of argument(s) it will be sent
int getCenturyValue(int year);
int getYearValue(int year);
int getMonthValue(int month, int year);
int main()
{
    bool isItALeapYear;
    int day, month, year, centuryValue, yearValue, monthValue;
    char reply;
    string dayOfWeek;
    do
    {
        cout << "Enter a date in the form month day year, e.g. 4 16 1987" << endl;
        cin >> month >> day >> year;
        if ((month > 12 || month < 1) || //This whole block checks for valid input, this line checks for valid month
            ((month == 2 && (day > 29 || day < 1))) ||  //checks for valid February day range
            ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day > 31 || day < 1)) || 
            //above line checks valid day range for 31 day months
            ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30 || day < 1)) || // checks valid day range for 30 day months
            (year < 1)) // checks that year is in common era 
        { 
            cout << "Invalid month, day, or year please use valid Gregorian calendar value!" << endl <<
                "Hints: make sure it's a valid month, that your month has that many days, and year is in common era." << endl; 
            reply = 'Y';
        }
        else
        {
            isItALeapYear = isLeapYear(year); 
            centuryValue = getCenturyValue(year);
            yearValue = getYearValue(year);
            monthValue = getMonthValue(month, year);
            int dayOfWeekValue;
            string leapText = " on a non-leap year!"; //Added functionality to tell the user if date is on a leap year.
            if (isItALeapYear == 0 && month == 2 && day == 29) 
            { 
                cout << "This is not a leap year, there can't be a 29th of February. Try again!" << endl; // checks to make sure there's no 2/29 on non leap years
                reply = 'Y';
            }
            else
            {
                if (isItALeapYear == 1) { leapText = " on a leap year!"; }
                dayOfWeekValue = ((day + monthValue + yearValue + centuryValue) % 7); // Runs final day of week calculation based on returns from functions
                if (dayOfWeekValue == 0) { dayOfWeek = "Sunday"; } // These lines pair the dayOfWeekValue(s) with their respective day of the week they represent
                if (dayOfWeekValue == 1) { dayOfWeek = "Monday"; }
                if (dayOfWeekValue == 2) { dayOfWeek = "Tuesday"; }
                if (dayOfWeekValue == 3) { dayOfWeek = "Wednesday"; }
                if (dayOfWeekValue == 4) { dayOfWeek = "Thursday"; }
                if (dayOfWeekValue == 5) { dayOfWeek = "Friday"; }
                if (dayOfWeekValue == 6) { dayOfWeek = "Saturday"; }
                cout << month << "/" << day << "/" << year << " is a " << dayOfWeek << leapText << endl; // User output to tell them the day of the week.
                cout << endl << "Would you like to check another date? Y or N "; //to allow user to opt whether to input additional runs
                cin >> reply;
            }
        }
    } while (toupper(reply) == 'Y'); 
    cout << "Thanks for using the program!" << endl; //End of program
    return 0;
}
bool isLeapYear (int year) //leap year checker function; receives year argument
{
    bool isItALeapYear;
    if ((year % 400 == 0) || ((year % 4 == 0) && year % 100 != 0)) { isItALeapYear = 1; } // these are the leap years per given parameters in document
    else { isItALeapYear = 0; }
    if (year == 4) { isItALeapYear = 0; } // not a leap year due to roman priest miscalculations. corrects this exception.
    return isItALeapYear; //sends a true-false value of leap year or not back
}
int getCenturyValue(int year) //century value function; receives year argument outputs a centuryValue needed for final day of week check
{
    int centuryValue = (3 - ((year / 100) % 4)) * 2;
    return centuryValue; // returns output to main for final calculation
}
int getYearValue(int year) //year value function; receives year argument outputs a yearValue needed for final day of week check
{
    int yearValue = ((year % 100) / 4) + (year % 100);
    return yearValue; // returns output to main for final calculation
}
int getMonthValue(int month, int year) //month value function; outputs a monthValue based on the leap year function and month; needed for final day of week check
{
    bool isItALeapYear = isLeapYear(year);
    int monthValue; //placeholder
    if (month == 10) { monthValue = 0; } //This block pairs months (other than Jan/Feb) with their value based on provided table
    if (month == 5) { monthValue = 1; } //This block pairs months (other than Jan/Feb) with their value based on provided table
    if (month == 8) { monthValue = 2; } //This block pairs months (other than Jan/Feb) with their value based on provided table
    if (month == 3 || month == 11) { monthValue = 3; } //This block pairs months (other than Jan/Feb) with their value based on provided table
    if (month == 6) { monthValue = 4; } //This block pairs months (other than Jan/Feb) with their value based on provided table
    if (month == 9 || month == 12) { monthValue = 5; } //This block pairs months (other than Jan/Feb) with their value based on provided table
    if (month == 4 || month == 7) { monthValue = 6; } //This block pairs months (other than Jan/Feb) with their value based on provided table
    if (isItALeapYear == 0) // this statement pairs Jan/Feb non-leap months with their value from the table
    {
        if (month == 1) { monthValue = 0; }
        if (month == 2) { monthValue = 3; }
    }
    else // this statement pairs Jan/Feb leap months with their value from the table
    {
        if (month == 1) { monthValue = 6; }
        if (month == 2 ) { monthValue = 2; }
    }
    return monthValue; // returns output to main
}
/* Execution Sample:
Enter a date in the form month day year, e.g. 4 16 1987
10 26 2016
10/26/2016 is a Wednesday on a leap year!

Would you like to check another date? Y or N y
Enter a date in the form month day year, e.g. 4 16 1987
12 25 2016
12/25/2016 is a Sunday on a leap year!

Would you like to check another date? Y or N y
Enter a date in the form month day year, e.g. 4 16 1987
2 29 2015
This is not a leap year, there can't be a 29th of February. Try again!
Enter a date in the form month day year, e.g. 4 16 1987
10 25 2021
10/25/2021 is a Monday on a non-leap year!

Would you like to check another date? Y or N n
Thanks for using the program!

C:\Users\lowri\OneDrive\Documents\School\CMPSC\Experiments\Lab9\Debug\Lab9.exe (process 21828) exited with code 0.
Press any key to close this window . . .
*/