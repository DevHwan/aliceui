#pragma once

#include "AUIFrameLayoutWidget.h"


class AUIScrollableContentWidget;
class AUIScrollableBarWidget;

class ALICEUI_API AUIScrollableWidget : public AUIFrameLayoutWidget
{
    typedef AUIFrameLayoutWidget SuperClass;
public:
    AUIScrollableWidget();
    ~AUIScrollableWidget() override;



    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;


    //////////////////////////////////////////////////////////////////////////
    // Public child interface
public:
    void AddSubWidgetAt(const std::shared_ptr<AUIWidget>& widget, const size_t pos) override;
    void DelSubWidget(const std::shared_ptr<AUIWidget>& widget) override;
    void PopSubWidget() override;
    void ClearSubWidget() override;
    std::shared_ptr<AUIWidget> FindSubWidget(size_t pos) override;
    size_t SubWidgetCount() const override;
protected:
    AUIScrollableContentWidget* const GetContent() const noexcept {
        return m_pContent.get();
    }


    //////////////////////////////////////////////////////////////////////////
    // ScrollBar
public:
    void SetShowThumbOnHit(bool show);
    bool IsShowThumbOnHit() const;
protected:
    AUIScrollableBarWidget* GetScrollBarWidget() const noexcept {
        return m_pScrollBar.get();
    }


    //////////////////////////////////////////////////////////////////////////
    // Scroll Info
public:
    bool IsHorizontal() const noexcept {
        return m_bHorizontal;
    }


    //////////////////////////////////////////////////////////////////////////
    // Inner Layout
public:
    enum ScrollBarPolicy
    {
        SBP_Auto,
        SBP_Show,
        SBP_Hide
    };
    ScrollBarPolicy GetScrollBarPolicy() const noexcept {
        return m_eScrollBarPolicy;
    }
protected:
    void OnSetDefaultSize(const AUIScalar2& size) override;


    //////////////////////////////////////////////////////////////////////////
    // Children
protected:
    void OnUpdateChildPosition() override;


    //////////////////////////////////////////////////////////////////////////
    // Scrolling
public:
    void ScrollToTop();
    void ScrollToBottom();
protected:
    virtual void OnContentScroll(AUIScrollableContentWidget* const pWidget, float delta);
    virtual void OnAfterMeasureSize(SkScalar width, SkScalar height) override;
private:
    void OnThumbScroll(const SkScalar& val);
    

    
private:
    std::shared_ptr<AUIScrollableContentWidget> m_pContent;
    std::shared_ptr< AUIScrollableBarWidget > m_pScrollBar;
    float m_fScrollPos = 0.0f;
    float m_fScrollOffset = 30.0f;
    ScrollBarPolicy m_eScrollBarPolicy = SBP_Show;
    bool m_bHorizontal = false;
    bool m_bPendingScrollToTop = false;
    bool m_bPendingScrolllToBottom = false;
};
