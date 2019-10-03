#include "pch.h"
#include "AUICalendarFoldButton.h"

AUICalendarFoldButton::AUICalendarFoldButton() noexcept
	: m_pCalendar( std::make_shared< AUICalendarFrameWidget >() )
	, m_bFold( true )
	, m_Date( L"Calendar" )
{
	SetCaption(m_Date);
	SetCaptionHorzAlign(AUITextHorzAlign::kCenter);

	SetPopupWidget(m_pCalendar);
	SetPopupPosition(glm::vec3(0.0f, GetHeight() + 25.0f, 0.0f));

	Connect(m_pCalendar->UserEventSignal, this, &AUICalendarFoldButton::OnUserEvent);
}

bool AUICalendarFoldButton::OnMouseLBtnUp(AUIMouseEvent::EventFlag flag)
{
	FoldCalendar();
	return true;
}

void AUICalendarFoldButton::FoldCalendar()
{
	m_bFold = !m_bFold;

	if (m_bFold)
		Dismiss();
	else
	{
		Invoke(GetWidgetManager(), shared_from_this());
		m_pCalendar->SetSizePolicy(AUISizePolicy::kContent, AUISizePolicy::kContent);
	}
}

void AUICalendarFoldButton::OnUserEvent(AUICalendarFrameWidget* pCal)
{
	int tempYear;
	int tempMonth;
	int tempDay;

	tempYear = pCal->GetYear();
	tempMonth = pCal->GetMonth();
	tempDay = pCal->GetDay();

	UserEventSignal.Send(tempYear, tempMonth, tempDay);
	FoldCalendar();
}

void AUICalendarFoldButton::SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay)
{
	m_pCalendar->SetPeriod(iStartYear, iStartMonth, iStartDay, iEndYear, iEndMonth, iEndDay);
}

void AUICalendarFoldButton::SetFocus(const int& iYear, const int& iMonth)
{
	m_pCalendar->SetFocus(iYear, iMonth);
}
