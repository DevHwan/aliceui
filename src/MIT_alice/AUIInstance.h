#pragma once

#include "AUICommonDef.h"

class AUIWidgetManager;
class AUIWidget;
class AUISensor;
class AUICompass;


class ALICEUI_API AUIInstance
{
    friend class AUIWidgetManager;
public:
    AUIInstance(AUIWidgetManager* pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget);
    virtual ~AUIInstance();


    //////////////////////////////////////////////////////////////////////////
    // Coordinate
public:
    virtual void OnSetCoordSpace() {}
    virtual void OnSetRootMatrix() {}
    virtual void OnSetPosition() {}



    //////////////////////////////////////////////////////////////////////////
    // Widget Manager
public:
    AUIWidgetManager* GetWidgetManager() const noexcept {
        return m_pWidgetManager;
    }
private:
    AUIWidgetManager* const m_pWidgetManager = nullptr;


    //////////////////////////////////////////////////////////////////////////
    // Instance Lifecycle
public:
    bool IsValid() const noexcept { return m_bValid; }
    bool IsDirty() const noexcept { return m_bDirty; }
    void SetDirty();
protected:
    virtual void OnCreateInstance() { /* Implement in subclass */ }
    virtual void OnDestroyInstance() { /* Implement in subclass */ }
    virtual void OnUpdateInstance() { /* Implement in subclass */ }
    virtual void OnSetDirty();
private:
    void CreateInstance();
    void DestroyInstance();
    void UpdateInstance();
    bool m_bValid = false;
    bool m_bDirty = true;
    int m_iWidgetDepth = 0;


    //////////////////////////////////////////////////////////////////////////
    // Camera Info

public:
    virtual glm::mat4 GetRootMatrix() const;
    virtual glm::mat4 GetViewingMatrix() const;
    virtual glm::mat4 GetProjectionMatrix() const;
    virtual glm::vec4 GetViewport() const;
    glm::mat4 GetLocalMatrix();

    //////////////////////////////////////////////////////////////////////////
    // Hit Test
public:
    static const float kHitDistanceScreen;
    bool IsHit() const noexcept {
        return m_bHit;
    }
    float GetHitDistance() const noexcept {
        return m_fHitDist;
    }
    const AUISensor* GetCurSensor() const noexcept {
        return m_wpCurSensor.lock().get();
    }
protected:
    void SetHit(bool bHIt, float fHitDist = 0.f) {
        m_bHit = bHIt;
        m_fHitDist = fHitDist;
    }
public:
    void UpdateCompass(AUICompass* pCompass);
private:
    void UpdateHitData(int sx, int sy);
    bool m_bHit = false;
    float m_fHitDist;
    glm::vec3 m_vLocalOrg;
    glm::vec3 m_vLocalDir;
    std::weak_ptr<AUISensor> m_wpCurSensor;


    //////////////////////////////////////////////////////////////////////////
    // Widget-Visual
public:
    AUIWidget* GetWidget() const noexcept {
        return m_pWidget.get();
    }
private:
    std::shared_ptr<AUIWidget> const m_pWidget;

public:
    bool IsDrawableRoot() const noexcept {
        return m_bDrawableRoot;
    }
protected:
    bool m_bDrawableRoot = false;
};
