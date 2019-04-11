#include "pch.h"
#include "AUIDateFormatSymbolsImpl.h"
#include "AUILocaleImpl.h"
#include "AUICalendarImpl.h"

AUIDateFormatSymbols::Impl::Impl()
{
    UErrorCode errCode(U_ZERO_ERROR);
    m_pDateFormatSymbols = std::unique_ptr<icu::DateFormatSymbols>(new icu::DateFormatSymbols(errCode));
    AUIAssert(U_SUCCESS(errCode));
    AUIAssert(m_pDateFormatSymbols);
}

AUIDateFormatSymbols::Impl::Impl(const AUILocale& locale)
{
    UErrorCode errCode(U_ZERO_ERROR);
    m_pDateFormatSymbols = std::unique_ptr<icu::DateFormatSymbols>(new icu::DateFormatSymbols(locale.GetImpl()->RefLocale(), errCode));
    AUIAssert(U_SUCCESS(errCode));
    AUIAssert(m_pDateFormatSymbols);
}

AUIDateFormatSymbols::Impl::Impl(const AUICalendar& calendar)
{
    UErrorCode errCode(U_ZERO_ERROR);
    m_pDateFormatSymbols = std::unique_ptr<icu::DateFormatSymbols>(new icu::DateFormatSymbols(calendar.GetImpl()->GetCalendar()->getType(), errCode));
    AUIAssert(U_SUCCESS(errCode));
    AUIAssert(m_pDateFormatSymbols);
}

AUIDateFormatSymbols::Impl::Impl(const Impl& other)
{
    CopyFrom(other);
}

AUIDateFormatSymbols::Impl& AUIDateFormatSymbols::Impl::operator=(const Impl& other)
{
    CopyFrom(other);
    return *this;
}

void AUIDateFormatSymbols::Impl::CopyFrom(const Impl& other)
{
    *GetDFS() = *other.GetDFS();
}

bool AUIDateFormatSymbols::Impl::operator==(const Impl& other)
{
    return *GetDFS() == *other.GetDFS();
}
