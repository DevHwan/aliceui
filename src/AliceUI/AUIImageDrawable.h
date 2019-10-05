#pragma once

#include "AUIDrawable.h"

class ALICEUI_API AUIImageDrawable : public AUIDrawable
{
public:
    AUIImageDrawable();
    AUIImageDrawable(const sk_sp<SkImage>& image, const AUIImageStretch stretch);
    ~AUIImageDrawable() override = default;


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;

    //////////////////////////////////////////////////////////////////////////
    // Load
public:
    bool LoadBitmapFromPath(const std::wstring& absolutepath);
    bool LoadBitmapFromPath(const std::string& absolutepath);


    //////////////////////////////////////////////////////////////////////////
    // Image stretch
public:
    void SetImageStretch(AUIImageStretch stretch) { m_eImageStretch = stretch; }
    AUIImageStretch GetImageStretch() const { return m_eImageStretch; }


    //////////////////////////////////////////////////////////////////////////
    // Opacity
public:
    void SetOpacity(SkAlpha val) { m_Opacity = val; }
    SkAlpha GetOpacity() const { return m_Opacity; }


    //////////////////////////////////////////////////////////////////////////
    // Image
public:
    void SetImage(const SkBitmap& bitmap) {
        SetImage(SkImage::MakeFromBitmap(bitmap));
    }
    void SetImage(const sk_sp<SkImage>& image);
    sk_sp<SkImage> GetImage() const { return m_pImage; }


private:
    AUIImageStretch m_eImageStretch = AUIImageStretch::kUniform;
    sk_sp<SkImage> m_pImage;
    SkAlpha m_Opacity = kAUIAlpha100;
};
