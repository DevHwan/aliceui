#pragma once

#include "AUILinearLayoutWidget.h"

class AUIWindowTitleBarWidget;

class ALICEUI_API AUIWindowWidget : public AUILinearLayoutWidget
{
    using SuperWidget = AUILinearLayoutWidget;
public:
    AUIWindowWidget();
    ~AUIWindowWidget() override;


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;

    //////////////////////////////////////////////////////////////////////////
    // Signals
public:
    AUISignal<void(AUIWidget*)>& GetTitleBarDblClickSignal() const;
    AUISignal<void(AUIWidget*)>& GetDragStartSignal() const;
    AUISignal<void(AUIWidget*)>& GetDragEndSignal() const;
    AUISignal<void(AUIWidget*, float, float)>& GetDraggingSignal() const;
    AUISignal<void(AUIWidget*)>& GetMinimizeSignal() const;
    AUISignal<void(AUIWidget*)>& GetMaximizeSignal() const;
    AUISignal<void(AUIWidget*)>& GetCloseSignal() const;

    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;

    //////////////////////////////////////////////////////////////////////////
    // Position
protected:
    void OnUpdateChildPosition() override;

    //////////////////////////////////////////////////////////////////////////
    // Public child interface
public:
    void AddSubWidgetAt(const std::shared_ptr<AUIWidget>& widget, const size_t pos) override;
    void DelSubWidget(const std::shared_ptr<AUIWidget>& widget) override;
    void PopSubWidget() override;
    void ClearSubWidget() override;
    std::shared_ptr<AUIWidget> FindSubWidget(size_t pos) override;
    size_t SubWidgetCount() const override;


    //////////////////////////////////////////////////////////////////////////
    // Title
public:
    void SetTitle(const std::wstring& caption);
    std::wstring GetTitle() const;

    //////////////////////////////////////////////////////////////////////////
    // Widgets
public:
    void SetIgnoreTitleBar(bool ignore);
    void SetIgnoreSysButton(bool ignore);
    void SetIgnoreSysButton(bool ignoreMinimize, bool ignoreMaximize, bool ignoreClose);
    std::shared_ptr<AUIWindowTitleBarWidget> GetTitleBarWidget() const {
        return m_pTitleBar;
    }
private:
    std::shared_ptr<AUIWindowTitleBarWidget> m_pTitleBar;
    std::shared_ptr<AUILinearLayoutWidget> m_pContent;
};
