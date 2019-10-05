#pragma once

#include "AUILinearLayoutWidget.h"
#include "AUIImageWidget.h"


class AUITextWidget;
class ALICEUI_API AUIImageCaptionButtonWidget : public AUILinearLayoutWidget
{
    using SuperWidget = AUILinearLayoutWidget;
public:
    AUIImageCaptionButtonWidget();
    explicit AUIImageCaptionButtonWidget(bool horizontal);
    ~AUIImageCaptionButtonWidget() override;



    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    void OnMouseEnter() override;
    void OnMouseHover() override;
    void OnMouseLeave() override;
    bool OnMouseLBtnDown(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseLBtnDblClk(AUIMouseEvent::EventFlag flag) override;
    bool OnMouseMove(AUIMouseEvent::EventFlag flag) override;



    //////////////////////////////////////////////////////////////////////////
    // Image caption style
public:
    void SetImageCaptionStyle(AUIImageCaptionStyle style);
    AUIImageCaptionStyle GetImageCaptionStyle() const { return m_Style; }

    //////////////////////////////////////////////////////////////////////////
    // Size
public:
    void SetImageDefaultSize(float width, float height);
	void SetImageMarginLTRB(float marginLeft, float marginTop, float marginRight, float marginBottom);
protected:
    void OnSetDefaultSize(const AUIScalar2& size) override;
    void OnSetChecked(bool state) override;

    //////////////////////////////////////////////////////////////////////////
    // Caption
public:
    void SetCaption(const std::wstring& text);
    void SetCaptionHorzAlign(AUITextHorzAlign align);
    void SetCaptionVertAlign(AUITextVertAlign align);
    void SetCaptionSize(float size);
    void ResetCaptionColor(const SkColor color);
    void SetCaptionColor(const SkColor color);
    void SetCaptionColor(AUIState::Index idx, bool state, const SkColor color);
    void SetCaptionStyle(SkFontStyle style);
    void SetCaptionFontName(const std::wstring& name);
	void SetCaptionMarginLTRB(float marginLeft, float marginTop, float marginRight, float marginBottom);
    std::wstring GetCaption() const;
    AUITextHorzAlign GetCaptionHorzAlign() const;
    AUITextVertAlign GetCaptionVertAlign() const;
    float GetCaptionSize() const;
    SkColor GetCaptionColor() const;
    SkColor GetCaptionColor(AUIState::Index idx, bool state) const;
    SkFontStyle GetCaptionStyle() const;
    std::wstring GetCaptionFontName() const;
    AUITextWidget* const GetCaptionWidget() const { return m_pCaption.get(); }
    void SetUseMultiline(bool use);
    bool IsUseMultiline() const;
    void SetMultilineType(const AUITextLineFeed& type);
    AUITextLineFeed GetMultilineType() const;

    //////////////////////////////////////////////////////////////////////////
    // Image
public:
    void SetBitmap(const SkBitmap& bitmap) {
        SetImage(SkImage::MakeFromBitmap(bitmap));
    }
    void SetImage(const sk_sp<SkImage>& image);
    void SetImageDrawable(const std::shared_ptr< AUIDrawable >& pBitmap);
    sk_sp<SkImage> GetImage() const;
    AUIImageWidget* const GetImageWidget() const { return m_pImage.get(); }

    
private:
    AUIImageCaptionStyle m_Style = AUIImageCaptionStyle::kImageAndText;
    std::shared_ptr<AUITextWidget> m_pCaption;
    std::shared_ptr<AUIImageWidget> m_pImage;
};
