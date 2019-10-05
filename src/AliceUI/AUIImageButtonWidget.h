#pragma once

#include "AUIImageWidget.h"

class ALICEUI_API AUIImageButtonWidget : public AUIImageWidget
{
    using SuperWidget = AUIImageWidget;
public:
    AUIImageButtonWidget();
    ~AUIImageButtonWidget() override;



    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    void OnMouseEnter() override;
    void OnMouseLeave() override;
    bool OnMouseLBtnDown(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseLBtnDblClk(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseMove(AUIMouseEvent::EventFlag flag) override;
};
