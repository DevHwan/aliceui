//////////////////////////////////////////////////////////////////////////
// Private Header
#pragma once
#ifndef ALICEUI_EXPORTS
#   error Do not include *Impl.h outside
#endif

#include "AUII18NPrivateDef.h"

class AUIDateFormatSymbols::Impl final
{
public:
    Impl();
    Impl(const AUILocale& locale);
    Impl(const AUICalendar& calendar);
    ~Impl() = default;

    // Copy
public:
    Impl(const Impl& other);
    Impl& operator=(const Impl& other);
    void CopyFrom(const Impl& other);

    // Equal
public:
    bool operator==(const Impl& other);

    // Formatter
public:
    icu::DateFormatSymbols* GetDFS() const {
        assert(m_pDateFormatSymbols);
        return m_pDateFormatSymbols.get();
    }
private:
    std::unique_ptr<icu::DateFormatSymbols> m_pDateFormatSymbols;
};
