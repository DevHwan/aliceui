#pragma once

#include "AUITextWidget.h"

class ALICEUI_API AUITitleBarTitleWidget : public AUITextWidget
{
    typedef AUITextWidget SuperWidget;
public:
    AUITitleBarTitleWidget();
    AUITitleBarTitleWidget(const std::wstring& caption);
    virtual ~AUITitleBarTitleWidget();


    //////////////////////////////////////////////////////////////////////////
    // Cursor Icon
protected:
    virtual bool OnChangeCursorIcon(AUICursorIcon& cursoricon) override;


    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    virtual bool OnMouseLBtnDown(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnDblClk(AUIMouseEvent::EventFlag flag) override;
    //////////////////////////////////////////////////////////////////////////
    // Move state
protected:
    virtual bool OnDragging() override;
private:
    float m_fAbsPrevX;
    float m_fAbsPrevY;

    //////////////////////////////////////////////////////////////////////////
    // DblClick signal
public:
    AUISignal<void(AUIWidget*)> TitleBarDblClickSignal;

    //////////////////////////////////////////////////////////////////////////
    // Dragging signal
public:
    AUISignal<void(AUIWidget*)> DragPressSignal;
    AUISignal<void(AUIWidget*)> DragReleaseSignal;
    AUISignal<void(AUIWidget*, float, float)> DragMoveSignal;
};
