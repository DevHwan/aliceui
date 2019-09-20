#pragma once
#define MIDAS_SDK

#include "AUII18NCommonDef.h"
#include "AUILocale.h"

class ALICEUI_API AUIDateFormat final
{
public:
    AUIDateFormat();       // DateTime Type, Simple Style, Default Locale
    AUIDateFormat(const AUIDateFormat& other);
    ~AUIDateFormat();

    //////////////////////////////////////////////////////////////////////////
    // Style
public:
    enum Type
    {
        kDefault_Type = 0,      // Locale will be ignored
        kDate_Type,
        kTime_Type,
        kDateTime_Type,
    };
    enum Style
    {
        // Basic styles
        kNone_Style = -1,
        kFull_Style = 0,
        kLong_Style = 1,
        kMedium_Style = 2,
        kShort_Style = 3,
        // Offset
        kDateOffset_Style = kShort_Style + 1,

        // Date-Time Style
        kDateTime_Style = 8,

        // Relative Styles
        kRelative_Style = (1 << 7),
        kFullRelative_Style = (kFull_Style | kRelative_Style),
        kLongRelative_Style = (kLong_Style | kRelative_Style),
        kMediumRelative_Style = (kMedium_Style | kRelative_Style),
        kShortRelative_Style = (kShort_Style | kRelative_Style),

        // Default Style
        kDefault_Style = kMedium_Style
    };

    //////////////////////////////////////////////////////////////////////////
    // Special Style
public:
    AUIDateFormat(const Type type, const Style style, const AUILocale& locale = AUILocale());
    AUIDateFormat(const Style styleDate, const Style styleTime, const AUILocale& locale = AUILocale());


    //////////////////////////////////////////////////////////////////////////
    // Formatting
public:
    std::wstring Fmt(const AUIDateUTC& date);
    std::wstring Fmt(const AUICalendar& calendar);

    //////////////////////////////////////////////////////////////////////////
    // Parsing
public:
    bool Parse(const std::wstring& str, AUICalendar& calendar) const;





    //////////////////////////////////////////////////////////////////////////
    // Operation
public:
    bool IsEqual(const AUIDateFormat& dateformat) const;
    bool operator==(const AUIDateFormat& dateformat) const {
        return IsEqual(dateformat);
    }
    bool operator!=(const AUIDateFormat& dateformat) const {
        return !IsEqual(dateformat);
    }



    //////////////////////////////////////////////////////////////////////////
    // Internal
private:
    class Impl;
    std::unique_ptr< Impl > m_pImpl;
public:
    Impl * GetImpl() const;
};
