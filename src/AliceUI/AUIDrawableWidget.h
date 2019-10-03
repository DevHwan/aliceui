#pragma once


#include "AUICommonDef.h"
#include "AUIWidget.h"
#include "AUILayerDrawable.h"


class ALICEUI_API AUIDrawableWidget : public AUIWidget, public AUILayerDrawable
{
    using SuperWidget = AUIWidget;
public:
    AUIDrawableWidget();
    ~AUIDrawableWidget() override = default;

	//////////////////////////////////////////////////////////////////////////
	// Create & Destroy
public:
	virtual void OnDestroy() override;

    // Drawable
public:
    AUIDrawable * GetAsDrawable() const override;

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* canvas) override;

	//////////////////////////////////////////////////////////////////////////
	// Style
public:
	void OnSetMarginLTRB(float marginLeft, float marginTop, float marginRight, float marginBottom);

    //////////////////////////////////////////////////////////////////////////
    // Rect
public:
    SkRect GetRect() const;


    //////////////////////////////////////////////////////////////////////////
    // Style Sheet
protected:
    void OnSetStyleNotion(unsigned int uiKey, const AUIStyleNotionValue& value) override;

    //////////////////////////////////////////////////////////////////////////
    // Drawable
public:
    enum DrawableLayer
    {
        kBackground_Layer = 0,
        kForeground_Layer,
        kTotalCount_Layer
    };
    virtual void SetBackgroundDrawable(const std::shared_ptr< AUIDrawable >& pDrawable);
    virtual void SetForegroundDrawable(const std::shared_ptr< AUIDrawable >& pDrawable);
protected:
    std::shared_ptr<AUIDrawable> GetBackgroundLayer() const {
        return GetLayerAt(kBackground_Layer);
    }
    std::shared_ptr<AUIDrawable> GetForegroundLayer() const {
        return GetLayerAt(kForeground_Layer);
    }

    //////////////////////////////////////////////////////////////////////////
    // Mouse Event
public:
    void SetEventPassThrough(bool bEnable) { m_bEventPassthrough = bEnable; }
protected:
    virtual void OnMouseHover() override;
    virtual void OnMouseLeave() override;
    virtual bool OnMouseLBtnDblClk(AUIMouseEvent::EventFlag flag) override { /* Implement in subclass */ return !m_bEventPassthrough; }
    virtual bool OnMouseRBtnDblClk(AUIMouseEvent::EventFlag flag) override { /* Implement in subclass */ return !m_bEventPassthrough; }
    virtual bool OnMouseMBtnDblClk(AUIMouseEvent::EventFlag flag) override { /* Implement in subclass */ return !m_bEventPassthrough; }
    virtual bool OnMouseLBtnDown(AUIMouseEvent::EventFlag flag) override { /* Implement in subclass */ return !m_bEventPassthrough; }
    virtual bool OnMouseRBtnDown(AUIMouseEvent::EventFlag flag) override { /* Implement in subclass */ return !m_bEventPassthrough; }
    virtual bool OnMouseMBtnDown(AUIMouseEvent::EventFlag flag) override { /* Implement in subclass */ return !m_bEventPassthrough; }
    virtual bool OnMouseLBtnUp(AUIMouseEvent::EventFlag flag) override { /* Implement in subclass */ return !m_bEventPassthrough; }
    virtual bool OnMouseRBtnUp(AUIMouseEvent::EventFlag flag) override { /* Implement in subclass */ return !m_bEventPassthrough; }
    virtual bool OnMouseMBtnUp(AUIMouseEvent::EventFlag flag) override { /* Implement in subclass */ return !m_bEventPassthrough; }
    virtual bool OnMouseMove(AUIMouseEvent::EventFlag flag) override { /* Implement in subclass */ return !m_bEventPassthrough; }
    virtual bool OnMouseWheel(AUIMouseEvent::EventFlag flag, float delta) override { /* Implement in subclass */ return false; }
private:
    bool m_bEventPassthrough;

    //////////////////////////////////////////////////////////////////////////
    // Status
protected:
    virtual void OnUpdate() override;
    //////////////////////////////////////////////////////////////////////////
    // Tick time event
protected:
    virtual void OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime) override;

    //////////////////////////////////////////////////////////////////////////
    // Debug Tool
private:
    SkColor m_DebugColor;
};
