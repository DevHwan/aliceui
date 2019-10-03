#include "pch.h"
#include "AUICalendarElementWidget.h"
#include "AUILocale.h"
#include "AUIDateFormatSymbols.h"

AUICalendarElementWidget::AUICalendarElementWidget(AUITableCriterion criterion, const int& val)
{
	if (criterion == AUITableCriterion::DAY)
	{
		SetClickable(false);
		SetDefaultSize(30.0f, 20.0f);
		SetCaption(std::to_wstring(m_Day));
	}
	else if (criterion == AUITableCriterion::MONTH)
	{
		AUILocale locale;
		locale.SetDefault();
		AUIDateFormatSymbols dfmtsym(locale);
        const auto wsMonth = dfmtsym.GetShortMonths();
        //auto text = wsMonth[m_Month - 1];
        //SetCaption(text);
        if (wsMonth.end() != wsMonth.begin())
        {
            SetCaption(*wsMonth.begin());
        }
		SetDefaultSize(50.0f, 45.0f);
	}
	else if (criterion == AUITableCriterion::YEAR)
	{
		SetDefaultSize(50.0f, 45.0f);
		SetCaption(std::to_wstring(m_Year));
	}

	SetCaptionHorzAlign(AUITextHorzAlign::kCenter);
}

AUICalendarElementWidget::AUICalendarElementWidget(const std::wstring& dayofWeek)
{
	SetClickable(false);
	SetDefaultSize(30.0f, 20.0f);
	SetCaption(dayofWeek);
	SetCaptionColor(kAUIColorWhite);

	AUILocale locale;
	locale.SetDefault();
	AUIDateFormatSymbols dfmtsym(locale);

	const auto wsWeekdays = dfmtsym.GetShortWeekdays();

	if (dayofWeek == wsWeekdays[1])
		SetCaptionColor(kAUIColorRed);
	else if (dayofWeek == wsWeekdays[7])
		SetCaptionColor(kAUIColorBlue);

	SetCaptionColor(AUIState::kDefault, true, GetCaptionColor());
	SetCaptionColor(AUIState::kDefault, false, GetCaptionColor());
	SetCaptionColor(AUIState::kMouseHovered, true, GetCaptionColor());
	SetCaptionColor(AUIState::kPressed, true, GetCaptionColor());
	SetCaptionColor(AUIState::kDisabled, true, GetCaptionColor());

	SetCaptionHorzAlign(AUITextHorzAlign::kCenter);
	SetBackgroundDrawable(nullptr);
}

bool AUICalendarElementWidget::OnMouseLBtnUp(AUIMouseEvent::EventFlag flag)
{
	if (!IsClickable())
		return false;

	if (m_Criterion == AUITableCriterion::DAY)
	{
		if (m_MonthType == AUIMonthType::NEXTMONTH) // 다음 달
		{
			if (m_Month == 12)
				ReturnSignal.Send(m_Criterion, m_MonthType, m_Year + 1, 1, m_Day);
			else
				ReturnSignal.Send(m_Criterion, m_MonthType, m_Year, m_Month + 1, m_Day);
		}
		else if (m_MonthType == AUIMonthType::LASTMONTH) // 지난 달
		{
			if (m_Month == 1)
				ReturnSignal.Send(m_Criterion, m_MonthType, m_Year - 1, 12, m_Day);
			else
				ReturnSignal.Send(m_Criterion, m_MonthType, m_Year, m_Month - 1, m_Day);
		}
		else // 이번 달
			ReturnSignal.Send(m_Criterion, m_MonthType, m_Year, m_Month, m_Day);
	}
	else if (m_Criterion == AUITableCriterion::MONTH)
		ReturnSignal.Send(m_Criterion, m_MonthType, m_Year, m_Month, 1);
	else
		ReturnSignal.Send(m_Criterion, m_MonthType, m_Year, 1, 1);

	return true;
}

void AUICalendarElementWidget::SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay)
{
	m_iStartYear = iStartYear;
	m_iStartMonth = iStartMonth;
	m_iStartDay = iStartDay;
	m_iEndYear = iEndYear;
	m_iEndMonth = iEndMonth;
	m_iEndDay = iEndDay;

	long tempSDate = iStartYear * 10000 + iStartMonth * 100 + iStartDay;
	long tempEDate = iEndYear * 10000 + iEndMonth * 100 + iEndDay;
	long tempToday = m_Year * 10000 + m_Month * 100 + m_Day;
	bool checkDate = false;

	if (tempSDate <= tempToday && tempToday <= tempEDate)
		checkDate = true;

	if (m_MonthType == AUIMonthType::THISMONTH && checkDate)
	{
		SetClickable(true);

		auto pDefaultBG = std::make_shared< AUINinePatchDrawable >();
		pDefaultBG = AUINinePatchDrawable::CreateFromResourcePath(L"calendar/BG_default.9.png");
		auto pHoverBG = std::make_shared< AUINinePatchDrawable >();
		pHoverBG = AUINinePatchDrawable::CreateFromResourcePath(L"calendar/BG_hover.9.png");
		auto pPressBG = std::make_shared< AUINinePatchDrawable >();
		pPressBG = AUINinePatchDrawable::CreateFromResourcePath(L"calendar/BG_press.9.png");

		auto pDefaultBackground = std::make_shared< AUILayerDrawable >();
		pDefaultBackground->InsertLayer(pDefaultBG);
		auto pHoverBackground = std::make_shared< AUILayerDrawable >();
		pHoverBackground->InsertLayer(pHoverBG);
		auto pPressBackground = std::make_shared< AUILayerDrawable >();
		pPressBackground->InsertLayer(pPressBG);

		auto pStateDrawable = std::make_shared< AUIStateDrawable >();
		pStateDrawable->SetTrueStateDrawable(AUIState::kDefault, pDefaultBackground);
		pStateDrawable->SetTrueStateDrawable(AUIState::kMouseHovered, pHoverBackground);
		pStateDrawable->SetTrueStateDrawable(AUIState::kPressed, pPressBackground);
		SetBackgroundDrawable(pStateDrawable);
	}
	else
	{
		SetClickable(false);

		auto pDefaultBG = std::make_shared< AUINinePatchDrawable >();
		pDefaultBG = AUINinePatchDrawable::CreateFromResourcePath(L"calendar/BG_noimage.9.png");

		auto pDefaultBackground = std::make_shared< AUILayerDrawable >();
		pDefaultBackground->InsertLayer(pDefaultBG);

		auto pStateDrawable = std::make_shared< AUIStateDrawable >();
		pStateDrawable->SetTrueStateDrawable(AUIState::kDefault, pDefaultBackground);
		SetBackgroundDrawable(pStateDrawable);
	}

	Invalidate();
}

void AUICalendarElementWidget::SetTableData(const AUITableCriterion& criterion, const int32_t& tempYear, const AUIMonths& tempMonth,
	const AUIDaysOfWeek& tempFirstDay, const int32_t& tempMaximum, const int32_t& tempWeek, const int32_t& tempDay)
{
	m_Criterion = criterion;
	m_Year = tempYear;
	m_Month = static_cast<int>(tempMonth) + 1;
	auto pStateDrawable = std::make_shared< AUIStateDrawable >();
	auto pDefaultBG = std::make_shared< AUINinePatchDrawable >();
	pDefaultBG = AUINinePatchDrawable::CreateFromResourcePath(L"calendar/BG_noimage.9.png");

	if (tempDay > tempMaximum) // 다음 달
	{
		m_MonthType = AUIMonthType::NEXTMONTH;
		m_Day = tempDay - tempMaximum;
		SetCaptionColor(kAUIColorLightGray);
	}
	else if (tempDay < 1) // 지난 달
	{
		
		m_MonthType = AUIMonthType::LASTMONTH;
		AUICalendar Impi;
		auto tempMonthtoInt = static_cast<int>(tempMonth);
		Impi.Set(tempYear, static_cast<AUIMonths>(tempMonthtoInt - 1), 1);
		m_Day = Impi.GetActualMaximum(AUIDateFields::kDayOfMonth) + tempDay;
		SetCaptionColor(kAUIColorLightGray);
	}
	else // 이번 달
	{
		m_MonthType = AUIMonthType::THISMONTH;
		m_Day = tempDay;
		SetCaptionColor(kAUIColorBlack);
		/*pDefaultBG = MAUINinePatchDrawable::CreateFromResourcePath(L"calendar/BG_default.9.png");
		auto pHoverBG = std::make_shared< MAUINinePatchDrawable >();
		pHoverBG = MAUINinePatchDrawable::CreateFromResourcePath(L"calendar/BG_hover.9.png");
		auto pPressBG = std::make_shared< MAUINinePatchDrawable >();
		pPressBG = MAUINinePatchDrawable::CreateFromResourcePath(L"calendar/BG_press.9.png");

		auto pHoverBackground = std::make_shared< MAUILayerDrawable >();
		pHoverBackground->InsertLayer(pHoverBG);
		auto pPressBackground = std::make_shared< MAUILayerDrawable >();
		pPressBackground->InsertLayer(pPressBG);

		pStateDrawable->SetTrueStateDrawable(MAUIState::MouseHovered, pHoverBackground);
		pStateDrawable->SetTrueStateDrawable(MAUIState::Pressed, pPressBackground);*/
	}

	auto pDefaultBackground = std::make_shared< AUILayerDrawable >();
	pDefaultBackground->InsertLayer(pDefaultBG);
	pStateDrawable->SetTrueStateDrawable(AUIState::kDefault, pDefaultBackground);
	SetBackgroundDrawable(pStateDrawable);
	SetCaption(std::to_wstring(m_Day));

	Invalidate();

	if (m_iStartYear != -1 && m_iEndYear != -1)
		SetPeriod(m_iStartYear, m_iStartMonth, m_iStartDay, m_iEndYear, m_iEndMonth, m_iEndDay);
}

void AUICalendarElementWidget::SetYearData(const AUITableCriterion& criterion, const int& tempYear, const int& tempMonth)
{
	m_Criterion = criterion;
	m_Year = tempYear;
	m_Month = tempMonth;

	AUILocale locale;
	locale.SetDefault();
	AUIDateFormatSymbols dfmtsym(locale);
	const auto wsMonth = dfmtsym.GetShortMonths();
    AUIAssert(m_Month - 1 >= 0);
    AUIAssert(wsMonth.size() > m_Month - 1);
	auto text = wsMonth[m_Month - 1];
	SetCaption(text);
}

void AUICalendarElementWidget::SetDecadeData(const AUITableCriterion& criterion, const int& tempYear)
{
	m_Criterion = criterion;
	m_Year = tempYear;
	SetCaption(std::to_wstring(tempYear));
}
