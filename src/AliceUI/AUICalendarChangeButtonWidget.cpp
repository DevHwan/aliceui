#include "pch.h"
#include "AUICalendarChangeButtonWidget.h"

AUICalendarChangeButtonWidget::AUICalendarChangeButtonWidget(const bool& direction)
{
	SetCaptionVertAlign(AUITextVertAlign::kCenter);
	SetCaptionHorzAlign(AUITextHorzAlign::kCenter);

	m_Direction = direction;
}
