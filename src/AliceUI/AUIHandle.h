#pragma once

#include "AUICommonDef.h"

class AUIWidget;

class ALICEUI_API AUIHandle : public std::enable_shared_from_this<AUIHandle>
{
public:
    AUIHandle() noexcept;
    virtual ~AUIHandle() noexcept = default;


    //////////////////////////////////////////////////////////////////////////
    // Typecast helper
public:
    template<typename _Derived>
    bool IsKindOf() const {
        static_assert(std::is_base_of<AUIHandle, _Derived>::value, "Must be derived from AUIWidget");
        return (nullptr != dynamic_cast<const _Derived*>(this));
    }
    template<typename _Derived>
    _Derived* Cast() const {
        AUIAssert(this->IsKindOf<_Derived>());
        return static_cast<_Derived*>(const_cast<AUIHandle*>(this));
    }
    template<typename _Derived>
    _Derived* DynCast() const {
        return dynamic_cast<_Derived*>(const_cast<AUIHandle*>(this));
    }


    //////////////////////////////////////////////////////////////////////////
    // Option
public:
    bool IsNonActivate() const { return m_bNonActivate; }
    void SetNonActivate(bool val) { m_bNonActivate = val; }
    bool IsTopMost() const { return m_bTopMost; }
    void SetTopMost(bool val) { m_bTopMost = val; }



    //////////////////////////////////////////////////////////////////////////
    // Widget
public:
    virtual void SetRootWidget(const std::shared_ptr< AUIWidget >& pWidget);
    virtual std::shared_ptr< AUIWidget > GetWidget() const;


    //////////////////////////////////////////////////////////////////////////
    // Title
public:
    virtual void SetTitle(const std::wstring& title);
    virtual std::wstring GetTitle() const;

    //////////////////////////////////////////////////////////////////////////
    // Mode
public:
    virtual void SetMode(AUIHandleMode mode);
    virtual AUIHandleMode GetMode() const;


    //////////////////////////////////////////////////////////////////////////
    // Activate / Deactivate
public:
    void Activate() {
        Activate(nullptr);
    }
    virtual void Activate(AUIHandle* const pParent);
    virtual void Deactivate();
    virtual bool IsActivated() const;
    virtual void DoShowMinimized();
    virtual void DoShowMaximized();
    virtual void DoShowDefault();
    void ActivateModal() {
        ActivateModal(nullptr);
    }
    virtual void ActivateModal(AUIHandle* const pHandle);
    bool IsActivatedAsModal() const {
        return m_bActivatedAsModal;
    }


    //////////////////////////////////////////////////////////////////////////
    // Invalidate
public:
    virtual void Invalidate();
    virtual void UpdateWindow();

    //////////////////////////////////////////////////////////////////////////
    // Visible
public:
    virtual void SetVisible(bool state);

    //////////////////////////////////////////////////////////////////////////
    // Focus
public:
    virtual void SetFocus();

    //////////////////////////////////////////////////////////////////////////
    // State
public:
    virtual bool IsZoomed() const { return false; }
    virtual bool IsIconic() const { return false; }

    //////////////////////////////////////////////////////////////////////////
    // Mouse Event Capture
public:
    virtual void CaptureMouseEvent();
    virtual void ReleaseMouseEvent();


    //////////////////////////////////////////////////////////////////////////
    // Opacity
public:
    virtual void SetOpacity(const SkAlpha opacity);
    virtual SkAlpha GetOpacity() const;


    //////////////////////////////////////////////////////////////////////////
    // Size / Position
public:
    virtual void SetResizeable(bool val);
    virtual bool IsResizeable() const;
    virtual void SetSize(int width, int height);
    virtual void SetPosition(int x, int y);
    virtual void SetPositionAndSize(int x, int y, int width, int height);
    virtual void SetMinSize(int width, int height);
    virtual void SetMaxSize(int width, int height);
    virtual void GetSize(int& width, int& height);
    virtual void GetPosition(int& x, int& y);
    virtual void GetPositionAndSize(int& x, int& y, int& width, int& height);
    virtual void GetMinSize(int& width, int& height);
    virtual void GetMaxSize(int& width, int& height);
    static constexpr int kNoMinMaxSizeValue = -1;



    //////////////////////////////////////////////////////////////////////////
    // Modal Loop
public:
    virtual void BeginModal();
    virtual void EndModal(int result);




    //////////////////////////////////////////////////////////////////////////
    // Transparency
public:
    virtual void SetTransparent(bool val) {};
    virtual bool IsTransparent() const { return false; };
    
    

protected:
    std::shared_ptr<AUIWidget> m_pWidget;
    std::wstring m_strTitle;
    AUIHandleMode m_Mode = AUIHandleMode::kPopup;
    // Activate
    bool m_bNonActivate = false;
    bool m_bActivated = false;
    bool m_bActivatedAsModal = false;
    // Visibility
    SkAlpha m_Opacity = kAUIAlpha100;
    bool m_bVisible = true;
    // UI state
    bool m_bTopMost = false;
    bool m_bMouseCaptured = false;
    // Window size
    int m_iX = 0;
    int m_iY = 0;
    int m_iWidth = 0;
    int m_iHeight = 0;
    int m_MinWidth = kNoMinMaxSizeValue;
    int m_MinHeight = kNoMinMaxSizeValue;
    int m_MaxWidth = kNoMinMaxSizeValue;
    int m_MaxHeight = kNoMinMaxSizeValue;
    bool m_Resizeable = false;
};
