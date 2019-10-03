#pragma once

#include "AUIDrawableWidget.h"


class ALICEUI_API AUISkiaExampleWidget : public AUIDrawableWidget
{
    typedef AUIDrawableWidget SuperWidget;
public:
    AUISkiaExampleWidget();
    virtual ~AUISkiaExampleWidget();


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Mouse event
protected:
    virtual bool OnMouseMove(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseWheel(AUIMouseEvent::EventFlag flag, float delta) override;
    virtual bool OnMouseMBtnDown(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseMBtnUp(AUIMouseEvent::EventFlag flag) override;
private:
    float m_fPrevMDownPosX;
    float m_fPrevMDownPosY;


private:
    float m_fBaseScaleX;
    float m_fBaseScaleY;
    float m_fBaseTransX;
    float m_fBaseTransY;
};
