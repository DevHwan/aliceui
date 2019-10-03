#pragma once

#include "AUITextWidget.h"

class ALICEUI_API AUIButtonWidget : public AUITextWidget
{
    typedef AUITextWidget SuperWidget;
public:
    AUIButtonWidget();
    explicit AUIButtonWidget(const std::wstring& caption);
    virtual ~AUIButtonWidget();

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
