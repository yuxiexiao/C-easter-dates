#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * easter:
 * This program takes as input a text file with a list of years. It creates a new
 * file writing what day Easter falls on for each given year.
 */



/* This function returns a string of what day Easter falls on given an integer
 * input year as an argument.
 */

int calculate_Easter_date(int year)
{
    int gold, leap, correction, sunday, epact, calendarMoon, century;

    if ((year < 1592) || (year > 39999))
    {
        return 0;
    }

    /* gold is the "golden year" in the 19 year Metonic cycle. */
    gold = (year % 19) + 1;
    century = (year / 100) + 1;
    /* leap is the skipped leap years. */
    leap = (3 * century / 4) - 12;
    /* correction is a correction factor for the moon's orbit */
    correction = ((8 * century + 5) / 25) - 5;
    /* March ((-sunday)% 7 + 7 is a Sunday). */
    sunday = ( 5 * year / 4) - leap - 10;
    /* epact is the "epact" which specifies when a full moon occurs. */
    epact = (11 * gold + 20 + correction - leap ) % 30;

    if ((epact == 25 && gold > 11) ||  (epact == 24))
    {
        epact++;
    }

    /* March "calendarMoon" is a calendar full moon. */
    calendarMoon = 44 - epact;

    if (calendarMoon < 21)
    {
        calendarMoon += 30;
    }

    calendarMoon = calendarMoon + 7 - (( sunday + calendarMoon) % 7);

    if (calendarMoon > 31)
    {
        return (calendarMoon - 31);/* The date is April (calendarMoon - 31) */
    }
    else
    {
        return -calendarMoon; /* The date is March (calendarMoon).
                               */
    }
}

int main(void)
{
    int scanned, scan, day;
    while (1)
        {
            scanned = scanf("%d", &scan);
            if (scanned == EOF)
            {
                break;
            }
            else
            {
                day = calculate_Easter_date(scan);

                if (day == 0)
                {
                    fprintf(stderr, "year is out of bounds!\n");
                    exit(1);
                }
                /* To differentiate March from April, we return a
                 * negative number.
                 */
                else if (day < 0)
                {
                    printf("%d - March %d\n", scan, -(day));
                }
                else
                {
                    printf("%d - April %d\n", scan, day);
                }
            }
        }
    return 0;
}
