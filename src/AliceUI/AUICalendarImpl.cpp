#include "pch.h"
#include "AUICalendarImpl.h"

AUICalendar::Impl::Impl()
{
    UErrorCode err(U_ZERO_ERROR);
    m_pCalendar = std::unique_ptr< icu::Calendar >(icu::Calendar::createInstance(icu::Locale::getDefault(), err));
    AUIAssert(U_SUCCESS(err));
}

AUICalendar::Impl::Impl(const Impl& other)
{
    CopyFrom(other);
}

AUICalendar::Impl::Impl(const AUILocale& locale)
{
    UErrorCode err;
    m_pCalendar = std::unique_ptr< icu::Calendar >(icu::Calendar::createInstance(locale.GetImpl()->RefLocale(), err));
    AUIAssert(U_SUCCESS(err));
}

AUICalendar::Impl::Impl(const AUITimeZone& timezone)
{
    UErrorCode err;
    m_pCalendar = std::unique_ptr< icu::Calendar >(icu::Calendar::createInstance(*timezone.GetImpl()->GetTimeZone(), err));
    AUIAssert(U_SUCCESS(err));
}

AUICalendar::Impl::Impl(const AUITimeZone& timezone, const AUILocale& locale)
{
    UErrorCode err;
    m_pCalendar = std::unique_ptr< icu::Calendar >(icu::Calendar::createInstance(*timezone.GetImpl()->GetTimeZone(), locale.GetImpl()->RefLocale(), err));
    AUIAssert(U_SUCCESS(err));
}

AUICalendar::Impl& AUICalendar::Impl::operator=(const Impl& other)
{
    CopyFrom(other);
    return *this;
}

void AUICalendar::Impl::CopyFrom(const Impl& other)
{
    m_pCalendar = std::unique_ptr< icu::Calendar >(GetCalendar()->clone());
    AUIAssert(m_pCalendar);
}
