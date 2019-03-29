#include "pch.h"
#include "AUITimeZone.h"
#include "AUITimeZoneImpl.h"

AUITimeZone::AUITimeZone()
    : m_pImpl( new Impl() )
{

}

AUITimeZone::AUITimeZone( const AUITimeZone& other )
    : m_pImpl( new Impl() )
{
    *GetImpl() = *other.GetImpl();
}

AUITimeZone::AUITimeZone( AUITimeZone&& other ) noexcept
    : m_pImpl( std::move( other.m_pImpl ) )
{

}

AUITimeZone::AUITimeZone( const std::wstring& id )
    : m_pImpl( new Impl( id ) )
{

}

AUITimeZone::~AUITimeZone()
{

}

bool AUITimeZone::IsEqual( const AUITimeZone& timezone ) const
{
    return !!( *GetImpl()->GetTimeZone() == *timezone.GetImpl()->GetTimeZone() );
}

AUITimeZone AUITimeZone::GetUnknown()
{
    static std::once_flag sOnce;
    static AUITimeZone sUnknownTimeZone;
    std::call_once( sOnce, [&]() {
        sUnknownTimeZone.GetImpl()->SetUnknown();
    } );
    return sUnknownTimeZone;
}
