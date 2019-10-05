#pragma once
#include "AUIDrawable.h"

class AUIShape;

class ALICEUI_API AUIShapeDrawable : public AUIDrawable
{
public:
    AUIShapeDrawable();
    AUIShapeDrawable(const std::shared_ptr< AUIShape >& shape);
    ~AUIShapeDrawable() override;


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Shape
public:
    std::shared_ptr<AUIShape> GetShape() const {
        return m_pShape;
    }
    void SetShape(const std::shared_ptr<AUIShape>& shape) {
        m_pShape = shape;
    }

    //////////////////////////////////////////////////////////////////////////
    // Color
public:
    SkColor GetColor() const noexcept {
        return m_Color;
    }
    void SetColor(const SkColor color) {
        m_Color = color;
    }
private:


    //////////////////////////////////////////////////////////////////////////
    // Stroke Style
public:
    SkPaint::Style GetStrokeStyle() const noexcept {
        return m_StrokeStyle;
    }
    float GetStrokeWidth() const noexcept {
        return m_fStrokeWidth;
    }
    void SetStrokeStyle(const SkPaint::Style style) noexcept {
        m_StrokeStyle = style;
    }
    void SetStrokeWidth(const float val) noexcept {
        m_fStrokeWidth = val;
    }
    
    
private:
    std::shared_ptr<AUIShape> m_pShape;
    SkPaint::Style m_StrokeStyle = SkPaint::kFill_Style;
    SkColor m_Color = kAUIColorBlack;
    float m_fStrokeWidth = 1.0f;
};
