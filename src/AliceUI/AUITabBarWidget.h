#pragma once

#include "AUILinearLayoutWidget.h"

class AUITab;
class AUITabButtonWidget;

class ALICEUI_API AUITabBarWidget : public AUILinearLayoutWidget
{
    typedef AUILinearLayoutWidget SuperClass;
public:
    AUITabBarWidget();
    ~AUITabBarWidget() override;

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;
    AUITabButtonWidget* GetCurrentTabButton();

    //////////////////////////////////////////////////////////////////////////
    // Tab Style
public:
    void SetTabStyle(AUIImageCaptionStyle style);
    AUIImageCaptionStyle GetTabStyle() const;
    void SetTabDefaultTextColor(SkColor color);
    void SetTabUncheckTextColor(SkColor color);
    void SetTabHoverTextColor(SkColor color);

	//////////////////////////////////////////////////////////////////////////
	// UnderLine
public:
	bool IsUnderLine() const noexcept {
        return m_bUnderLine;
    }
	void SetUnderLine(const bool val) noexcept {
        m_bUnderLine = val;
    }
	SkColor GetUnderLineColor() const noexcept {
        return m_UnderLineColor;
    }
	void SetUnderLineColor(const SkColor val) noexcept {
        m_UnderLineColor = val;
    }
    
    //////////////////////////////////////////////////////////////////////////
    // Tab
public:
    void AddTab(const std::shared_ptr<AUITab>& pTab);
    void RemoveTab(const std::shared_ptr<AUITab>& pTab);
    void RemoveTab(const std::shared_ptr<AUIWidget>& pWidget);
    void SetVisibleTab(const std::shared_ptr<AUITab>& pTab, bool bVisible);
    void HideTab(const std::shared_ptr<AUITab>& pTab, bool bHide);
    bool IsHiddenTab(const std::shared_ptr<AUITab>& pTab) const;
    bool IsHiddenTab(const size_t idx) const;
    void ClearTab();
    void SetCurrentTab(const std::shared_ptr<AUITab>& pTab);
    void ReplaceTab(size_t idx, const std::shared_ptr<AUITab>& pTab);
    const std::shared_ptr<AUITab> GetCurrentTab() const {
        return m_pCurTab;
    }
    size_t GetTabCount() const { return m_arrTabs.size(); }
    std::shared_ptr<AUITab> FindTabByWidget(const std::shared_ptr<AUIWidget>& pWidget);
    std::shared_ptr<AUITab> FindTabByIndex(const size_t idx) const;
    const std::vector<std::shared_ptr<AUITab>>& GetTabs() const noexcept {
        return m_arrTabs;
    }
protected:
    virtual std::shared_ptr<AUITabButtonWidget> OnCreateTabButton();
    void OnClickTabButton(AUIWidget* const pWidget);

    //////////////////////////////////////////////////////////////////////////
    // Public child interface
public:
    void AddSubWidgetAt(const std::shared_ptr<AUIWidget>& widget, const size_t pos) override;
    void DelSubWidget(const std::shared_ptr<AUIWidget>& widget) override;
    void PopSubWidget() override;
    void ClearSubWidget() override;
    std::shared_ptr< AUIWidget > FindSubWidget(size_t pos) override;
    size_t SubWidgetCount() const override;

    // Signals
public:
    AUISignal<void(AUITab*)> TabClickSignal;

private:
    std::shared_ptr<AUITab> m_pCurTab;
    std::vector<std::shared_ptr<AUITab>> m_arrTabs;
    std::unordered_map<AUITab*, std::weak_ptr<AUITabButtonWidget>> m_mapTab2Button;
    AUIImageCaptionStyle m_TabStyle = AUIImageCaptionStyle::kTextOnly;
    // Text Colors
    SkColor m_TabDefaultTextColor;
    SkColor m_TabUncheckTextColor;
    SkColor m_TabHoverTextColor;
    SkColor m_UnderLineColor;
    // Border
    bool m_bUnderLine = false;
};
