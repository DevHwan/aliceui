#pragma once

#include "AUIDrawableWidget.h"

class ALICEUI_API AUISeparatorWidget : public AUIDrawableWidget
{
    typedef AUIDrawableWidget SuperWidget;
public:
    AUISeparatorWidget();
    explicit AUISeparatorWidget(bool horizontal);
    ~AUISeparatorWidget() override;

    //////////////////////////////////////////////////////////////////////////
    // Mode
public:
    bool IsHorizontal() const noexcept {
        return m_bHorizontal;
    }

    //////////////////////////////////////////////////////////////////////////
    // Cursor Icon
public:
    bool OnChangeCursorIcon(AUICursorIcon& cursoricon) override;


    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    bool OnMouseLBtnDown(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override;


    //////////////////////////////////////////////////////////////////////////
    // Move state
protected:
    bool OnDragging() override;


    //////////////////////////////////////////////////////////////////////////
    // Mode
public:
    void SetHorizontal(bool state);
    void SetColor(const SkColor color);

    //////////////////////////////////////////////////////////////////////////
    // Dragging signal
public:
    AUISignal<void(AUIWidget*)> DragPressSignal;
    AUISignal<void(AUIWidget*)> DragReleaseSignal;
    AUISignal<void(AUIWidget*, float, float)> DragMoveSignal;
    
private:
    float m_fAbsPrevX = 0.0f;
    float m_fAbsPrevY = 0.0f;
    bool m_bHorizontal = false;
};
