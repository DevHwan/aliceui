#pragma once

#include "AUIButtonWidget.h"
#include "AUIJsonDrawableParser.h"
#include "AUINinePatchDrawable.h"
#include "AUIStateDrawable.h"
#include "AUICalendarCommonDef.h"

#include "AUII18NCommonDef.h"
#include "AUICalendar.h"

class ALICEUI_API AUICalendarElementWidget : public AUIButtonWidget
{
    // function
public:
    AUICalendarElementWidget(const std::wstring& dayofWeek);
    AUICalendarElementWidget(AUITableCriterion criterion, const int& val);
    ~AUICalendarElementWidget() override = default;

    void SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay);
    void SetTableData(const AUITableCriterion& criterion, const int32_t& tempYear, const AUIMonths& tempMonth,
        const AUIDaysOfWeek& tempFirstDay, const int32_t& tempMaximum, const int32_t& tempWeek, const int32_t& tempDay);
    void SetYearData(const AUITableCriterion& criterion, const int& tempYear, const int& tempMonth);
    void SetDecadeData(const AUITableCriterion& criterion, const int& tempYear);
protected:
    virtual bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override;
private:
    // variable
public:
    AUISignal<void(AUITableCriterion, AUIMonthType, int, int, int)> ReturnSignal;

private:
    AUITableCriterion m_Criterion = AUITableCriterion::DAY;
    AUIMonthType m_MonthType = AUIMonthType::THISMONTH;
    int m_Year = 2000;
    int m_Month = 1;
    int m_Day = 1;

    int m_iStartYear = -1;
    int m_iStartMonth = -1;
    int m_iStartDay = -1;
    int m_iEndYear = -1;
    int m_iEndMonth = -1;
    int m_iEndDay = -1;
};
