#pragma once


#include "AUICalendarRowWidget.h"
#include "AUILinearLayoutWidget.h"
#include "AUII18NCommonDef.h"
#include "AUICalendarCommonDef.h"

class ALICEUI_API AUICalendarTableWidget : public AUILinearLayoutWidget
{
    // function
public:
    AUICalendarTableWidget(AUITableCriterion criterion);
    ~AUICalendarTableWidget() override = default;
    void SetTableData(const AUITableCriterion& criterion, const int32_t& tempYear, const AUIMonths& tempMonth,
        const AUIDaysOfWeek& tempFirstDay, const int32_t& tempMaximum);
    void SetYearData(const AUITableCriterion& criterion, const int& year);
    void SetDecadeData(const AUITableCriterion& criterion, const int& year);
    void SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay);
protected:

private:
    void ReturnData(AUITableCriterion criterion, AUIMonthType tempType, int tempYear, int tempMonth, int tempDay);

    // variable
public:
    AUISignal<void(AUITableCriterion, AUIMonthType, int, int, int)> ReturnSignal;
private:
    std::vector<std::shared_ptr<AUICalendarRowWidget>> m_vpTable;
};
