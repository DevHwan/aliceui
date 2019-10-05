#pragma once

#include "AUIFrameLayoutWidget.h"

class ALICEUI_API AUITransitionWidget : public AUIFrameLayoutWidget
{
    using SuperWidget = AUIFrameLayoutWidget;
public:
    AUITransitionWidget();
    ~AUITransitionWidget() override;


    //////////////////////////////////////////////////////////////////////////
    // Transition
public:
    void ReplaceWidget(const std::shared_ptr<AUIWidget>& pWidget, bool animate = true);
    std::shared_ptr<AUIWidget> GetCurrentWidget() const {
        return m_pCurrentWidget;
    }
private:
    void BeforeTransition(const std::shared_ptr<AUIWidget>& pFromWidget, const std::shared_ptr<AUIWidget>& pToWidget);
    void AfterTransition(const std::shared_ptr<AUIWidget>& pFromWidget, const std::shared_ptr<AUIWidget>& pToWidget);

    //////////////////////////////////////////////////////////////////////////
    // Transition state
public:
    bool IsInTransition() const { return m_bInTransition; }
    void StartTransition(const std::shared_ptr< AUIWidget >& pFromWidget, const std::shared_ptr< AUIWidget >& pToWidget, bool animate);
    void EndTransition();

    //////////////////////////////////////////////////////////////////////////
    // Time tick
protected:
    virtual void OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime) override;

    
private:
    std::shared_ptr<AUIWidget> m_pCurrentWidget;
    std::shared_ptr<AUIWidget> m_pFromWidget;
    std::shared_ptr<AUIWidget> m_pToWidget;
    float m_fFromTargetOpacity = 1.0f;
    float m_fToTargetOpacity = 1.0f;
    bool m_bInTransition = false;
    bool m_bFromFreezed = false;
    bool m_bToFreezed = false;
};
