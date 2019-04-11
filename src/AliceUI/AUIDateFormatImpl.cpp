#include "pch.h"
#include "AUIDateFormatImpl.h"

AUIDateFormat::Impl::Impl()
{
    m_pDateFormat = std::unique_ptr< icu::DateFormat >(icu::DateFormat::createInstance());
    AUIAssert(m_pDateFormat);
}

AUIDateFormat::Impl::Impl(const Impl& other)
{
    CopyFrom(other);
}

AUIDateFormat::Impl::Impl(const AUIDateFormat::Type type, const AUIDateFormat::Style style, const icu::Locale& locale)
{
    const auto icuStyle = static_cast<icu::DateFormat::EStyle>(style);
    switch (type)
    {
    case AUIDateFormat::Type::kDate_Type:
        m_pDateFormat = std::unique_ptr< icu::DateFormat >(icu::DateFormat::createDateInstance(icuStyle, locale));
        break;
    case AUIDateFormat::Type::kTime_Type:
        m_pDateFormat = std::unique_ptr< icu::DateFormat >(icu::DateFormat::createTimeInstance(icuStyle, locale));
        break;
    case AUIDateFormat::Type::kDateTime_Type:
        m_pDateFormat = std::unique_ptr< icu::DateFormat >(icu::DateFormat::createDateTimeInstance(icuStyle, icuStyle, locale));
        break;
    default:
        m_pDateFormat = std::unique_ptr< icu::DateFormat >(icu::DateFormat::createInstance());
        break;
    }
    AUIAssert(m_pDateFormat);
}

AUIDateFormat::Impl::Impl(const AUIDateFormat::Style styleDate, const AUIDateFormat::Style styleTime, const icu::Locale& locale)
{
    const auto icuStyleDate = static_cast<icu::DateFormat::EStyle>(styleDate);
    const auto icuStyleTime = static_cast<icu::DateFormat::EStyle>(styleTime);
    m_pDateFormat = std::unique_ptr< icu::DateFormat >(icu::DateFormat::createDateTimeInstance(icuStyleDate, icuStyleTime, locale));
    AUIAssert(m_pDateFormat);
}

AUIDateFormat::Impl& AUIDateFormat::Impl::operator=(const Impl& other)
{
    CopyFrom(other);
    return *this;
}

void AUIDateFormat::Impl::CopyFrom(const Impl& other)
{
    m_pDateFormat = std::unique_ptr< icu::DateFormat >(static_cast<icu::DateFormat*>(other.GetDF()->clone()));
    AUIAssert(m_pDateFormat);
}
