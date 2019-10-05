#pragma once

#include "AUIDrawable.h"
#include "AUINinePatch.h"


class ALICEUI_API AUINinePatchDrawable : public AUIDrawable
{
public:
    AUINinePatchDrawable();
    AUINinePatchDrawable(const AUINinePatch& ninepatch);
    ~AUINinePatchDrawable() override;

    //////////////////////////////////////////////////////////////////////////
    // Helper
public:
    static std::shared_ptr<AUINinePatchDrawable> CreateFromResourcePath(const std::wstring& path);

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;

private:
    AUINinePatch m_NinePatch;
};
