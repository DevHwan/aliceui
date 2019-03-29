#include "pch.h"
#include "AUIDateFormat.h"
#include "AUIDateFormatImpl.h"
#include "AUILocaleImpl.h"
#include "AUICalendarImpl.h"

AUIDateFormat::AUIDateFormat()
    : m_pImpl( new Impl() )
{

}

AUIDateFormat::AUIDateFormat( const AUIDateFormat& other )
    : m_pImpl( new Impl() )
{
    *GetImpl() = *other.GetImpl();
}

AUIDateFormat::AUIDateFormat( const Type type, const Style style , const AUILocale& locale )
    : m_pImpl( new Impl( type, style, locale.GetImpl()->RefLocale() ) )
{

}

AUIDateFormat::AUIDateFormat( const Style styleDate , const Style styleTime , const AUILocale& locale )
    : m_pImpl( new Impl( styleDate, styleTime, locale.GetImpl()->RefLocale() ) )
{

}

AUIDateFormat::~AUIDateFormat()
{

}

bool AUIDateFormat::IsEqual( const AUIDateFormat& dateformat ) const
{
    return AUIICUStringUtility::UBoolToBool( *GetImpl()->GetDF() == *dateformat.GetImpl()->GetDF() );
}

std::wstring AUIDateFormat::Fmt( const AUIDateUTC& date )
{
    icu::UnicodeString ustr;
    GetImpl()->GetDF()->format(static_cast<UDate>(date), ustr);
    return AUIICUStringUtility::CvtToWStr( ustr );
}

std::wstring AUIDateFormat::Fmt(const AUICalendar& calendar)
{
    UErrorCode errCode(U_ZERO_ERROR);
    return this->Fmt(calendar.GetImpl()->GetCalendar()->getTime(errCode));
}

bool AUIDateFormat::Parse( const std::wstring& str, AUICalendar& calendar ) const
{
    icu::ParsePosition pos(0);
    GetImpl()->GetDF()->parse( AUIICUStringUtility::CvtToUStr( str ), *calendar.GetImpl()->GetCalendar(), pos );
    return icu::ParsePosition(0) != pos;
}
