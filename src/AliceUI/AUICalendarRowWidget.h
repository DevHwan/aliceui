#pragma once

#include "AUILinearLayoutWidget.h"
#include "AUICalendarElementWidget.h"

class ALICEUI_API AUICalendarRowWidget : public AUILinearLayoutWidget
{
    // function
public:
    AUICalendarRowWidget();
    AUICalendarRowWidget(AUITableCriterion criterion);
    ~AUICalendarRowWidget() override = default;

    void SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay);
    void SetTableData(const AUITableCriterion& criterion, const int32_t& tempYear, const AUIMonths& tempMonth,
        const AUIDaysOfWeek& tempFirstDay, const int32_t& tempMaximum, const int32_t& tempWeek);
    void SetYearData(const AUITableCriterion& criterion, const int& year, const int& temp);
    void SetDecadeData(const AUITableCriterion& criterion, const int& year, const int& temp);
protected:

private:
    void ReturnData(AUITableCriterion criterion, AUIMonthType tempType, int tempYear, int tempMonth, int tempDay);
    // variable
public:
    AUISignal<void(AUITableCriterion, AUIMonthType, int, int, int)> ReturnSignal;
private:
    std::vector< std::shared_ptr< AUICalendarElementWidget > > m_vpRow;
};
