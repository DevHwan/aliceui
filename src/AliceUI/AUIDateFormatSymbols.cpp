#include "pch.h"
#include "AUIDateFormatSymbols.h"
#include "AUIDateFormatSymbolsImpl.h"

AUIDateFormatSymbols::AUIDateFormatSymbols()
    : m_pImpl(new Impl())
{

}

AUIDateFormatSymbols::AUIDateFormatSymbols(const AUILocale& locale)
    : m_pImpl(new Impl(locale))
{

}

AUIDateFormatSymbols::AUIDateFormatSymbols(const AUICalendar& calendar)
    : m_pImpl(new Impl(calendar))
{

}

AUIDateFormatSymbols::~AUIDateFormatSymbols()
{

}

bool AUIDateFormatSymbols::IsEqual(const AUIDateFormatSymbols& dfmtsym) const
{
    return *GetImpl() == *dfmtsym.GetImpl();
}

AUIDateFormatSymbols::Impl * AUIDateFormatSymbols::GetImpl() const
{
    AUIAssert(m_pImpl);
    return m_pImpl.get();
}

std::vector<std::wstring> AUIDateFormatSymbols::GetEras() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getEras(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(AUIICUStringUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> AUIDateFormatSymbols::GetEraNames() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getEraNames(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(AUIICUStringUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> AUIDateFormatSymbols::GetNarrowEras() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getNarrowEras(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(AUIICUStringUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> AUIDateFormatSymbols::GetMonths() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getMonths(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(AUIICUStringUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> AUIDateFormatSymbols::GetShortMonths() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getShortMonths(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(AUIICUStringUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> AUIDateFormatSymbols::GetWeekdays() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getWeekdays(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(AUIICUStringUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> AUIDateFormatSymbols::GetShortWeekdays() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getShortWeekdays(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(AUIICUStringUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> AUIDateFormatSymbols::GetQuarters() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getQuarters(cnt, icu::DateFormatSymbols::FORMAT, icu::DateFormatSymbols::ABBREVIATED);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(AUIICUStringUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}

std::vector<std::wstring> AUIDateFormatSymbols::GetAmPmStrings() const
{
    int32_t cnt = 0;
    auto arrStr = GetImpl()->GetDFS()->getAmPmStrings(cnt);
    assert(arrStr);
    std::vector<std::wstring> out;
    out.reserve(cnt);
    for (int32_t idx = 0; idx < cnt; ++idx)
    {
        out.emplace_back(AUIICUStringUtility::CvtToWStr(arrStr[idx]));
    }
    return out;
}
