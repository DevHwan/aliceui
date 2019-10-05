#pragma once


#include "AUICommonDef.h"
#include "AUIDeviceEvents.h"
#include "AUICursorIcon.h"


class AUIWidget;
class AUIHandle;
class AUIWidgetSelection;
class AUIInstance;
class AUIWidgetLazyTaskManager;
class AUITooltip;
class AUITooltipWidget;

class ALICEUI_API AUIWidgetManager
{
    friend class AUIApplication;
public:
    AUIWidgetManager();
    virtual ~AUIWidgetManager();


    //////////////////////////////////////////////////////////////////////////
    // Typecast helper
public:
    template<typename _Derived>
    bool IsKindOf() const {
        static_AUIAssert(std::is_base_of<AUIWidgetManager, _Derived>::value, "Must be derived from AUIWidget");
        return (nullptr != dynamic_cast<const _Derived*>(this));
    }
    template<typename _Derived>
    _Derived* Cast() const {
        AUIAssert(this->IsKindOf<_Derived>());
        return static_cast<_Derived*>(const_cast<AUIWidgetManager*>(this));
    }
    template<typename _Derived>
    _Derived* DynCast() const {
        return dynamic_cast<_Derived*>(const_cast<AUIWidgetManager*>(this));
    }

    //////////////////////////////////////////////////////////////////////////
    // Handle
public:
    void SetHandle(const std::shared_ptr<AUIHandle>& pHandle);
    AUIHandle* const GetHandle() const {
        return m_wpHandle.lock().get();
    }


    //////////////////////////////////////////////////////////////////////////
    // Widget selection control
public:
    AUIWidgetSelection& GetWidgetSelection() const {
        return *m_pWidgetSelection;
    }
    void SetGrabMouseEvent(bool state);
    bool IsGrabMouseEvent() const noexcept {
        return m_bGrabMouseEvent;
    }


    //////////////////////////////////////////////////////////////////////////
    // Popup
public:
    bool IsInvoked(const std::shared_ptr<AUIWidget>& pWidget) const;
    bool Invoke(const std::shared_ptr<AUIWidget>& pWidget, const std::shared_ptr<AUIWidget>& pParent, const AUIScalar3& pos) {
        return Invoke(pWidget, pParent, pos, AUIPopupPos::kUnchanged);
    }
    bool Invoke(const std::shared_ptr<AUIWidget>& pWidget, const std::shared_ptr<AUIWidget>& pParent, const AUIScalar3& pos, const AUIPopupPos& opt);
    bool Dismiss(const std::shared_ptr<AUIWidget>& pWidget);
protected:
    virtual bool OnInvoke(const std::shared_ptr<AUIWidget>& pWidget, const std::shared_ptr<AUIWidget>& pParent, const AUIScalar3& pos, const AUIPopupPos& opt);
    virtual bool OnDismiss(const std::shared_ptr<AUIWidget>& pWidget);


    //////////////////////////////////////////////////////////////////////////
    // State
public:
    bool IsEnabled() const noexcept {
        return m_bEnabled;
    }
protected:
    void SetEnabled(bool state) {
        m_bEnabled = state;
    }

    //////////////////////////////////////////////////////////////////////////
    // Camera Info
public:
    virtual glm::mat4 GetViewingMatrix() const {
        return glm::mat4(1.0f);
    }
    virtual glm::mat4 GetProjectionMatrix() const {
        return glm::mat4(1.0f);
    }
    virtual glm::vec4 GetViewport() const {
        return glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
	virtual double GetPixelSize() const {
        return 0.0;
    }

    //////////////////////////////////////////////////////////////////////////
    // Focus control
public:
    void SetFocusTarget(const std::weak_ptr<AUIWidget>& pWidget = std::weak_ptr<AUIWidget>());
    std::weak_ptr<AUIWidget> GetFocusedTarget() const {
        return m_pFocusWidget;
    }

    //////////////////////////////////////////////////////////////////////////
    // Event sender
public:
    bool SendMouseEvent(const AUIMouseEvent& evt);
    bool SendKeyboardEvent(const AUIKeyboardEvent& evt);
    void SendTickTimeEvent(const std::chrono::milliseconds& prevTick, const std::chrono::milliseconds& curTick);
    bool SendSetCursorEvent(AUICursorIcon& cursoricon);

    glm::dvec2 GetMousePos() const {
        return glm::vec2(m_MousePosX, m_MousePosY);
    }
    glm::dvec3 GetMouseOrg() const {
        return m_MouseOrg;
    }
	glm::dvec3 GetMouseDir() const {
        return m_MouseDir;
    }

private:
    bool SendMouseHoverEventToWidget(AUIInstance* const pInstance, const AUIMouseEvent& evt);
    bool SendMouseEventToWidget(AUIInstance* const pInstance, const AUIMouseEvent& evt);
    bool SendKeyboardEventToWidget(AUIInstance* const pInstance, const AUIKeyboardEvent& evt);
    void SendTickTimeToWidget(AUIInstance* const pInstance, const std::chrono::milliseconds& prevTick, const std::chrono::milliseconds& curTick);
    bool SendSetCursorEventToWidget(AUIInstance* const pInstance, AUICursorIcon& cursoricon);


    //////////////////////////////////////////////////////////////////////////
    // Tooltip
protected:
    virtual void OnShowTooltip(const std::shared_ptr< AUITooltip >& pTooltip, int x, int y);
    virtual void OnHideTooltip();
    bool HasTooltipInstance() const {
        return m_bHasTooltipInst;
    }
private:
    void LazyUpdateTooltip();
    void ShowTooltip(const std::shared_ptr< AUITooltip >& pTooltip);
    void HideTooltip();



    //////////////////////////////////////////////////////////////////////////
    // Hit Test Buffer
private:
    void RefreshHitTestBuffer(int x, int y);
    struct HitBufferData
    {
        float fDistance = 0.0f;
        std::weak_ptr<AUIInstance> fInstance;

        HitBufferData(const float dist, std::weak_ptr<AUIInstance> inst) noexcept : fDistance(dist), fInstance(std::move(inst)) {}

        HitBufferData() noexcept = default;
        HitBufferData(const HitBufferData&) noexcept = default;
        HitBufferData(HitBufferData&&) noexcept = default;
        HitBufferData& operator=(const HitBufferData&) noexcept = default;
        HitBufferData& operator=(HitBufferData&&) noexcept = default;
    };
    
    //////////////////////////////////////////////////////////////////////////
    // Widget control
public:
    void CreateInstance(const std::shared_ptr<AUIWidget>& pWidget);
    void DestroyInstance(const std::shared_ptr<AUIWidget>& pWidget);
    void ClearInstance();
    size_t GetInstanceCount() const noexcept {
        return m_mapWidget2Instance.size();
    }
    AUIInstance* const FindInstance(AUIWidget* const pWidget);
    const AUIInstance* const FindInstance(AUIWidget* const pWidget) const;
protected:
    virtual std::shared_ptr<AUIInstance> OnRegisterWidget(const std::shared_ptr<AUIWidget>& pWidget);
    std::vector<std::shared_ptr<AUIInstance>>::const_iterator InstBegin() const {
        return m_Instances.cbegin();
    }
    std::vector<std::shared_ptr<AUIInstance>>::const_iterator InstEnd() const {
        return m_Instances.cend();
    }
    void GetInstances(std::vector<std::shared_ptr<AUIInstance>>& arrInstances) const;
    virtual void OnPreRegisterWidget() { /* Implement in subclass */ }
    virtual void OnPostRegisterWidget() { /* Implement in subclass */ }
    virtual void OnPreUnregisterWidget() { /* Implement in subclass */ }
    virtual void OnPostUnregisterWidget() { /* Implement in subclass */ }
private:
    void RegisterWidget(const std::shared_ptr<AUIWidget>& pWidget);
    void UnregisterWidget(const std::shared_ptr<AUIWidget>& pWidget);


    //////////////////////////////////////////////////////////////////////////
    // Update
public:
    bool UpdateAllInstance();
protected:
    virtual void OnPreUpdateAllInstance() { /* Implement in subclass */ }
    virtual void OnPostUpdateAllInstance() { /* Implement in subclass */ }
private:
    void UpdateInstance(AUIWidget* const pWidget);
    void UpdateInstance(const std::shared_ptr<AUIInstance>& pInstance);


    //////////////////////////////////////////////////////////////////////////
    // Dirty
public:
    bool IsDirty() const noexcept {
        return m_bDirty;
    }
    void SetDirty() noexcept {
        m_bDirty = true;
    }

    //////////////////////////////////////////////////////////////////////////
    // Hover state
public:
    bool IsLastHovered() const noexcept {
        return m_bLastHovered;
    }
    bool IsLastHandled() const noexcept {
        return m_bLastHandled;
    }
    
    
private:
    std::weak_ptr<AUIHandle> m_wpHandle;
    std::unique_ptr<AUIWidgetSelection> m_pWidgetSelection;
    std::weak_ptr<AUIWidget> m_pFocusWidget;
    std::vector<std::shared_ptr<AUIWidget>> m_InvokedWidgets;
    
    glm::vec3 m_MouseOrg = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_MouseDir = glm::vec3(0.0f, 0.0f, 0.0f);
    //std::multimap<float, std::weak_ptr<MAUIInstance>> m_HitTestBuffer;
    std::vector<HitBufferData> m_HitTestBuffer;
    
    std::vector<std::shared_ptr<AUIInstance>> m_Instances;
    mutable std::recursive_mutex m_mtxInstances;
    std::unordered_map<AUIWidget*, std::shared_ptr<AUIInstance>> m_mapWidget2Instance;

    std::chrono::milliseconds m_TooltipTimerStart = std::chrono::milliseconds::zero();
    std::weak_ptr<AUIWidget> m_wpTooltipTarget;
    std::weak_ptr<AUIWidget> m_wpTooltipTimerTarget;
    std::shared_ptr<AUITooltip> m_pTooltip;
    
    int m_MousePosX = 0;
    int m_MousePosY = 0;
    int m_TooltipOffsetX = 20;
    int m_TooltipOffsetY = 20;
    
    bool m_bGrabMouseEvent = false;
    bool m_bEnabled = true;
    bool m_bDirty = false;
    bool m_bShowTooltip = false;
    bool m_bHasTooltipInst = false;
    bool m_bLastHovered = false;
    bool m_bLastHandled = false;

};
