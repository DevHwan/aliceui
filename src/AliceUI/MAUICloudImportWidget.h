#pragma once

#include "AUILinearLayoutWidget.h"

class AUIImageWidget;
class AUITextWidget;

class ALICEUI_API AUICloudImportWidget : public AUILinearLayoutWidget
{
public:
    AUICloudImportWidget();
    virtual ~AUICloudImportWidget();

private:
    std::shared_ptr< AUIImageWidget > m_pCloudTemplate;
    std::shared_ptr< AUITextWidget > m_pText;
};