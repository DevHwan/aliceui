#pragma once

#include "AUIWindow.h"
#include "AUICalendarChangeButtonWidget.h"
#include "AUICalendarQuickButtonWidget.h"
#include "AUICalendarBodyWidget.h"

class ALICEUI_API AUICalendarFrameWidget : public AUILinearLayoutWidget
{
    // function
public:
    AUICalendarFrameWidget() noexcept;
    ~AUICalendarFrameWidget() override = default;

    int32_t GetYear() { return m_Year; }
    int32_t GetMonth() { return static_cast<int32_t>(m_Month) + 1; }
    int32_t GetDay() { return m_Day; }
    void SetYear(int32_t tempYear) { m_Year = tempYear; }
    void SetMonth(int32_t tempMonth) { m_Month = static_cast<AUIMonths>(tempMonth - 1); }
    void SetDay(int32_t tempDay) { m_Day = tempDay; }
    void SetPeriod(const int& iStartYear, const int& iStartMonth, const int& iStartDay, const int& iEndYear, const int& iEndMonth, const int& iEndDay);
    void SetFocus(const int& iYear, const int& iMonth);

private:
    void SetTableData(const AUITableCriterion& criterion);
    void SetQuickCaption(const std::wstring& quickCaption) { m_Quick->SetCaption(quickCaption); }
    void OnClickUBtn(AUIWidget*);
    void OnClickDBtn(AUIWidget*);
    void OnClickDate(AUITableCriterion criterion, AUIMonthType tempType, int tempYear, int tempMonth, int tempDay);
    void OnClickQuickBtn(const AUITableCriterion& criterion);
    // variable
public:
    AUISignal<void(AUICalendarFrameWidget*)> UserEventSignal;

private:
    std::shared_ptr<AUICalendar> m_pPImpl;
    std::shared_ptr<AUILinearLayoutWidget> m_Header;
    std::shared_ptr<AUICalendarQuickButtonWidget> m_Quick;
    std::shared_ptr<AUICalendarBodyWidget> m_Body;
    std::shared_ptr<AUICalendarChangeButtonWidget> m_UBtn;
    std::shared_ptr<AUICalendarChangeButtonWidget> m_DBtn;

    int32_t m_Year;
    AUIMonths m_Month;
    int32_t m_Day;
    AUIDaysOfWeek m_FirstDayOfWeek; // 시작하는 요일
    int32_t m_MaximumOfMonth; // 그 달의 날짜 수
};
