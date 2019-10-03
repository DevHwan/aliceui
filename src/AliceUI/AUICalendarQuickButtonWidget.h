#pragma once

#include "AUIButtonWidget.h"
#include "AUICalendarCommonDef.h"

class ALICEUI_API AUICalendarQuickButtonWidget : public AUIButtonWidget
{
    // function
public:
    AUICalendarQuickButtonWidget(const AUITableCriterion& criterion, const std::wstring& val);
    ~AUICalendarQuickButtonWidget() override = default;

    void DownCriterion(const AUITableCriterion& criterion);

protected:
    virtual bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override;

    // variable
public:
    AUISignal<void(const AUITableCriterion&)> BodyChangeUpSignal;
private:
    AUITableCriterion m_Criterion;
};
