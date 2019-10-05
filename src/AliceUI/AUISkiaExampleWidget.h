#pragma once

#include "AUIDrawableWidget.h"


class ALICEUI_API AUISkiaExampleWidget : public AUIDrawableWidget
{
    using SuperWidget = AUIDrawableWidget;
public:
    AUISkiaExampleWidget();
    ~AUISkiaExampleWidget() override;


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Mouse event
protected:
    bool OnMouseMove(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseWheel(AUIMouseEvent::EventFlag flag, float delta) override;
    bool OnMouseMBtnDown(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseMBtnUp(AUIMouseEvent::EventFlag flag) override;


private:
    float m_fPrevMDownPosX = 0.0f;
    float m_fPrevMDownPosY = 0.0f;
    float m_fBaseScaleX = 1.0f;
    float m_fBaseScaleY = 1.0f;
    float m_fBaseTransX = 0.0f;
    float m_fBaseTransY = 0.0f;
};
