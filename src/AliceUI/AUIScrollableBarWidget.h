#pragma once

#include "AUIDrawableWidget.h"

class ALICEUI_API AUIScrollableBarWidget : public AUIDrawableWidget
{
    using SuperWidget = AUIDrawableWidget;
public:
    AUIScrollableBarWidget();
    ~AUIScrollableBarWidget() override;


    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    void OnMouseEnter() override;
    void OnMouseHover() override;
    void OnMouseLeave() override;
    bool OnMouseLBtnDblClk(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseRBtnDblClk(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseMBtnDblClk(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseLBtnDown(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseRBtnDown(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseMBtnDown(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseRBtnUp(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseMBtnUp(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseMove(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseWheel(AUIMouseEvent::EventFlag flag, float delta) override;
    bool OnChangeCursorIcon(AUICursorIcon& cursoricon) override;

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Values
public:
    void SetContentHeight(const SkScalar val) {
        m_ContentHeight = val;
    }
    void SetScrollPos(const SkScalar val) {
        m_ScrollPos = val;
    }
private:

    //////////////////////////////////////////////////////////////////////////
    // Thumb
public:
    void SetShowThumbOnHit(bool show) {
        m_bShowThumbOnHit = show;
    }
    bool IsShowThumbOnHit() const {
        return m_bShowThumbOnHit;
    }
    SkRect GetThumbRect() const;
    bool IsScrollable() const;
    
    
    // Signals
public:
    AUISignal<void(const SkScalar&)> ThumbScrollSignal;
    
    
private:
    std::shared_ptr<AUIDrawable> m_pThumbDrawable;
    SkScalar m_ContentHeight = 0.0f;
    SkScalar m_ScrollPos = 0.0f;
    AUIState m_ThumbState;
    SkPoint m_PrevLDownPos = { 0, 0 };
    bool m_bShowThumbOnHit = false;
};
