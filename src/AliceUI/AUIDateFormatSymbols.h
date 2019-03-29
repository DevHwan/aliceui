#pragma once
#define MIDAS_SDK
#include "AUII18NCommonDef.h"

class ALICEUI_API AUIDateFormatSymbols final
{
public:
    AUIDateFormatSymbols();
    AUIDateFormatSymbols(const AUILocale& locale);
    AUIDateFormatSymbols(const AUICalendar& calendar);
    ~AUIDateFormatSymbols();

    //////////////////////////////////////////////////////////////////////////
    // Getters
public:
    std::vector<std::wstring> GetEras() const;
    std::vector<std::wstring> GetEraNames() const;
    std::vector<std::wstring> GetNarrowEras() const;
    std::vector<std::wstring> GetMonths() const;
    std::vector<std::wstring> GetShortMonths() const;
    std::vector<std::wstring> GetWeekdays() const;
    std::vector<std::wstring> GetShortWeekdays() const;
    std::vector<std::wstring> GetQuarters() const;
    std::vector<std::wstring> GetAmPmStrings() const;

    //////////////////////////////////////////////////////////////////////////
    // Operation
public:
    bool IsEqual(const AUIDateFormatSymbols& dfmtsym) const;
    bool operator==(const AUIDateFormatSymbols& dfmtsym) const {
        return IsEqual(dfmtsym);
    }
    bool operator!=(const AUIDateFormatSymbols& dfmtsym) const {
        return !IsEqual(dfmtsym);
    }
private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
public:
    Impl * GetImpl() const { assert(m_pImpl); return m_pImpl.get(); }
};
