#pragma once

#include "AUIButtonWidget.h"
#include "AUICalendarFrameWidget.h"
#include "AUIPopup.h"

class AUICalendarFrameWidget;
class ALICEUI_API AUICalendarFoldButton : public AUIButtonWidget, public AUIPopup
{
public:
    AUICalendarFoldButton() noexcept;
    ~AUICalendarFoldButton() override = default;
    void SetDate(const std::wstring& tempDate) { m_Date = tempDate; SetCaption(m_Date); }
    void SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay);
    void SetFocus(const int& iYear, const int& iMonth);

protected:
    virtual bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override;
private:
    void OnUserEvent(AUICalendarFrameWidget*);
    void FoldCalendar();
    ////////////////////////////////////////////////////////////////////////////////////////////////
public:
    AUISignal<void(const int, const int, const int) > UserEventSignal;

private:
    std::shared_ptr<AUICalendarFrameWidget> m_pCalendar;
    bool m_bFold = true;
    std::wstring m_Date = L"Calendar";
};
