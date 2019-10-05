#pragma once

#include "AUIStringFilter.h"

class ALICEUI_API AUIIntegerStringFilter : public AUIStringFilter
{
public:
    AUIIntegerStringFilter();
    ~AUIIntegerStringFilter() override;


    //////////////////////////////////////////////////////////////////////////
    // Filter method
public:
    std::wstring Filter(const std::wstring& strOrigin) override;
protected:
    std::wstring FilterInteger(const std::wstring& strOrigin);
};

