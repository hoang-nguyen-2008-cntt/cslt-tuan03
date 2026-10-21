#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int day;
    int month;
    int year;
} Date;

int isLeapYear(int year)
{
    return (year % 400 == 0) ||
           (year % 4 == 0 && year % 100 != 0);
}

int daysInMonth(int month, int year)
{
    switch (month)
    {
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12:
            return 31;

        case 4: case 6: case 9: case 11:
            return 30;

        case 2:
            return isLeapYear(year) ? 29 : 28;
    }

    return 0;
}

void inputDate(Date *d)
{
    scanf("%d%d%d", &d->day, &d->month, &d->year);
}

void outputDate(const Date *d)
{
    printf("%04d-%02d-%02d",
           d->year,
           d->month,
           d->day);
}

int compareDate(const Date *a, const Date *b)
{
    if (a->year != b->year)
        return (a->year < b->year) ? -1 : 1;

    if (a->month != b->month)
        return (a->month < b->month) ? -1 : 1;

    if (a->day != b->day)
        return (a->day < b->day) ? -1 : 1;

    return 0;
}

Date tomorrow(const Date *d)
{
    Date result = *d;

    result.day++;

    if (result.day > daysInMonth(result.month, result.year))
    {
        result.day = 1;
        result.month++;

        if (result.month > 12)
        {
            result.month = 1;
            result.year++;
        }
    }

    return result;
}

Date yesterday(const Date *d)
{
    Date result = *d;

    result.day--;

    if (result.day == 0)
    {
        result.month--;

        if (result.month == 0)
        {
            result.month = 12;
            result.year--;
        }

        result.day = daysInMonth(result.month, result.year);
    }

    return result;
}

Date addDays(const Date *d, int k)
{
    Date result = *d;

    while (k--)
        result = tomorrow(&result);

    return result;
}

Date subtractDays(const Date *d, int k)
{
    Date result = *d;

    while (k--)
        result = yesterday(&result);

    return result;
}

int daysFromStartOfYear(const Date *d)
{
    int days = 0;

    for (int m = 1; m < d->month; m++)
        days += daysInMonth(m, d->year);

    days += d->day - 1;

    return days;
}

int daysSinceEpoch(const Date *d)
{
    int days = 0;

    for (int y = 1970; y < d->year; y++)
    {
        days += isLeapYear(y) ? 366 : 365;
    }

    days += daysFromStartOfYear(d);

    return days;
}

int daysBetween(const Date *a, const Date *b)
{
    int diff = daysSinceEpoch(a) - daysSinceEpoch(b);

    return diff < 0 ? -diff : diff;
}

int dayOfWeek(const Date *d)
{
    return (daysSinceEpoch(d) + 4) % 7;
}

int checkInt(int testNo, long long expected, long long actual)
{
    if (expected == actual)
    {
        printf("Test %d: PASS\n", testNo);
        return 1;
    }

    printf("Test %d: FAIL (expected %lld, got %lld)\n",
           testNo, expected, actual);

    return 0;
}

int checkDate(int testNo, Date expected, Date actual)
{
    if (expected.day == actual.day &&
        expected.month == actual.month &&
        expected.year == actual.year)
    {
        printf("Test %d: PASS\n", testNo);
        return 1;
    }

    printf("Test %d: FAIL (expected %04d-%02d-%02d, got %04d-%02d-%02d)\n",
           testNo,
           expected.year, expected.month, expected.day,
           actual.year, actual.month, actual.day);

    return 0;
}

int main()
{
    int passed = 0;

    passed += checkInt(1, 1, isLeapYear(2020));
    passed += checkInt(2, 0, isLeapYear(1900));
    passed += checkInt(3, 29, daysInMonth(2, 2020));
    passed += checkInt(4, 28, daysInMonth(2, 2019));

    Date d1 = {31, 12, 2019};
    Date d2 = {1, 1, 2020};

    passed += checkInt(5, -1, compareDate(&d1, &d2));
    passed += checkDate(6, d2, tomorrow(&d1));
    passed += checkDate(7, d1, yesterday(&d2));

    Date expected1 = {3, 1, 2020};
    passed += checkDate(8, expected1, addDays(&(Date){4,12,2019}, 30));

    Date expected2 = {4, 11, 2019};
    passed += checkDate(9, expected2, subtractDays(&(Date){4,12,2019}, 30));

    passed += checkInt(10, 60,
                       daysFromStartOfYear(&(Date){1,3,2020}));

    passed += checkInt(11, 10957,
                       daysSinceEpoch(&(Date){1,1,2000}));

    passed += checkInt(12, 88,
                       daysBetween(&(Date){4,12,2019},
                                   &(Date){1,3,2020}));

    passed += checkInt(13, 4,
                       dayOfWeek(&(Date){1,1,1970}));

    passed += checkInt(14, 6,
                       dayOfWeek(&(Date){1,1,2000}));

    printf("Passed %d/14\n", passed);

    return 0;
}