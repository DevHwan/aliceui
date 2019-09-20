//////////////////////////////////////////////////////////////////////////
// Private Header
#pragma once

#include "AUII18NPrivateDef.h"

constexpr size_t AUIICUNullTerm = size_t(-1);   // Null termination mark

class AUIICUStringUtility final
{
public:
    AUIICUStringUtility() = default;
    ~AUIICUStringUtility() = default;


    //////////////////////////////////////////////////////////////////////////
    // String conversion
public:
    static icu::UnicodeString CvtToUStr(const std::wstring& in);
    static icu::UnicodeString CvtToUStr(const std::string& in);
    static icu::UnicodeString CvtToUStr(const char* pIn, const size_t len = AUIICUNullTerm);
    static icu::UnicodeString CvtToUStr(const wchar_t* pIn, const size_t len = AUIICUNullTerm);
    static std::wstring CvtToWStr(const icu::UnicodeString& in);
    static std::wstring CvtToWStr(const std::string& in);
    static std::wstring CvtToWStr(const char* pIn);
    static std::string CvtToStr(const icu::UnicodeString& in);
    static std::string CvtToStr(const std::wstring& in);
    static std::string CvtToStr(const wchar_t* pIn);

    //////////////////////////////////////////////////////////////////////////
    // Basic type conversion
public:
    static bool UBoolToBool(const UBool val) {
        return !!val;
    }
};
