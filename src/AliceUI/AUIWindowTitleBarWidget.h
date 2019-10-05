#pragma once

#include "AUIRelativeLayoutWidget.h"


class AUIImageWidget;
class AUITextWidget;
class AUIImageButtonWidget;
class ALICEUI_API AUIWindowTitleBarWidget : public AUIRelativeLayoutWidget
{
    using SuperWidget = AUIRelativeLayoutWidget;
public:
    AUIWindowTitleBarWidget();
    ~AUIWindowTitleBarWidget() override;



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
    // Dragging signal
public:
    AUISignal<void(AUIWidget*)> DragPressSignal;
    AUISignal<void(AUIWidget*)> DragReleaseSignal;
    AUISignal<void(AUIWidget*, float, float)> DragMoveSignal;

    //////////////////////////////////////////////////////////////////////////
    // Widgets
public:
    std::shared_ptr<AUIImageWidget> GetIconWidget() const {
        return m_pIcon;
    }
    std::shared_ptr<AUITextWidget> GetTitleTextWidget() const {
        return m_pTitleText;
    }
    std::shared_ptr<AUIImageButtonWidget> GetMinimizeButtonWidget() const {
        return m_pMinimizeButton;
    }
    std::shared_ptr<AUIImageButtonWidget> GetMaximizeButtonWidget() const {
        return m_pMaximizeButton;
    }
    std::shared_ptr<AUIImageButtonWidget> GetCloseButtonWidget() const {
        return m_pCloseButton;
    }
    
private:
    std::shared_ptr<AUIImageWidget> m_pIcon;
    std::shared_ptr<AUITextWidget> m_pTitleText;
    std::shared_ptr<AUIImageButtonWidget> m_pMinimizeButton;
    std::shared_ptr<AUIImageButtonWidget> m_pMaximizeButton;
    std::shared_ptr<AUIImageButtonWidget> m_pCloseButton;
    float m_fAbsPrevX = -1.0f;
    float m_fAbsPrevY = -1.0f;
};
