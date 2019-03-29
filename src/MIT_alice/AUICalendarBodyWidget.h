#pragma once

#include "AUICalendarTableWidget.h"


class ALICEUI_API AUICalendarBodyWidget : public AUIWidget
{
public:
    AUICalendarBodyWidget() noexcept;
    ~AUICalendarBodyWidget() override = default;

    std::shared_ptr< AUICalendarTableWidget > GetTable(const AUITableCriterion& criterion);
    void SetTable(const AUITableCriterion& criterion) { m_Criterion = criterion; }
    AUITableCriterion GetPresentState() { return m_Criterion; }
private:
    void ReturnData(AUITableCriterion criterion, AUIMonthType tempType, int tempYear, int tempMonth, int tempDay);

public:
    AUISignal< void(AUITableCriterion, AUIMonthType, int, int, int) > ReturnSignal;

private:
    std::shared_ptr< AUICalendarTableWidget > m_dayTable;
    std::shared_ptr< AUICalendarTableWidget > m_monthTable;
    std::shared_ptr< AUICalendarTableWidget > m_yearTable;

    AUITableCriterion m_Criterion = AUITableCriterion::DAY;
};
