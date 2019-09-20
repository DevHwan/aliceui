//////////////////////////////////////////////////////////////////////////
// Private Header
#pragma once

#include "AUII18NPrivateDef.h"

class AUITimeZone::Impl final
{
public:
    Impl();
    Impl(const std::wstring& id);
    Impl(const Impl& other);
    ~Impl() = default;
    Impl& operator=(const Impl& other);
    void CopyFrom(const Impl& other);
public:
    void SetUnknown();
    icu::TimeZone* GetTimeZone() const {
        assert(m_pTimeZone);
        return m_pTimeZone.get();
    }
private:
    std::unique_ptr< icu::TimeZone > m_pTimeZone;
};
