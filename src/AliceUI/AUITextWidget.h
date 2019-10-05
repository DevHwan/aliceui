#pragma once

#include "AUIDrawableWidget.h"

class ALICEUI_API AUITextWidget : public AUIDrawableWidget
{
    using SuperWidget = AUIDrawableWidget;
public:
    AUITextWidget();
    AUITextWidget(const std::wstring& caption);
    ~AUITextWidget() override;

	//////////////////////////////////////////////////////////////////////////
	// Create & Destroy
public:
	void OnDestroy() override;

    //////////////////////////////////////////////////////////////////////////
    // Caption parameter
public:
    void SetCaption(const std::wstring& text);
    void SetCaptionHorzAlign(AUITextHorzAlign align);
    void SetCaptionVertAlign(AUITextVertAlign align);
    void SetCaptionColor(const SkColor color);
    void SetCaptionColor(AUIState::Index idx, bool state, const SkColor color);
    void ResetCaptionColor(const SkColor defaultColor) {
        m_mapTrueStateCaptionColor.clear();
        m_mapFalseStateCaptionColor.clear();
        SetCaptionColor(defaultColor);
    }
    std::wstring GetCaption() const;
    AUITextHorzAlign GetCaptionHorzAlign() const;
    AUITextVertAlign GetCaptionVertAlign() const;
    SkColor GetCaptionColor() const;
    SkColor GetCaptionColor(AUIState::Index idx, bool state) const;
protected:
    virtual std::wstring OnSetCaption(const std::wstring& text) {
        return text;
    }
    virtual std::wstring OnGetCaption(const std::wstring& text) const {
        return text;
    }

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;
    virtual void OnDrawCaption(SkCanvas* const canvas);
    void OnDrawCaption_SingleLine(SkCanvas* const canvas);
    void OnDrawCaption_Multiline(SkCanvas* const canvas);

    //////////////////////////////////////////////////////////////////////////
    // Style Sheet
protected:
    void OnSetStyleNotion(unsigned int uiKey, const AUIStyleNotionValue& value) override;


    //////////////////////////////////////////////////////////////////////////
    // Drawable
public:
    void SetBackgroundDrawable(const std::shared_ptr< AUIDrawable >& pDrawable) override;
private:
    enum DrawableLayer {
        BackgroundLayer = 0,
    };


    //////////////////////////////////////////////////////////////////////////
    // Measure
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;


    //////////////////////////////////////////////////////////////////////////
    // Draw helper function
protected:
    virtual SkRect GetCaptionAreaRect() const;
    void GetCaptionPaint(SkPaint& paint) const;


    //////////////////////////////////////////////////////////////////////////
    // Caption parameter
public:
    void SetCaptionAntialias(bool state) {
        m_bCaptionAA = state;
        InvalidateCaption();
    }
    void SetCaptionSize(SkScalar size) {
        m_fCaptionSize = size;
        InvalidateCaption();
    }
    void SetCaptionStyle(const SkFontStyle style) {
        m_captionStyle = style;
        InvalidateCaption();
    }
    void SetCaptionFontName(const std::wstring& name) {
        m_captionFontName = name;
        InvalidateCaption();
    }
    bool GetCaptionAntialias() const noexcept {
        return m_bCaptionAA;
    }
    SkScalar GetCaptionSize() const noexcept {
        return m_fCaptionSize;
    }
    SkFontStyle GetCaptionStyle() const noexcept {
        return m_captionStyle;
    }
    std::wstring GetCaptionFontName() const noexcept {
        return m_captionFontName;
    }
    void InvalidateCaption();
private:
    bool HasTrueStateColor(AUIState::Index idx) const;
    bool HasFalseStateColor(AUIState::Index idx) const;


    //////////////////////////////////////////////////////////////////////////
    // Multi-Line
public:
    void SetMinLines(int line);
    int GetMinLines() const noexcept {
        return m_iMinLines;
    }
    void SetMaxLines(int line);
    int GetMaxLines() const noexcept {
        return m_iMaxLines;
    }
    void SetLines(int line);
    int GetLines() const noexcept {
        return m_iLines;
    }
    void SetUseMultiline(bool val) {
        m_bUseMultiline = val;
        InvalidateCaption();
    }
    bool IsUseMultiline() const noexcept {
        return m_bUseMultiline;
    }
    void SetMultilineType(const AUITextLineFeed& type) {
        m_MultilineType = type;
        InvalidateCaption();
    }
    AUITextLineFeed GetMultilineType() const noexcept {
        return m_MultilineType;
    }
    void SetLineHeight(const SkScalar lineHeight) {
        m_LineHeight = lineHeight;
        InvalidateCaption();
    }
    SkScalar GetLineHeight() const noexcept {
        return m_LineHeight;
    }
protected:
    void MeasureCaption(AUIScalar2& out, SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec);

    
    
private:
    std::wstring m_Caption;
    std::vector<std::wstring> m_MeasuredCaption;
    std::shared_ptr<AUIDrawable> m_pBackgroundDrawable;
    // Cpation styles
    SkFontStyle m_captionStyle;
    std::wstring m_captionFontName;
    std::unordered_map<AUIState::Index, SkColor> m_mapTrueStateCaptionColor;
    std::unordered_map<AUIState::Index, SkColor> m_mapFalseStateCaptionColor;
    SkScalar m_fCaptionSize = 13.0f;
    bool m_bCaptionAA = true;
    // Line style
    AUITextLineFeed m_MultilineType = AUITextLineFeed::kNewline;
    int m_iLines = 0;
    int m_iMinLines = 1;
    int m_iMaxLines = (std::numeric_limits<int>::max)();
    SkScalar m_LineHeight = 0.0f;
    bool m_bUseMultiline = false;
};
