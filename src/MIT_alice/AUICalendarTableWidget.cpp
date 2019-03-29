#include "pch.h"
#include "AUICalendarTableWidget.h"

AUICalendarTableWidget::AUICalendarTableWidget(AUITableCriterion criterion)
	: AUILinearLayoutWidget(false)
{
	SetMarginLeft(5.0f);
	if (criterion == AUITableCriterion::DAY)
	{
		auto tempDayOfWeek = std::make_shared< AUICalendarRowWidget >(); // ¿äÀÏ
		tempDayOfWeek->SetMarginBottom(1.0f);
		m_vpTable.emplace_back(tempDayOfWeek);
		AddSubWidget(m_vpTable[0]);

		for (int i = 1; i < 7; i++)
		{
			auto tempRow = std::make_shared< AUICalendarRowWidget >(criterion);
			if (i != 6)
				tempRow->SetMarginBottom(1.0f);
			m_vpTable.emplace_back(tempRow);
			AddSubWidget(m_vpTable[i]);

			Connect(tempRow->ReturnSignal, this, &AUICalendarTableWidget::ReturnData);
		}
	}
	else if (criterion == AUITableCriterion::MONTH)
	{
		for (int i = 0; i < 3; i++)
		{
			auto tempRow = std::make_shared< AUICalendarRowWidget >(criterion);
			if (i != 2)
				tempRow->SetMarginBottom(4.0f);
			m_vpTable.emplace_back(tempRow);
			AddSubWidget(m_vpTable[i]);

			Connect(tempRow->ReturnSignal, this, &AUICalendarTableWidget::ReturnData);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			auto tempRow = std::make_shared< AUICalendarRowWidget >(criterion);
			if (i != 2)
				tempRow->SetMarginBottom(4.0f);
			m_vpTable.emplace_back(tempRow);
			AddSubWidget(m_vpTable[i]);

			Connect(tempRow->ReturnSignal, this, &AUICalendarTableWidget::ReturnData);
		}
	}
}

void AUICalendarTableWidget::SetTableData(const AUITableCriterion& criterion, const int32_t& tempYear, const AUIMonths& tempMonth, const AUIDaysOfWeek& tempFirstDay, const int32_t& tempMaximum)
{
	for (int i = 1; i < 7; i++)
		m_vpTable[i]->SetTableData(criterion, tempYear, tempMonth, tempFirstDay, tempMaximum, i);
}

void AUICalendarTableWidget::SetYearData(const AUITableCriterion& criterion, const int& year)
{
	for (int i = 0; i < 3; i++)
		m_vpTable[i]->SetYearData(criterion, year, i);
}

void AUICalendarTableWidget::SetDecadeData(const AUITableCriterion& criterion, const int& year)
{
	for (int i = 0; i < 3; i++)
		m_vpTable[i]->SetDecadeData(criterion, year, i);
}


void AUICalendarTableWidget::SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay)
{
	for (int i = 1; i < 7; i++)
		m_vpTable[i]->SetPeriod(iStartYear, iStartMonth, iStartDay, iEndYear, iEndMonth, iEndDay);
}

void AUICalendarTableWidget::ReturnData(AUITableCriterion criterion, AUIMonthType tempType, int tempYear, int tempMonth, int tempDay)
{
	ReturnSignal.Send(criterion, tempType, tempYear, tempMonth, tempDay);
}
