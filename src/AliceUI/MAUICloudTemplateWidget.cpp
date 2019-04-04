#include "pch.h"
#include "MAUICloudTemplateWidget.h"
#include "AUIResourceManager.h"

namespace
{
    constexpr SkScalar DefaultWidth = 150.0f;
    constexpr SkScalar DefaultHeight = 180.0f;
}

AUICloudTemplateWidget::AUICloudTemplateWidget()
	: AUILinearLayoutWidget(false)
	, m_pCheckBox( std::make_shared< AUICheckboxWidget >() )
	, m_pImage( std::make_shared< AUIImageWidget >() )
	, m_pText( std::make_shared< AUITextWidget >() )
{
	SetDefaultSize(DefaultWidth, DefaultHeight);

	m_pImage->SetImage(AUIResourceManager::Instance().LoadImage(L"test_files/CIM_Layout_Segment_Front.png"));

	m_pText->SetCaptionHorzAlign(AUITextHorzAlign::kCenter);
	m_pText->SetCaptionVertAlign(AUITextVertAlign::kCenter);
	m_pText->SetCaption(L"TEST_TEXT");

	AddSubWidget(m_pCheckBox);
	AddSubWidget(m_pImage);
	AddSubWidget(m_pText);
}

AUICloudTemplateWidget::~AUICloudTemplateWidget()
{

}

void AUICloudTemplateWidget::OnDraw(SkCanvas* const canvas)
{

}
