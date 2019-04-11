#pragma once
#define MIDAS_SDK
#include "AUII18NCommonDef.h"

class ALICEUI_API AUILocale final
{
public:
    AUILocale();
    AUILocale(const AUILocale& other);
    AUILocale(AUILocale&& other) noexcept;
    ~AUILocale();


    //////////////////////////////////////////////////////////////////////////
    // Locale language/country setter
    //  - language : ISO-639 code (https://en.wikipedia.org/wiki/ISO_639)
    //  - country : ISO-3166 code (https://en.wikipedia.org/wiki/ISO_3166)
public:
    static AUILocale Make(const std::wstring& language, const std::wstring& country = L"", const std::wstring& variant = L"", const std::wstring& keywordAndValues = L"") {
        AUILocale _locale;
        _locale.Set(language, country, variant, keywordAndValues);
        return _locale;
    }
    // Default
    void Set(const std::wstring& language, const std::wstring& country = L"", const std::wstring& variant = L"", const std::wstring& keywordAndValues = L"");
    void SetDefault();
    // Language
    void SetEnglish();
    void SetFrench();
    void SetGerman();
    void SetItalian();
    void SetJapanese();
    void SetKorean();
    void SetChinese();
    void SetSimplifiedChinese();
    void SetTraditionalChinese();
    // Country
    void SetFrance();
    void SetGermany();
    void SetItaly();
    void SetJapan();
    void SetKorea();
    void SetChina();
    void SetTaiwan();
    void SetUK();
    void SetUS();
    void SetCanada();
    void SetCanadaFrench();
    // Get
    std::wstring GetLanguage() const;
    std::wstring GetScript() const;
    std::wstring GetCountry() const;
    std::wstring GetVariant() const;
    bool IsScriptRightToLeft() const;


    //////////////////////////////////////////////////////////////////////////
    // Operation
public:
    bool IsEqual(const AUILocale& locale) const;
    bool operator==(const AUILocale& locale) const {
        return IsEqual(locale);
    }
    bool operator!=(const AUILocale& locale) const {
        return !IsEqual(locale);
    }


    //////////////////////////////////////////////////////////////////////////
    // Internal
private:
    class Impl;
    std::unique_ptr< Impl > m_pImpl;
public:
    Impl * GetImpl() const;
};
