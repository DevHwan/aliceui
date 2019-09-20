#include "pch.h"
#include "AUISimpleDateFormat.h"
#include "AUISimpleDateFormatImpl.h"
#include "AUICalendarImpl.h"

AUISimpleDateFormat::AUISimpleDateFormat(const std::wstring& pattern)
    : m_pImpl(new AUISimpleDateFormat::Impl(pattern))
{

}

AUISimpleDateFormat::~AUISimpleDateFormat()
{

}

std::wstring AUISimpleDateFormat::Fmt(const AUIDateUTC& date)
{
    icu::UnicodeString ustr;
    GetImpl()->GetDF()->format(static_cast<UDate>(date), ustr);
    return AUIICUStringUtility::CvtToWStr(ustr);
}

std::wstring AUISimpleDateFormat::Fmt(const AUICalendar& calendar)
{
    UErrorCode errCode(U_ZERO_ERROR);
    return this->Fmt(calendar.GetImpl()->GetCalendar()->getTime(errCode));
}

bool AUISimpleDateFormat::Parse(const std::wstring& str, AUICalendar& calendar) const
{
    icu::ParsePosition pos(0);
    GetImpl()->GetDF()->parse(AUIICUStringUtility::CvtToUStr(str), *calendar.GetImpl()->GetCalendar(), pos);
    return icu::ParsePosition(0) != pos;
}

bool AUISimpleDateFormat::IsEqual(const AUISimpleDateFormat& dateformat) const
{
    return AUIICUStringUtility::UBoolToBool(*GetImpl()->GetDF() == *dateformat.GetImpl()->GetDF());
}

AUISimpleDateFormat::Impl * AUISimpleDateFormat::GetImpl() const {
    AUIAssert(m_pImpl);
    return m_pImpl.get();
}
