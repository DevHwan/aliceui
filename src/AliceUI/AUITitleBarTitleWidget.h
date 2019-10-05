#pragma once

#include "AUITextWidget.h"

class ALICEUI_API AUITitleBarTitleWidget : public AUITextWidget
{
    typedef AUITextWidget SuperWidget;
public:
    AUITitleBarTitleWidget();
    AUITitleBarTitleWidget(const std::wstring& caption);
    ~AUITitleBarTitleWidget() override;


    //////////////////////////////////////////////////////////////////////////
    // Cursor Icon
protected:
    bool OnChangeCursorIcon(AUICursorIcon& cursoricon) override;


    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    bool OnMouseLBtnDown(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseLBtnDblClk(AUIMouseEvent::EventFlag flag) override;
    //////////////////////////////////////////////////////////////////////////
    // Move state
protected:
    bool OnDragging() override;

    // signals
public:
    AUISignal<void(AUIWidget*)> TitleBarDblClickSignal;
    AUISignal<void(AUIWidget*)> DragPressSignal;
    AUISignal<void(AUIWidget*)> DragReleaseSignal;
    AUISignal<void(AUIWidget*, float, float)> DragMoveSignal;

private:
    float m_fAbsPrevX = -1.0f;
    float m_fAbsPrevY = -1.0f;
};
