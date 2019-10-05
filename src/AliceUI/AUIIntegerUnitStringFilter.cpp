#include "pch.h"
#include "AUIIntegerUnitStringFilter.h"

AUIIntegerUnitStringFilter::AUIIntegerUnitStringFilter()
{

}

AUIIntegerUnitStringFilter::~AUIIntegerUnitStringFilter()
{

}

std::wstring AUIIntegerUnitStringFilter::Filter( const std::wstring& strOrigin )
{
    const auto strUnit = AUIUnitString::ToString( GetUnitType() );

    auto strTarget = strOrigin;
    const auto strInteger = this->FilterInteger( strTarget );
    return strInteger + L" " + strUnit;
}
