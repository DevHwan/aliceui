#include "pch.h"
#include "MAUICloudImportWidget.h"

namespace
{
    constexpr SkScalar DefaultWidth = 150.0f;
    constexpr SkScalar DefaultHeight = 180.0f;
}

AUICloudImportWidget::AUICloudImportWidget()
	: AUILinearLayoutWidget(false)
{
	SetDefaultSize(DefaultWidth, DefaultHeight);
}

AUICloudImportWidget::~AUICloudImportWidget()
{

}
