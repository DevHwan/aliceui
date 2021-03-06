#pragma once

#include "AUIIntegerStringFilter.h"
#include "AUIUnitString.h"


class ALICEUI_API AUIIntegerUnitStringFilter : public AUIIntegerStringFilter
{
public:
    AUIIntegerUnitStringFilter();
    ~AUIIntegerUnitStringFilter() override;


    //////////////////////////////////////////////////////////////////////////
    // Filter method
public:
    std::wstring Filter(const std::wstring& strOrigin) override;


    //////////////////////////////////////////////////////////////////////////
    // Unit
public:
    void SetUnitType(const AUIUnitType& type) { m_UnitType = type; }
    AUIUnitType GetUnitType() const { return m_UnitType; }
private:
    AUIUnitType m_UnitType = AUIUnitType::kMeter;

};

