#pragma once

#include "AUIRectShape.h"

class ALICEUI_API AUIRoundRectShape : public AUIShape
{
public:
    AUIRoundRectShape();
    AUIRoundRectShape(const float radii[8]);
    AUIRoundRectShape(const SkVector radii[4]);
    ~AUIRoundRectShape() override;


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas, const SkPaint& paint) override;


    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    void OnResize(float width, float height) override;


    //////////////////////////////////////////////////////////////////////////
    // Rect
protected:
    SkRRect& RefRRect() noexcept {
        return m_RRect;
    }
    const SkRRect& RefRRect() const noexcept {
        return m_RRect;
    }
    
private:
    SkRRect m_RRect;
};
