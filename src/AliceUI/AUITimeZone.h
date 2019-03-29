#pragma once
#define MIDAS_SDK

#include "AUII18NCommonDef.h"

class ALICEUI_API AUITimeZone final
{
public:
    AUITimeZone();
    AUITimeZone(const std::wstring& id);
    AUITimeZone(const AUITimeZone& other);
    AUITimeZone(AUITimeZone&& other) noexcept;
    ~AUITimeZone();

    //////////////////////////////////////////////////////////////////////////
    // Make
public:
    static AUITimeZone GetUnknown();


    //////////////////////////////////////////////////////////////////////////
    // Operation
public:
    bool IsEqual(const AUITimeZone& timezone) const;
    bool operator==(const AUITimeZone& timezone) const {
        return IsEqual(timezone);
    }
    bool operator!=(const AUITimeZone& timezone) const {
        return !IsEqual(timezone);
    }

    //////////////////////////////////////////////////////////////////////////
    // Internal
private:
    class Impl;
    std::unique_ptr< Impl > m_pImpl;
public:
    Impl * GetImpl() const { assert(m_pImpl); return m_pImpl.get(); }
};
