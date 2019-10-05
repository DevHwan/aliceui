#pragma once

#include "AUIDrawable.h"
#include "AUIRulerDrawableDef.h"

class ALICEUI_API AUIRulerDrawable : public AUIDrawable
{
public:
    AUIRulerDrawable();
    ~AUIRulerDrawable() override;

    //////////////////////////////////////////////////////////////////////////
    // Location
public:
    void SetLocation(const AUIRulerLocation location) noexcept {
        m_Location = location;
    }
    AUIRulerLocation GetLocation() const noexcept {
        return m_Location;
    }


    //////////////////////////////////////////////////////////////////////////
    // Reference Position
public:
    void SetRefPos(const SkScalar pos) noexcept {
        m_RefPos = pos;
    }
    SkScalar GetRefPos() const noexcept {
        return m_RefPos;
    }


    //////////////////////////////////////////////////////////////////////////
    // Paint
public:
    SkPaint& RefLinePaint() noexcept {
        return m_LinePaint;
    }
    SkPaint& RefTextPaint() noexcept {
        return m_TextPaint;
    }


    //////////////////////////////////////////////////////////////////////////
    // Basis & Scale
public:
    void SetScale(SkScalar val) noexcept {
        m_Scale = val;
    }
    void SetBasis(SkScalar val) noexcept {
        m_Basis = val;
    }
    void SetGradationSize(SkScalar val) noexcept {
        m_GradationSize = val;
    }
    SkScalar GetScale() const noexcept {
        return m_Scale;
    }
    SkScalar GetBasis() const noexcept {
        return m_Basis;
    }
    SkScalar GetGradationSize() const noexcept {
        return m_GradationSize;
    }


    //////////////////////////////////////////////////////////////////////////
    // Text
public:
    void SetMaxTextWidth(SkScalar val) noexcept {
        m_MaxTextWidth = val;
    }
    void SetMaxTextHeight(SkScalar val) noexcept {
        m_MaxTextHeight = val;
    }
    SkScalar GetMaxTextWidth() const noexcept {
        return m_MaxTextWidth;
    }
    SkScalar GetMaxTextHeight() const noexcept {
        return m_MaxTextHeight;
    }


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;
    void OnDrawLeft(SkCanvas* const canvas);
    void OnDrawTop(SkCanvas* const canvas);
    void OnDrawRight(SkCanvas* const canvas);
    void OnDrawBottom(SkCanvas* const canvas);


    // Marking
public:
    void SetUseMarking(bool val) noexcept {
        m_UseMarking = val;
    }
    bool IsUseMarking() const noexcept {
        return m_UseMarking;
    }
    
    
    
private:
    AUIRulerLocation m_Location = AUIRulerLocation::kTop;
    SkScalar m_Scale = 1.0f;
    SkScalar m_Basis = 1.0f;
    SkScalar m_GradationSize = 5.0f;
    SkScalar m_RefPos = 0.0f;
    SkScalar m_MaxTextWidth = 30.0f;
    SkScalar m_MaxTextHeight = 15.0f;
    SkPaint m_LinePaint;
    SkPaint m_TextPaint;
    bool m_UseMarking = true;
};
