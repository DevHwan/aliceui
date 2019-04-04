#pragma once
#define MIDAS_SDK

#include "AUIAPIDef.h"

#include <memory>
#include <cassert>
#include <string>
#include <mutex>
#include <optional>

class AUILocale;
class AUIDateTime;
class AUICalendar;
class AUIDateFormat;
class AUITimeZone;

typedef double AUIDateUTC;

enum class AUIDateFields
{
    // AD or BC in Gregorian (Julian) calendar
    kEra,
    // Year
    kYear,
    // Month -> AUIMonths
    kMonth,
    // Week number within current year
    kWeekOfYear,
    // Week number within current month
    kWeekOfMonth,
    // Day of month (First day of month is 1)
    kDate,
    // Day number within current year
    kDayOfYear,
    // Day number within current week -> AUIDaysOfWeek
    kDayOfWeek,
    // Ordinal number of the day of the week within current month
    // Together with DayOfWeek, uniquely specifies a day within a month
    kDayOfWeekInMonth,
    // Hour is before / after noon
    kAmPm,
    // Hour of the morning of afternoon -> 12-hour clock
    kHour,
    // Hour of the day -> 24-hour clock
    kHourOfDay,
    // Minute within hour
    kMinute,
    // Second within the minute
    kSecond,
    // Millisecond within the second
    kMillisecond,
    // RAW offset from GMT in milliseconds
    kZoneOffset,
    // Daylight saving offset in milliseconds
    kDSTOffset,
    // Extended year corresponding to the WeekOfYear
    // May be on greater or less than ExtendedYear
    kYearWOY,
    // Localized day of week
    // Value ranges from 1 to 7 (1 is localized first day of the week)
    kDayOfWeekLocal,
    // Year of this calendar system - encompassing all supra-year
    // e.g. Gregorian(Julian) positive is AD, 1 BC == 0 extended, 2 BC == -1 extended, ...
    kExtendedYear,
    // Modified Julian day number
    // It demarcates days at local zone midnight, rather than noon GMT.
    // It is a local number - it depends on the local time zone
    kJulianDay,
    // Ranges from 0 to 23:59:59.999 (regardless of Daylight Saving Time-DST)
    kMillisecondsInDay,
    // Check if current month is leap month (0 or 1) -> See chinese calendar
    kIsLeapMonth,
    // Field count
    kFieldCount,
    // Days of month == Date
    kDayOfMonth = AUIDateFields::kDate
};

enum class AUIDaysOfWeek
{
    kSunday = 1,
    kMonday,
    kTuesday,
    kWednesday,
    kThursday,
    kFriday,
    kSaturday
};

enum class AUIMonths
{
    kJanuary = 0,
    kFebruary,
    kMarch,
    kApril,
    kMay,
    kJune,
    kJuly,
    kAugust,
    kSeptember,
    kOctober,
    kNovember,
    kDecember,
    kUndecimber      // Lunar calendar -> 13th month
};
inline AUIMonths NumberToMonth(int32_t nThMonth)
{
    return static_cast<AUIMonths>(nThMonth - 1);
}
inline int32_t MonthToNumber(AUIMonths month)
{
    return static_cast<int32_t>(month) + 1;
}

enum class AUIAmPms
{
    kAm,
    kPm
};

enum class AUISysTimeZone
{
    kAny,
    kCanonical,
    kCanonicalLocation
};
