#include "pch.h"
#include "AUITimeZoneImpl.h"

AUITimeZone::Impl::Impl()
{
    m_pTimeZone = std::unique_ptr< icu::TimeZone >(icu::TimeZone::createDefault());
}

AUITimeZone::Impl::Impl(const std::wstring& id)
{
    m_pTimeZone = std::unique_ptr< icu::TimeZone >(icu::TimeZone::createTimeZone(AUIICUStringUtility::CvtToUStr(id)));
}

AUITimeZone::Impl::Impl(const Impl& other)
{
    CopyFrom(other);
}

AUITimeZone::Impl& AUITimeZone::Impl::operator=(const Impl& other)
{
    CopyFrom(other);
    return *this;
}

void AUITimeZone::Impl::CopyFrom(const Impl& other)
{
    m_pTimeZone = std::unique_ptr< icu::TimeZone >(other.GetTimeZone()->clone());
}

void AUITimeZone::Impl::SetUnknown()
{
    m_pTimeZone = std::unique_ptr< icu::TimeZone >(icu::TimeZone::getUnknown().clone());
}
