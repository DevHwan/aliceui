#pragma once

#include "AUIDrawableWidget.h"

class ALICEUI_API AUIScrollableBarWidget : public AUIDrawableWidget
{
    typedef AUIDrawableWidget SuperClass;
public:
    AUIScrollableBarWidget();
    virtual ~AUIScrollableBarWidget();


    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    virtual void OnMouseEnter() override;
    virtual void OnMouseHover() override;
    virtual void OnMouseLeave() override;
    virtual bool OnMouseLBtnDblClk(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseRBtnDblClk(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseMBtnDblClk(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnDown(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseRBtnDown(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseMBtnDown(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseRBtnUp(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseMBtnUp(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseMove(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseWheel(AUIMouseEvent::EventFlag flag, float delta) override;
    virtual bool OnChangeCursorIcon(AUICursorIcon& cursoricon) override;

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Values
public:
    void SetContentHeight(const SkScalar& val) { m_ContentHeight = val; }
    void SetScrollPos(const SkScalar& val) { m_ScrollPos = val; }
private:
    SkScalar m_ContentHeight;
    SkScalar m_ScrollPos;
    std::shared_ptr< AUIDrawable > m_pThumbDrawable;

    //////////////////////////////////////////////////////////////////////////
    // Thumb
public:
    void SetShowThumbOnHit(bool show) { m_bShowThumbOnHit = show; }
    bool IsShowThumbOnHit() const { return m_bShowThumbOnHit; }
    SkRect GetThumbRect() const;
    AUISignal<void(const SkScalar&)> ThumbScrollSignal;
    bool IsScrollable() const;
private:
    AUIState m_ThumbState;
    SkPoint m_PrevLDownPos = { 0, 0 };
    bool m_bShowThumbOnHit;
};
