//////////////////////////////////////////////////////////////////////////
// Private Header
#pragma once
#ifndef ALICEUI_EXPORTS
#   error Do not include *Impl.h outside
#endif

#include "AUII18NPrivateDef.h"
#include "AUILocaleImpl.h"
#include "AUITimeZoneImpl.h"

//////////////////////////////////////////////////////////////////////////
// Check enum order
static_assert(static_cast<int>(AUIDateFields::kFieldCount) == UCAL_FIELD_COUNT, "Check enum order");

class AUICalendar::Impl final
{
public:
    Impl();
    Impl(const Impl& other);
    Impl(const AUILocale& locale);
    Impl(const AUITimeZone& timezone);
    Impl(const AUITimeZone& timezone, const AUILocale& locale);
    ~Impl() = default;
    Impl& operator=(const Impl& other);
    void CopyFrom(const Impl& other);
public:
    icu::Calendar* GetCalendar() const {
        assert(m_pCalendar);
        return m_pCalendar.get();
    }
private:
    std::unique_ptr< icu::Calendar > m_pCalendar;
};
