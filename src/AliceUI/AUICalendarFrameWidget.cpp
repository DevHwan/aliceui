#include "pch.h"
#include "AUICalendarFrameWidget.h"
#include "AUIDateFormatSymbols.h"
#include "AUILocale.h"

AUICalendarFrameWidget::AUICalendarFrameWidget() noexcept
	: AUILinearLayoutWidget( false )
	, m_pPImpl( std::make_shared< AUICalendar >() )
	, m_Header( std::make_shared< AUILinearLayoutWidget >( true ) )
	, m_Quick( std::make_shared< AUICalendarQuickButtonWidget >(AUITableCriterion::DAY, L"Calendar" ) )
	, m_Body( std::make_shared< AUICalendarBodyWidget >() )
	, m_UBtn( std::make_shared< AUICalendarChangeButtonWidget >( true ) ) // Up
	, m_DBtn( std::make_shared< AUICalendarChangeButtonWidget >( false ) ) // Down
	, m_Day( 1 )
{
	SetDefaultSize(228.0f, 195.0f);
	m_Header->SetMarginLTRB(5.0f, 3.0f, 5.0f, 3.0f);
	m_Header->SetDefaultSize(218.0f, 20.0f);
	m_Quick->SetDefaultSize(100.0f, 20.0f);
	m_Quick->SetMarginRight(55.0f);
	m_UBtn->SetDefaultSize(30.0f, 20.0f);
	m_UBtn->SetMarginRight(1.0f);
	m_UBtn->SetCaption(L"UP");
	m_DBtn->SetDefaultSize(30.0f, 20.0f);
	m_DBtn->SetCaption(L"DOWN");

	m_Header->AddSubWidget(m_Quick);
	m_Header->AddSubWidget(m_UBtn);
	m_Header->AddSubWidget(m_DBtn);

	m_Year = m_pPImpl->GetYear();
	m_Month = m_pPImpl->GetMonth();

	m_pPImpl->Set(m_Year, m_Month, m_Day);
	m_FirstDayOfWeek = m_pPImpl->GetDayOfWeek();
	m_MaximumOfMonth = m_pPImpl->GetActualMaximum(AUIDateFields::kDate);

	Connect(m_UBtn->ClickSignal, this, &AUICalendarFrameWidget::OnClickUBtn);
	Connect(m_DBtn->ClickSignal, this, &AUICalendarFrameWidget::OnClickDBtn);
	Connect(m_Body->ReturnSignal, this, &AUICalendarFrameWidget::OnClickDate);
	Connect(m_Quick->BodyChangeUpSignal, this, &AUICalendarFrameWidget::OnClickQuickBtn);

	SetTableData(AUITableCriterion::DAY);
	m_Body->SetTable(AUITableCriterion::DAY);
	AddSubWidget(m_Header);
	AddSubWidget(m_Body->GetTable(AUITableCriterion::DAY));
}

void AUICalendarFrameWidget::SetTableData(const AUITableCriterion& criterion)
{
	m_Body->SetTable(criterion);
	
	if (criterion == AUITableCriterion::DAY)
	{
		AUILocale locale;
		locale.SetDefault();
		AUIDateFormatSymbols dfmtsym(locale);
		const auto wsMonth = dfmtsym.GetShortMonths();
		auto text = wsMonth[MonthToNumber(m_Month) - 1] + L" " + std::to_wstring(m_Year);
		SetQuickCaption(text);

		m_pPImpl->Set(m_Year, m_Month, 1);
		m_FirstDayOfWeek = m_pPImpl->GetDayOfWeek();
		m_MaximumOfMonth = m_pPImpl->GetActualMaximum(AUIDateFields::kDate);
		m_Body->GetTable(criterion)->SetTableData(criterion, m_Year, m_Month, m_FirstDayOfWeek, m_MaximumOfMonth);
	}
	else if (criterion == AUITableCriterion::MONTH)
	{
		auto text = std::to_wstring(m_Year);
		SetQuickCaption(text);
		m_Body->GetTable(criterion)->SetYearData(criterion, m_Year);
	}
	else if (criterion == AUITableCriterion::YEAR)
	{
		auto frontYear = m_Year / 10 * 10;
		auto behindYear = frontYear + 9;
		auto text = std::to_wstring(frontYear) + L" ~ " + std::to_wstring(behindYear);
		SetQuickCaption(text);
		m_Body->GetTable(criterion)->SetDecadeData(criterion, m_Year);
	}

	Invalidate();
	InvalidateChildren();
}

void AUICalendarFrameWidget::OnClickUBtn(AUIWidget*)
{
	if (m_Body->GetPresentState() == AUITableCriterion::DAY)
	{
		if (m_Month == AUIMonths::kDecember)
		{
			m_Month = AUIMonths::kJanuary;
			m_Year++;
		}
		else
		{
			auto tempMonth = static_cast<int>(m_Month);
			m_Month = static_cast<AUIMonths>(tempMonth + 1);
		}

		m_pPImpl->Set(m_Year, m_Month, 1);
		m_FirstDayOfWeek = m_pPImpl->GetDayOfWeek();
		m_MaximumOfMonth = m_pPImpl->GetActualMaximum(AUIDateFields::kDate);

		SetTableData(AUITableCriterion::DAY);
	}
	else if (m_Body->GetPresentState() == AUITableCriterion::MONTH)
	{
		m_Year++;
		SetTableData(AUITableCriterion::MONTH);
	}
	else if (m_Body->GetPresentState() == AUITableCriterion::YEAR)
	{
		m_Year += 10;
		SetTableData(AUITableCriterion::YEAR);
	}
}

void AUICalendarFrameWidget::OnClickDBtn(AUIWidget*)
{
	if (m_Body->GetPresentState() == AUITableCriterion::DAY)
	{
		if (m_Month == AUIMonths::kJanuary)
		{
			m_Month = AUIMonths::kDecember;
			m_Year--;
		}
		else
		{
			auto tempMonth = static_cast<int>(m_Month);
			m_Month = static_cast<AUIMonths>(tempMonth - 1);
		}

		m_pPImpl->Set(m_Year, m_Month, 1);
		m_FirstDayOfWeek = m_pPImpl->GetDayOfWeek();
		m_MaximumOfMonth = m_pPImpl->GetActualMaximum(AUIDateFields::kDate);

		SetTableData(AUITableCriterion::DAY);
	}
	else if (m_Body->GetPresentState() == AUITableCriterion::MONTH)
	{
		m_Year--;
		SetTableData(AUITableCriterion::MONTH);
	}
	else if (m_Body->GetPresentState() == AUITableCriterion::YEAR)
	{
		m_Year -= 10;
		SetTableData(AUITableCriterion::YEAR);
	}
}

void AUICalendarFrameWidget::OnClickDate(AUITableCriterion criterion, AUIMonthType tempType, int tempYear, int tempMonth, int tempDay)
{
	if (criterion == AUITableCriterion::DAY)
	{
		if (tempType == AUIMonthType::NEXTMONTH) // 다음 달
			OnClickUBtn(nullptr);
		else if (tempType == AUIMonthType::LASTMONTH) // 지난 달
			OnClickDBtn(nullptr);

		SetYear(tempYear);
		SetMonth(tempMonth);
		SetDay(tempDay);

		UserEventSignal.Send(this);
	}
	else if (criterion == AUITableCriterion::MONTH)
	{
		SetYear(tempYear);
		SetMonth(tempMonth);

		DelSubWidget(m_Body->GetTable(m_Body->GetPresentState()));
		SetTableData(AUITableCriterion::DAY);
		AddSubWidget(m_Body->GetTable(AUITableCriterion::DAY));
	}
	else if (criterion == AUITableCriterion::YEAR)
	{
		SetYear(tempYear);

		DelSubWidget(m_Body->GetTable(m_Body->GetPresentState()));
		SetTableData(AUITableCriterion::MONTH);
		AddSubWidget(m_Body->GetTable(AUITableCriterion::MONTH));
	}

	m_Quick->DownCriterion(criterion);
}

void AUICalendarFrameWidget::OnClickQuickBtn(const AUITableCriterion& criterion)
{
	DelSubWidget(m_Body->GetTable(m_Body->GetPresentState()));
	SetTableData(criterion);
	AddSubWidget(m_Body->GetTable(criterion));
}

void AUICalendarFrameWidget::SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay)
{
	m_Body->GetTable(AUITableCriterion::DAY)->SetPeriod(iStartYear, iStartMonth, iStartDay, iEndYear, iEndMonth, iEndDay);
}

void AUICalendarFrameWidget::SetFocus(const int& iYear, const int& iMonth)
{
	m_Year = iYear;
	m_Month = static_cast<AUIMonths>(iMonth - 1);
	m_Day = 1;

	DelSubWidget(m_Body->GetTable(m_Body->GetPresentState()));
	SetTableData(AUITableCriterion::DAY);
	AddSubWidget(m_Body->GetTable(AUITableCriterion::DAY));
}
