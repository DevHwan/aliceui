#pragma once

#include "AUIDarwinHandle.h"
#include "AUIRasterWidgetManager.h"
#include "AUIWidget.h"

class ALICEUI_API AUIDarwinWindowHandle : public AUIDarwinHandle
{
    using SuperHandle = AUIDarwinHandle;
public:
    AUIDarwinWindowHandle();
    ~AUIDarwinWindowHandle() override;

private:
    bool InitializeWindow();
    bool FinalizeWindow();

    //////////////////////////////////////////////////////////////////////////
    // Widget
public:
    void SetRootWidget(const std::shared_ptr<AUIWidget>& pWidget) override;


    //////////////////////////////////////////////////////////////////////////
    // Activate / Deactivate
public:
    void Activate(AUIHandle* const pParent) override;
    void ActivateModal(AUIHandle* const pParent) override;
    void Deactivate() override;

    //////////////////////////////////////////////////////////////////////////
    // Size / Position
public:
    void SetMinSize(int width, int height) override;
    void SetMaxSize(int width, int height) override;

    //////////////////////////////////////////////////////////////////////////
    // Transparency
public:
    void SetTransparent(bool val) override;
    bool IsTransparent() const override;


    //////////////////////////////////////////////////////////////////////////
    // Window object
public:
    void* Window() const noexcept {
        return this->fWindow;
    }
    AUIRasterWidgetManager* GetWidgetManager() const {
        return this->m_pWidgetManager.get();
    }
private:
    void* fWindow;
    std::unique_ptr<AUIRasterWidgetManager> m_pWidgetManager;
};
