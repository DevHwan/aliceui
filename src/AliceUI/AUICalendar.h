#pragma once
#define MIDAS_SDK
#include "AUII18NCommonDef.h"

class ALICEUI_API AUICalendar final
{
public:
    AUICalendar();
    AUICalendar(const AUICalendar& other);
    AUICalendar(AUICalendar&& other) noexcept;
    ~AUICalendar();

    //////////////////////////////////////////////////////////////////////////
    // Make
public:
    AUICalendar(const AUILocale& locale);
    AUICalendar(const AUITimeZone& timezone);
    AUICalendar(const AUITimeZone& timezone, const AUILocale& locale);



    //////////////////////////////////////////////////////////////////////////
    // DateField Set / Get
public:
    int32_t Get(const AUIDateFields field) const {
        bool _succcess = false;
        return this->Get(field, _succcess);
    }
    int32_t Get(const AUIDateFields field, bool& success) const;
    int32_t GetWeekOfMonth() const {
        return this->Get(AUIDateFields::kWeekOfMonth);
    }
    AUIDaysOfWeek GetDayOfWeek() const {
        return static_cast<AUIDaysOfWeek>(this->Get(AUIDateFields::kDayOfWeek));
    }
    AUIDaysOfWeek GetDayOfMonth() const {
        return static_cast<AUIDaysOfWeek>(this->Get(AUIDateFields::kDayOfMonth));
    }
    AUIMonths GetMonth() const {
        return static_cast<AUIMonths>(this->Get(AUIDateFields::kMonth));
    }
    int32_t GetYear() const {
        return this->Get(AUIDateFields::kYear);
    }
    int32_t GetDate() const {
        return this->Get(AUIDateFields::kDate);
    }
    int32_t GetActualMaximum(const AUIDateFields field, bool& success) const;
    int32_t GetActualMaximum(const AUIDateFields field) const {
        bool _success = false;
        return GetActualMaximum(field, _success);
    }
    int32_t GetActualMinimum(const AUIDateFields field, bool& success) const;
    int32_t GetActualMinimum(const AUIDateFields field) const {
        bool _success = false;
        return GetActualMinimum(field, _success);
    }
    void Set(const AUIDateFields field, const int32_t val);
    void Set(const int32_t year, const AUIMonths month, const int32_t day, const int32_t hour = 0, const int32_t minute = 0, const int32_t second = 0);
    void Set(const int32_t year, const int32_t month, const int32_t day, const int32_t hour = 0, const int32_t minute = 0, const int32_t second = 0);
    void Clear();
    void Clear(const AUIDateFields field);


    //////////////////////////////////////////////////////////////////////////
    // Difference
    std::optional<int32_t> GetFieldDifference(const AUIDateFields field, const AUIDateUTC time);


    //////////////////////////////////////////////////////////////////////////
    // Time
public:
    void SetTime(const AUIDateUTC& date);
    AUIDateUTC GetTime() const;
    static AUIDateUTC ToUTC(const int32_t year, const int32_t month, const int32_t day, const int32_t hour = 0, const int32_t minute = 0, const int32_t second = 0);
    static AUIDateUTC ToUTC(const int32_t year, const AUIMonths month, const int32_t day, const int32_t hour = 0, const int32_t minute = 0, const int32_t second = 0);
    static AUIDateUTC GetNow();


    //////////////////////////////////////////////////////////////////////////
    // Extra Information
public:
    bool IsInDaylightTime() const;
    AUIDaysOfWeek GetFirstDaysOfWeek() const;



    //////////////////////////////////////////////////////////////////////////
    // Internal
private:
    class Impl;
    std::unique_ptr< Impl > m_pImpl;
public:
    Impl * GetImpl() const { assert(m_pImpl); return m_pImpl.get(); }
};
