//////////////////////////////////////////////////////////////////////////
// Private Header
#pragma once

#include "AUII18NPrivateDef.h"

class AUILocale::Impl final
{
public:
    Impl() = default;
    Impl(const Impl& other);
    ~Impl() = default;
    Impl& operator=(const Impl& other);
    void CopyFrom(const Impl& other);
public:
    const icu::Locale& RefLocale() const {
        return m_Locale;
    }
    icu::Locale& RefLocale() {
        return m_Locale;
    }
private:
    icu::Locale m_Locale;
};
