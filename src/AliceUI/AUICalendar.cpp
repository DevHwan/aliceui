#include "pch.h"
#include "AUICalendar.h"
#include "AUICalendarImpl.h"

namespace
{

    inline UCalendarDateFields CvtToUDateField( const AUIDateFields& field )
    {
        return static_cast<UCalendarDateFields>( field );
    }
}

AUICalendar::AUICalendar()
    : m_pImpl( new Impl() )
{

}

AUICalendar::AUICalendar( const AUICalendar& other )
    : m_pImpl( new Impl() )
{
    *GetImpl() = *other.GetImpl();
}

AUICalendar::AUICalendar( AUICalendar&& other ) noexcept
    : m_pImpl( std::move( other.m_pImpl ) )
{

}

AUICalendar::AUICalendar( const AUILocale& locale )
    : m_pImpl( new Impl( locale ) )
{

}

AUICalendar::AUICalendar( const AUITimeZone& timezone )
    : m_pImpl( new Impl( timezone ) )
{

}

AUICalendar::AUICalendar( const AUITimeZone& timezone, const AUILocale& locale )
    : m_pImpl( new Impl( timezone, locale ) )
{

}

AUICalendar::~AUICalendar()
{

}

void AUICalendar::SetTime( const AUIDateUTC& date )
{
    UErrorCode err = U_ZERO_ERROR;
    GetImpl()->GetCalendar()->setTime( static_cast<UDate>( date ), err );
    assert( U_SUCCESS( err ) );
}

AUIDateUTC AUICalendar::GetTime() const
{
    UErrorCode err = U_ZERO_ERROR;
    const auto time = GetImpl()->GetCalendar()->getTime( err );
    assert( U_SUCCESS( err ) );
    return static_cast<AUIDateUTC>( time );
}

bool AUICalendar::IsInDaylightTime() const
{
    UErrorCode err = U_ZERO_ERROR;
    const auto isInDaylight = GetImpl()->GetCalendar()->inDaylightTime( err );
    assert( U_SUCCESS( err ) );
    return !!isInDaylight;
}

AUIDaysOfWeek AUICalendar::GetFirstDaysOfWeek() const
{
    UErrorCode err = U_ZERO_ERROR;
    const auto firstDayOfWeek = GetImpl()->GetCalendar()->getFirstDayOfWeek( err );
    assert( U_SUCCESS( err ) );
    return static_cast<AUIDaysOfWeek>( firstDayOfWeek );
}

AUICalendar::Impl * AUICalendar::GetImpl() const
{
    AUIAssert(m_pImpl);
    return m_pImpl.get();
}

AUIDateUTC AUICalendar::GetNow()
{
    return static_cast<AUIDateUTC>( icu::Calendar::getNow() );
}

int32_t AUICalendar::Get( const AUIDateFields field, bool& success ) const
{
    UErrorCode err = U_ZERO_ERROR;
    const auto val = GetImpl()->GetCalendar()->get( CvtToUDateField( field ), err );
    success = !!U_SUCCESS( err );
    return val;
}

void AUICalendar::Set( const AUIDateFields field, const int32_t val )
{
    GetImpl()->GetCalendar()->set( CvtToUDateField( field ), val );
}

void AUICalendar::Set( const int32_t year, const AUIMonths month, const int32_t date, const int32_t hour, const int32_t minute, const int32_t second )
{
    GetImpl()->GetCalendar()->set( year, static_cast< int32_t >( month ), date, hour, minute, second );
}

void AUICalendar::Set(const int32_t year, const int32_t month, const int32_t day, const int32_t hour /*= 0*/, const int32_t minute /*= 0*/, const int32_t second /*= 0*/)
{
    this->Set(year, NumberToMonth(month), day, hour, minute, second);
}

void AUICalendar::Clear()
{
    GetImpl()->GetCalendar()->clear();
}

void AUICalendar::Clear( const AUIDateFields field )
{
    GetImpl()->GetCalendar()->clear( CvtToUDateField( field ) );
}

int32_t AUICalendar::GetActualMaximum( const AUIDateFields field, bool& success ) const
{
    UErrorCode err = U_ZERO_ERROR;
    const auto val =  GetImpl()->GetCalendar()->getActualMaximum( CvtToUDateField( field ), err );
    success = !!U_SUCCESS( err );
    return val;
}

int32_t AUICalendar::GetActualMinimum( const AUIDateFields field, bool& success ) const
{
    UErrorCode err = U_ZERO_ERROR;
    const auto val = GetImpl()->GetCalendar()->getActualMinimum( CvtToUDateField( field ), err );
    success = !!U_SUCCESS( err );
    return val;
}

AUIDateUTC AUICalendar::ToUTC(const int32_t year, const AUIMonths month, const int32_t day, const int32_t hour, const int32_t minute, const int32_t second)
{
    AUICalendar _calendar;
    _calendar.Set(year, month, day, hour, minute, second);
    return _calendar.GetTime();
}

AUIDateUTC AUICalendar::ToUTC(const int32_t year, const int32_t month, const int32_t day, const int32_t hour, const int32_t minute, const int32_t second)
{
    return ToUTC(year, NumberToMonth(month), day, hour, minute, second);
}

std::optional<int32_t> AUICalendar::GetFieldDifference(const AUIDateFields field, const AUIDateUTC time)
{
    UErrorCode errCode(U_ZERO_ERROR);
    const auto val = GetImpl()->GetCalendar()->fieldDifference(time, CvtToUDateField(field), errCode);
    if (U_SUCCESS(errCode))
        return { val };
    else
        return {};
}
