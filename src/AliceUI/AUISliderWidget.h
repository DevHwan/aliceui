#pragma once

#include "AUIAbsoluteLayoutWidget.h"


class AUISliderIndicatorWidget;
class ALICEUI_API AUISliderWidget : public AUIAbsoluteLayoutWidget
{
    using SuperWidget = AUIAbsoluteLayoutWidget;
public:
    AUISliderWidget();
    ~AUISliderWidget() override;

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;

    //////////////////////////////////////////////////////////////////////////
    // Mouse event
protected:
    bool OnMouseLBtnDown(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseMove(AUIMouseEvent::EventFlag flag) override;


    //////////////////////////////////////////////////////////////////////////
    // Horizontal
public:
    void SetHorizontal(bool val);
    bool IsHorizontal() const noexcept {
        return m_bHorizontal;
    }

    //////////////////////////////////////////////////////////////////////////
    // Range
public:
    void SetSlideRange(const SkScalar minVal, const SkScalar maxVal) noexcept {
        m_RangeMin = minVal;
        m_RangeMax = maxVal;
    }
    SkScalar GetSlideRangeMin() const noexcept {
        return m_RangeMin;
    }
    SkScalar GetSlideRangeMax() const noexcept {
        return m_RangeMax;
    }

    //////////////////////////////////////////////////////////////////////////
    // Value
public:
    void SetValue(SkScalar val);
    SkScalar GetValue() const;

    
private:
    std::shared_ptr<AUISliderIndicatorWidget> m_pIndicator;
    SkScalar m_RangeMin = 0.0f;
    SkScalar m_RangeMax = 1.0f;
    SkScalar m_Value = 0.0f;
    bool m_bHorizontal = false;
};
