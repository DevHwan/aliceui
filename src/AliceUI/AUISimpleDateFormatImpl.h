//////////////////////////////////////////////////////////////////////////
// Private Header
#pragma once

#include "AUII18NPrivateDef.h"

class AUISimpleDateFormat::Impl final
{
public:
    Impl(const std::wstring& pattern);
    ~Impl() = default;

    // Copy
public:
    Impl(const Impl& other);
    Impl& operator=(const Impl& other);
    void CopyFrom(const Impl& other);

    // Formatter
public:
    icu::SimpleDateFormat* GetDF() const {
        assert(m_pDateFormat);
        return m_pDateFormat.get();
    }
private:
    std::unique_ptr<icu::SimpleDateFormat> m_pDateFormat;
};
