#pragma once

#include "AUIFrameLayoutWidget.h"
#include "AUIPopup.h"

class AUIComboAdapter;
class AUIComboPopupWidget;

class ALICEUI_API AUIComboWidget : public AUIFrameLayoutWidget, public AUIPopup
{
    using SuperWidget = AUIFrameLayoutWidget;
public:
    AUIComboWidget();
    ~AUIComboWidget() override = default;


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Event
protected:
    virtual void OnMouseEnter() override;
    virtual void OnMouseHover() override;
    virtual void OnMouseLeave() override;
    virtual bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override;

protected:
    void OnDestroy() override;

    //////////////////////////////////////////////////////////////////////////
    // Combo adapter
public:
    void SetAdapter(const std::shared_ptr< AUIComboAdapter >& pAdapter);
    std::shared_ptr< AUIComboAdapter > GetAdapter() const;
protected:
    virtual void OnAdapterDataChanged(AUIComboAdapter*);

    //////////////////////////////////////////////////////////////////////////
    // Public child interface
public:
    virtual void AddSubWidgetAt(const std::shared_ptr< AUIWidget >& widget, const size_t pos) override { AUIAssert(!"Public interface Unsupported!"); }
    virtual void DelSubWidget(const std::shared_ptr< AUIWidget >& widget) override { AUIAssert(!"Public interface Unsupported!"); }
    virtual void PopSubWidget() override { AUIAssert(!"Public interface Unsupported!"); }
    virtual void ClearSubWidget() override { AUIAssert(!"Public interface Unsupported!"); }
    virtual std::shared_ptr< AUIWidget > FindSubWidget(size_t pos) override { AUIAssert(!"Public interface Unsupported!"); return nullptr; }
    virtual size_t SubWidgetCount() const override { AUIAssert(!"Public interface Unsupported!"); return 0; }

    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    virtual void OnSetDefaultSize(const AUIScalar2& size) override;
    virtual void OnAfterMeasureSize(SkScalar width, SkScalar height) override;


    //////////////////////////////////////////////////////////////////////////
    // Combo click
public:
    size_t GetCurPos() const noexcept {
        return m_curPos;
    }
    void SetCurPos(size_t pos);
    static size_t InvalidPos;
protected:
    virtual void OnClickPopup(AUIComboWidget*);
    virtual void OnItemClicked(AUIComboAdapter*, size_t pos);
    virtual void OnPopupFocusLost();
private:
    void RefreshLabel();


    //////////////////////////////////////////////////////////////////////////
    // Combo Popup
public:
    void SetPopupMaxHeight(SkScalar val) {
        m_PopupMaxHeight = val;
    }
    SkScalar GetPopupMaxHeight() const noexcept {
        return m_PopupMaxHeight;
    }
    void SetUseMarquee(bool val);
    bool IsUseMarquee() const;
    bool IsUsePopupHitRect() const noexcept {
        return m_bUsePopuptHitRect;
    }
    void SetUsePopupHitRect(bool state) {
        m_bUsePopuptHitRect = state;
    }
    void SetPopupHitRect(const SkRect& rect) {
        m_PopupHitRect = rect;
    }
    void SetPopupOpt(const AUIPopupPos opt) {
        m_PopupOpt = opt;
    }
    AUIPopupPos GetPopupOpt() const noexcept {
        return m_PopupOpt;
    }
protected:
    void SetLabel(const std::shared_ptr< AUIWidget >& pLabel);
    std::shared_ptr< AUIWidget > GetLabel() const { return m_pLabel.lock(); }
    
    // Signals
public:
    AUISignal<void(AUIComboWidget*)> ComboClickSignal;     // Only if UsePopupHitRect
    AUISignal<void(AUIComboWidget*)> ComboPopupSignal;     // Popup invoke callback
    
private:
    std::shared_ptr<AUIComboPopupWidget> m_pPopup;
    std::shared_ptr<AUIDrawable> m_pArrowDrawable;
    std::weak_ptr<AUIWidget> m_pLabel;
    SkScalar m_PopupMaxHeight = -1.0f;
    SkRect m_PopupHitRect = SkRect::MakeEmpty();
    bool m_bUsePopuptHitRect = false;
    AUIPopupPos m_PopupOpt = AUIPopupPos::kOptimal;
    AUISlotPool m_spoolDataChange;
    AUISlotPool m_spoolItemClick;
    size_t m_curPos = InvalidPos;
};
