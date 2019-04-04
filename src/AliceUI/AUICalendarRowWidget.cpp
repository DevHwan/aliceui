#include "pch.h"
#include "AUICalendarRowWidget.h"
#include "AUIDateFormatSymbols.h"
#include "AUILocale.h"

AUICalendarRowWidget::AUICalendarRowWidget()
	: AUILinearLayoutWidget(true)
{
	AUILocale locale;
	locale.SetDefault();
	AUIDateFormatSymbols dfmtsym(locale);
	const auto wsWeekdays = dfmtsym.GetShortWeekdays();

	for (int i = 0; i < 7; i++)
	{
		auto tempElement = std::make_shared< AUICalendarElementWidget >(wsWeekdays[i + 1]);
		if (i != 6)
			tempElement->SetMarginRight(1.0f);
		m_vpRow.emplace_back(tempElement);
		AddSubWidget(m_vpRow[i]);
	}
}

AUICalendarRowWidget::AUICalendarRowWidget(AUITableCriterion criterion)
	: AUILinearLayoutWidget(true)
{
	if (criterion == AUITableCriterion::DAY)
	{
		for (int i = 0; i < 7; i++)
		{
			auto tempElement = std::make_shared< AUICalendarElementWidget >(criterion, -1);
			if (i != 6)
				tempElement->SetMarginRight(1.0f);
			m_vpRow.emplace_back(tempElement);
			AddSubWidget(m_vpRow[i]);

			Connect(tempElement->ReturnSignal, this, &AUICalendarRowWidget::ReturnData);
		}
	}
	else if (criterion == AUITableCriterion::MONTH)
	{
		for (int i = 0; i < 4; i++)
		{
			auto tempElement = std::make_shared< AUICalendarElementWidget >(criterion, -1);
			if (i != 3)
				tempElement->SetMarginRight(6.0f);
			m_vpRow.emplace_back(tempElement);
			AddSubWidget(m_vpRow[i]);

			Connect(tempElement->ReturnSignal, this, &AUICalendarRowWidget::ReturnData);
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			auto tempElement = std::make_shared< AUICalendarElementWidget >(criterion, -1);
			if (i != 3)
				tempElement->SetMarginRight(6.0f);
			m_vpRow.emplace_back(tempElement);
			AddSubWidget(m_vpRow[i]);

			Connect(tempElement->ReturnSignal, this, &AUICalendarRowWidget::ReturnData);
		}
	}
}

void AUICalendarRowWidget::SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay)
{
	for (int i = 0; i < 7; i++) // 일월화수목금토
		m_vpRow[i]->SetPeriod(iStartYear, iStartMonth, iStartDay, iEndYear, iEndMonth, iEndDay);
}

void AUICalendarRowWidget::SetTableData(const AUITableCriterion& criterion, const int32_t& tempYear, const AUIMonths& tempMonth, const AUIDaysOfWeek& tempFirstDay, const int32_t& tempMaximum, const int32_t& tempWeek)
{
	auto StartDayofWeek = static_cast<int32_t>(tempFirstDay); // 시작 요일
	if (StartDayofWeek == 1)
		StartDayofWeek = 8; // 지난 달의 한 주를 보여주기 위해

	for (int i = 0; i < 7; i++) // 일월화수목금토
	{
		auto tempDay = (tempWeek - 1) * 7 + i + 1; // 위치
		m_vpRow[i]->SetTableData(criterion, tempYear, tempMonth, tempFirstDay, tempMaximum, tempWeek, tempDay - StartDayofWeek + 1);
	}
}

void AUICalendarRowWidget::SetYearData(const AUITableCriterion& criterion, const int& year, const int& temp)
{
	for (int i = 0; i < 4; i++)
	{
		auto tempMonth = temp * 4 + i + 1;
		m_vpRow[i]->SetYearData(criterion, year, tempMonth);
	}
}

void AUICalendarRowWidget::SetDecadeData(const AUITableCriterion& criterion, const int& year, const int& temp)
{
	for (int i = 0; i < 4; i++)
	{
		auto tempYear = year / 10 * 10 - 1 + temp * 4 + i;
		m_vpRow[i]->SetDecadeData(criterion, tempYear);
	}
}

void AUICalendarRowWidget::ReturnData(AUITableCriterion criterion, AUIMonthType tempType, int tempYear, int tempMonth, int tempDay)
{
	ReturnSignal.Send(criterion, tempType, tempYear, tempMonth, tempDay);
}