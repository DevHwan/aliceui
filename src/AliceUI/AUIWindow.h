#pragma once

#include "AUICommonDef.h"
#include "AUIForm.h"
#include "AUISignal.h"
#include "AUISlotPool.h"

class AUIDrawable;
class AUIWindowWidget;
class AUIWidget;

class ALICEUI_API AUIWindow : public std::enable_shared_from_this<AUIWindow>
{
public:
    AUIWindow();
    AUIWindow(const std::shared_ptr<AUIWindowWidget>& pWindowWidget);
    virtual ~AUIWindow();


    //////////////////////////////////////////////////////////////////////////
    // Content Widget
public:
    void SetContent(const std::shared_ptr<AUIWidget>& pWidget);


    //////////////////////////////////////////////////////////////////////////
    // Title Bar
public:
    void SetIgnoreSysButton(bool ignore);
    void SetIgnoreTitleBar(bool ignore);

    //////////////////////////////////////////////////////////////////////////
    // Window Title
public:
    void SetTitle(const std::wstring& title);
    std::wstring GetTitle() const;


    //////////////////////////////////////////////////////////////////////////
    // Show
public:
    bool IsActivated() const;
    void Activate();
    void Activate(const std::shared_ptr<AUIWindow>& pParent);
    void ActivateWithHandle(AUIHandle* const pHandle);
    void ActivateModal();
    void ActivateModal(const std::shared_ptr<AUIWindow>& pParent);
    void Deactivate();


    //////////////////////////////////////////////////////////////////////////
    // Size / Position
public:
    void SetSize(int width, int height);
    void SetPosition(int x, int y);
    void SetPositionAndSize(int x, int y, int width, int height);
    void GetSize(int& width, int& height);
    void GetPosition(int& x, int& y);
    void SetMinSize(int width, int height);
    void SetMaxSize(int width, int height);
    void SetResizeable(bool val);
    bool IsResizeable() const;


    //////////////////////////////////////////////////////////////////////////
    // System button action
private:
    void OnClickMinimize(AUIWidget*);
    void OnClickClose(AUIWidget*);


    //////////////////////////////////////////////////////////////////////////
    // Dragging
private:
    void OnDragStart(AUIWidget*);
    void OnDragEnd(AUIWidget*);
    void OnDragging(AUIWidget*, float dx, float dy);


    //////////////////////////////////////////////////////////////////////////
    // Window Widget
public:
    // NOTE : milestone 
    void SetTitleBarDrawable(const std::shared_ptr<AUIDrawable>& pDrawable);
    void SetBackgroundDrawable(const std::shared_ptr<AUIDrawable>& pDrawable);


    //////////////////////////////////////////////////////////////////////////
    // Transparency
public:
    void SetTransparent(bool val);
    bool IsTransparent() const;
    

    // Signals
public:
    AUISignal<void(AUIWindow*)> ClickCloseSignal;
    AUISignal<void(AUIWindow*)> ClickMinimizeSignal;
    
private:
    std::shared_ptr<AUIWindowWidget> m_pWindow;
    std::shared_ptr<AUIWidget> m_pContent;
    AUISlotPool m_spoolWindow;
    AUIForm m_Form;
    int m_iPrevMouseX = 0;
    int m_iPrevMouseY = 0;
};
