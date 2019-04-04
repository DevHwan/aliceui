#pragma once


#include "AUICommonDef.h"
#include "AUILinearLayoutWidget.h"
#include "AUICheckboxWidget.h"
#include "AUIImageWidget.h"
#include "AUITextWidget.h"

class ALICEUI_API AUICloudTemplateWidget : public AUILinearLayoutWidget
{
public:
    AUICloudTemplateWidget();
    virtual ~AUICloudTemplateWidget();
protected:
    // Draw
private:
    virtual void OnDraw(SkCanvas* const canvas) override;

public:

private:
    std::shared_ptr< AUICheckboxWidget > m_pCheckBox;
    std::shared_ptr< AUIImageWidget > m_pImage;
    std::shared_ptr< AUITextWidget > m_pText;
};


