#pragma once

#include "AUIHandle.h"

class ALICEUI_API AUIWin32Handle : public AUIHandle
{
    using SuperClass = AUIHandle;
public:
    AUIWin32Handle(HWND hWnd) noexcept;
    ~AUIWin32Handle() noexcept override = default;


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
private:
    void ActivateHWND(AUIHandle* const pParent);


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
private:
    bool MakeTransparent();

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
    struct ModalLooper
    {
        bool fDone = false;
        int fResult = 0;
        int RunModalLoop(HWND hWnd, HWND hParentWnd);
        void EndModalLoop(HWND hWnd, int nResult);
    };
    ModalLooper m_ModalLooper;

    //////////////////////////////////////////////////////////////////////////
    // MUIWnd
public:
    void SetWndClassName(const std::wstring& wndclassname) {
        m_strWndClassName = wndclassname;
    }
    HWND GetHWND() const { return m_hWnd; }
protected:
    std::wstring m_strWndClassName;
private:
    HWND m_hWnd = nullptr;
};
