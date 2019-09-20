//////////////////////////////////////////////////////////////////////////
// Private Header
#pragma once

#include "AUII18NPrivateDef.h"


//////////////////////////////////////////////////////////////////////////
// Check enum order
static_assert(static_cast<int>(AUIDateFormat::kNone_Style) == icu::DateFormat::kNone, "Check enum order");
static_assert(static_cast<int>(AUIDateFormat::kShortRelative_Style) == icu::DateFormat::kShortRelative, "Check enum order");
static_assert(static_cast<int>(AUIDateFormat::kDefault_Style) == icu::DateFormat::kDefault, "Check enum order");

class AUIDateFormat::Impl final
{
public:
    Impl();
    Impl(const Impl& other);
    Impl(const AUIDateFormat::Type type, const AUIDateFormat::Style style, const icu::Locale& locale);
    Impl(const AUIDateFormat::Style styleDate, const AUIDateFormat::Style styleTime, const icu::Locale& locale);
    ~Impl() = default;
    Impl& operator=(const Impl& other);
    void CopyFrom(const Impl& other);
public:
    icu::DateFormat* GetDF() const {
        assert(m_pDateFormat);
        return m_pDateFormat.get();
    }
private:
    std::unique_ptr< icu::DateFormat > m_pDateFormat;
};
