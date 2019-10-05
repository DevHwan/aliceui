#pragma once

#include "AUIShape.h"

class ALICEUI_API AUIRectShape : public AUIShape
{
public:
    AUIRectShape();
    ~AUIRectShape() override;


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
    SkRect& RefRect() noexcept {
        return m_Rect;
    }
    const SkRect& RefRect() const noexcept {
        return m_Rect;
    }
private:
    SkRect m_Rect;
};
