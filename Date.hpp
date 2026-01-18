#pragma once

#include <stdexcept>

class Date {
    int year;
    int month;
    int day;

    static bool isLeap(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    static int daysInMonth(int y, int m) {
        static const int days[] =
            {31,28,31,30,31,30,31,31,30,31,30,31};

        if (m == 2 && isLeap(y))
            return 29;

        return days[m - 1];
    }

public:
    Date(int y, int m, int d)
        : year(y), month(m), day(d)
    {
        if (m < 1 || m > 12)
            throw std::invalid_argument("Invalid month");
        if (d < 1 || d > daysInMonth(y, m))
            throw std::invalid_argument("Invalid day");
    }

    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }

    // Comparisons
    bool operator==(const Date& o) const {
        return year == o.year && month == o.month && day == o.day;
    }

    bool operator<(const Date& o) const {
        if (year != o.year) return year < o.year;
        if (month != o.month) return month < o.month;
        return day < o.day;
    }

    bool operator!=(const Date& o) const { return !(*this == o); }
    bool operator>(const Date& o) const { return o < *this; }
    bool operator<=(const Date& o) const { return !(*this > o); }
    bool operator>=(const Date& o) const { return !(*this < o); }

    // Arithmetic
    Date addMonths(int n) const {
        int total = year * 12 + (month - 1) + n;
        int y = total / 12;
        int m = total % 12 + 1;

        int d = day;
        int dim = daysInMonth(y, m);
        if (d > dim) d = dim;

        return Date(y, m, d);
    }

    Date addYears(int n) const {
        int y = year + n;
        int d = day;
        if (month == 2 && day == 29 && !isLeap(y))
            d = 28;
        return Date(y, month, d);
    }

    static double yearFraction(const Date& d1, const Date& d2) {
        return daysBetween(d1, d2) / 365.0;
    }

private:
    static int daysFromEpoch(const Date& d) {
        static const int cumDays[] =
            {0,31,59,90,120,151,181,212,243,273,304,334};

        int y = d.year;
        int m = d.month;

        int days = 365 * (y - 1);
        days += (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;
        days += cumDays[m - 1] + d.day;

        if (m > 2 && isLeap(y))
            days += 1;

        return days;
    }

    static int daysBetween(const Date& d1, const Date& d2) {
        if (d2 < d1)
            throw std::invalid_argument("End before start");
        return daysFromEpoch(d2) - daysFromEpoch(d1);
    }
};
