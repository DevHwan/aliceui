#pragma once

#include "AUICommonDef.h"
#include "AUISignal.h"

class AUIWidgetManager;
class AUIWidget;

class ALICEUI_API AUIPopup
{
public:
    AUIPopup();
    virtual ~AUIPopup();


    //////////////////////////////////////////////////////////////////////////
    // Popup Widget
public:
    void SetPopupWidget(const std::shared_ptr< AUIWidget >& pWidget);


    //////////////////////////////////////////////////////////////////////////
    // Popup Position
public:
    void SetPopupPosition(const glm::vec3& pos) { m_v3PopupPos = pos; }
    glm::vec3 GetPopupPosition() const { return m_v3PopupPos; }


    //////////////////////////////////////////////////////////////////////////
    // Invoke / Dismiss
public:
    bool IsInvoked() const;
    bool Invoke(AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pParent, const AUIPopupPos& opt);
    bool Invoke(AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pParent) {
        return Invoke(pWidgetManager, pParent, AUIPopupPos::kUnchanged);
    }
    bool Invoke(AUIWidgetManager* const pWidgetManager) { return Invoke(pWidgetManager, nullptr, AUIPopupPos::kUnchanged); }
    void Dismiss();
    
    // Signals
public:
    AUISignal<void(void)> InvokeSignal;
    AUISignal<void(void)> DismissSignal;

private:
    std::shared_ptr<AUIWidget> m_pPopupWidget;
    std::weak_ptr<AUIWidget> m_wpParent;
    AUIWidgetManager* m_pWidgetManager = nullptr;
    glm::vec3 m_v3PopupPos = glm::vec3(0.0f, 0.0f, 0.0f);
};
