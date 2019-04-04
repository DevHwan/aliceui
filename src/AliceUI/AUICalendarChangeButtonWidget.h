#pragma once

#include "AUIButtonWidget.h"

class ALICEUI_API AUICalendarChangeButtonWidget : public AUIButtonWidget
{
    // function
public:
    AUICalendarChangeButtonWidget(const bool& direction);
    ~AUICalendarChangeButtonWidget() override = default;
protected:

private:

    // variable
public:
private:
    bool m_Direction;
};
