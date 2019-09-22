#pragma once

#include "AUIHandle.h"

class ALICEUI_API AUIDarwinHandle : public AUIHandle
{
    using SuperClass = AUIHandle;
public:
    AUIDarwinHandle(void* native) noexcept;
    ~AUIDarwinHandle() noexcept override = default;
    
    
    //////////////////////////////////////////////////////////////////////////
    // Title
public:
    void SetTitle(const std::wstring& title) override;
    
    
    //////////////////////////////////////////////////////////////////////////
    // Activate / Deactivate
public:
    void Activate(AUIHandle* const pParent) override;
    void ActivateModal(AUIHandle* const pParent) override;
    void Deactivate() override;
    bool IsActivated() const override;
    void DoShowMinimized() override;
    void DoShowMaximized() override;
    void DoShowDefault() override;
    
    
    //////////////////////////////////////////////////////////////////////////
    // Invalidate
public:
    void Invalidate() override;
    void UpdateWindow() override;
    
    //////////////////////////////////////////////////////////////////////////
    // Visible
public:
    void SetVisible(bool state) override;
    
    //////////////////////////////////////////////////////////////////////////
    // Focus
public:
    void SetFocus() override;
    
    
    //////////////////////////////////////////////////////////////////////////
    // Mouse Event Capture
public:
    void CaptureMouseEvent() override;
    void ReleaseMouseEvent() override;
    
    
    //////////////////////////////////////////////////////////////////////////
    // Opacity
public:
    void SetOpacity(const SkAlpha alpha) override;
    
    //////////////////////////////////////////////////////////////////////////
    // State
public:
    bool IsZoomed() const override;
    bool IsIconic() const override;
    
    //////////////////////////////////////////////////////////////////////////
    // Size / Position
public:
    void SetResizeable(bool val) override;
    bool IsResizeable() const override;
    void SetSize(int width, int height) override;
    void SetPosition(int x, int y) override;
    void SetPositionAndSize(int x, int y, int sx, int sy) override;
    void GetSize(int& width, int& height) override;
    void GetPosition(int& x, int& y) override;
    void GetPositionAndSize(int& x, int& y, int& sx, int& sy) override;
private:
    bool m_bUseDefaultPos = true;
    
    
    //////////////////////////////////////////////////////////////////////////
    // Modal Loop
public:
    void BeginModal() override;
    void EndModal(int result) override;
    
private:
    void* fNative = nullptr;
};
