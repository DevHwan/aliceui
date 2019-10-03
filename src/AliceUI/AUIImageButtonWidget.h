#pragma once

#include "AUIImageWidget.h"

class ALICEUI_API AUIImageButtonWidget : public AUIImageWidget
{
    using SuperWidget = AUIImageWidget;
public:
    AUIImageButtonWidget();
    virtual ~AUIImageButtonWidget();



    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    virtual void OnMouseEnter() override;
    virtual void OnMouseLeave() override;
    virtual bool OnMouseLBtnDown(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnDblClk(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseMove(AUIMouseEvent::EventFlag flag) override;
};
