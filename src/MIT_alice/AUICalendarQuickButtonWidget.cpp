#include "pch.h"
#include "AUICalendarQuickButtonWidget.h"

AUICalendarQuickButtonWidget::AUICalendarQuickButtonWidget(const AUITableCriterion& criterion, const std::wstring& val)
{
	m_Criterion = criterion;
	SetCaptionHorzAlign(AUITextHorzAlign::kCenter);
	SetCaption(val);
}

bool AUICalendarQuickButtonWidget::OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag)
{
	if (m_Criterion == AUITableCriterion::DAY)
		m_Criterion = AUITableCriterion::MONTH;
	else if (m_Criterion == AUITableCriterion::MONTH)
		m_Criterion = AUITableCriterion::YEAR;

	BodyChangeUpSignal.Send(m_Criterion);
	return true;
}

void AUICalendarQuickButtonWidget::DownCriterion(const AUITableCriterion& criterion)
{
	if (criterion == AUITableCriterion::MONTH)
		m_Criterion = AUITableCriterion::DAY;
	else if (criterion == AUITableCriterion::YEAR)
		m_Criterion = AUITableCriterion::MONTH;
}
