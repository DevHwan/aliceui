#pragma once
#define MIDAS_SDK
#include "AUII18NCommonDef.h"

class ALICEUI_API AUISimpleDateFormat final
{
public:
    AUISimpleDateFormat(const std::wstring& pattern);
    ~AUISimpleDateFormat();

    //////////////////////////////////////////////////////////////////////////
    // Formatting : http://www.unicode.org/reports/tr35/tr35-dates.html#Date_Field_Symbol_Table
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
    bool IsEqual(const AUISimpleDateFormat& dateformat) const;
    bool operator==(const AUISimpleDateFormat& dateformat) const {
        return IsEqual(dateformat);
    }
    bool operator!=(const AUISimpleDateFormat& dateformat) const {
        return !IsEqual(dateformat);
    }

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
public:
    Impl * GetImpl() const {
        assert(m_pImpl);
        return m_pImpl.get();
    }
};
