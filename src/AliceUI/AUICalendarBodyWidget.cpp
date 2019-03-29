#include "pch.h"
#include "AUICalendarBodyWidget.h"

AUICalendarBodyWidget::AUICalendarBodyWidget() noexcept
	: m_dayTable(std::make_shared< AUICalendarTableWidget >(AUITableCriterion::DAY))
	, m_monthTable(std::make_shared< AUICalendarTableWidget >(AUITableCriterion::MONTH))
	, m_yearTable(std::make_shared< AUICalendarTableWidget >(AUITableCriterion::YEAR))
{
	Connect(m_dayTable->ReturnSignal, this, &AUICalendarBodyWidget::ReturnData);
	Connect(m_monthTable->ReturnSignal, this, &AUICalendarBodyWidget::ReturnData);
	Connect(m_yearTable->ReturnSignal, this, &AUICalendarBodyWidget::ReturnData);
}

std::shared_ptr< AUICalendarTableWidget > AUICalendarBodyWidget::GetTable(const AUITableCriterion& criterion)
{
	if (criterion == AUITableCriterion::DAY)
		return m_dayTable;
	else if (criterion == AUITableCriterion::MONTH)
		return m_monthTable;
	else
		return m_yearTable;
    AUIAssertFail();
    return {};
}

void AUICalendarBodyWidget::ReturnData(AUITableCriterion criterion, AUIMonthType tempType, int tempYear, int tempMonth, int tempDay)
{
	ReturnSignal.Send(criterion, tempType, tempYear, tempMonth, tempDay);
}