#pragma once

#include "AUICommonDef.h"
#include "AUISignal.h"

class AUILazyTaskManager;
class AUIAsyncTask;
class AUIWidgetTreeHelper;
class AUIWidget;
class AUIWidgetManager;
class AUIWindow;
class AUIHandle;
class AUIForm;

class ALICEUI_API AUIApplicationImpl
{
protected:
    AUIApplicationImpl();
public:
    virtual ~AUIApplicationImpl();

    virtual AUIHandle* GetApplicationHandle() const = 0;
    virtual void GetApplicationSize(int& width, int& height) const = 0;
    virtual void GetApplicationPosition(int& x, int& y) const = 0;
    virtual void GetApplicationPositionAndSize(int& x, int& y, int& width, int& height) const = 0;
    virtual std::wstring GetApplicationDirectory() const = 0;

    virtual AUIHandle* const GetDesktopHandle() const = 0;
    virtual void GetDesktopSize(int& width, int& height) const = 0;
    virtual void GetVirtualScreenSize(int& width, int& height) const = 0;
    virtual void GetMonitorCount(int& count) const = 0;
    virtual void ConvertToDesktopPos(int& desktopX, int& desktopY, const int x, const int y, AUIHandle* const pHandle) = 0;
    virtual void GetMonitorRectFromPoint(SkRect& monitorRect, const int& desktopX, const int& desktopY) = 0;

    virtual void GetMousePosition(int& x, int& y) const = 0;
    virtual void GetMouseDragOffset(int& x, int& y) const = 0;
    virtual bool IsMouseRightHanded() const = 0;
};

class ALICEUI_API AUIApplication final
{
private:
    AUIApplication(std::unique_ptr<AUIApplicationImpl>&& pAppImpl);
public:
    ~AUIApplication();
public:
    static bool SetupApplication(std::unique_ptr<AUIApplicationImpl>&& pAppImpl);
    static AUIApplication& Instance();

    //////////////////////////////////////////////////////////////////////////
    // Initialize instance
public:
    bool Initialize();
    bool Finalize();
    bool IsInitialized() const {
        return m_bInitialized;
    }
private:
    bool m_bInitialized;

    //////////////////////////////////////////////////////////////////////////
    // Widget Manager
public:
    void AttachWidgetManager(AUIWidgetManager* const pWidgetManager);
    void DetachWidgetmanager(AUIWidgetManager* const pWidgetManager);

    //////////////////////////////////////////////////////////////////////////
    // Widget Instance Control
public:
    void CreateInstance(AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget);
    void DestroyInstance(AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget);
    void ClearInstance(AUIWidgetManager* const pWidgetManager);
    void RunUpdateInstanceTask();
    void RunInstanceGarbageCollection();
    bool IsInUpdateInstanceTask() const {
        return m_bInUpdateInstanceTask;
    }
private:
    void OnRunLazyCreateInstance(AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget);
    void OnRunLazyDestroyInstance(AUIWidgetManager* const pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget);
    std::unordered_set< AUIWidgetManager* > m_setWidgetManager;
    bool m_bInUpdateInstanceTask;

    struct WidgetLazyTask final
    {
        enum TaskType
        {
            kInvalid_TaskType,
            kCreate_TaskType,
            kDestroy_TaskType
        };
        TaskType fTaskType = kInvalid_TaskType;
        std::shared_ptr< AUIWidget > fWidget;
        AUIWidgetManager* fWidgetManager = nullptr;

        WidgetLazyTask() noexcept = default;
        WidgetLazyTask(const TaskType& _taskType, const std::shared_ptr< AUIWidget >& _widget, AUIWidgetManager* const _widgetManager) noexcept;
        WidgetLazyTask(const WidgetLazyTask& _other) noexcept = default;
        WidgetLazyTask(WidgetLazyTask&& _other) noexcept = default;
        WidgetLazyTask& operator=(const WidgetLazyTask&) noexcept = default;
        WidgetLazyTask& operator=(WidgetLazyTask&&) noexcept = default;

        bool IsSameWidget(const WidgetLazyTask& _lazyTask) noexcept
        {
            return (this->fWidget == _lazyTask.fWidget);
        }
        bool IsSameTask(const WidgetLazyTask& _lazyTask) noexcept
        {
            return (this->fWidget == _lazyTask.fWidget &&
                this->fTaskType == _lazyTask.fTaskType &&
                this->fWidgetManager == _lazyTask.fWidgetManager);
        }

        static WidgetLazyTask MakeCreate(const std::shared_ptr< AUIWidget >& _widget, AUIWidgetManager* const _widgetManager) noexcept;
        static WidgetLazyTask MakeDestroy(const std::shared_ptr< AUIWidget >& _widget, AUIWidgetManager* const _widgetManager) noexcept;
    };
    std::vector< WidgetLazyTask > m_arrWidgetLazyTask;



    //////////////////////////////////////////////////////////////////////////
    // Debug
public:
#ifdef _DEBUG
    inline void DebugPrintTreeInfo(AUIWidget* pWidget) const
    {
        DebugPrintTreeInfo_Private(pWidget);
    }
#else
    inline void DebugPrintTreeInfo(AUIWidget* pWidget) const
    {
        do {} while (false); /* No-Op */
    }
#endif
private:
    void DebugPrintTreeInfo_Private(AUIWidget* pWidget, int step = 0) const;



    //////////////////////////////////////////////////////////////////////////
    // Widget Tree
public:
    AUIWidgetTreeHelper& GetWidgetTree() const;
private:
    std::unique_ptr< AUIWidgetTreeHelper > m_pWidgetTree;





    //////////////////////////////////////////////////////////////////////////
    // Debug Tool
public:
    void SetVisualizeLayout(bool val) { m_bVisualizeLayout = val; }
    bool IsVisualizeLayout() const { return m_bVisualizeLayout; }
    void SetTraceWidgetLifecycle(bool val) { m_bTraceWidgetLifecycle = val; }
    bool IsTraceWidgetLifecycle() const { return m_bTraceWidgetLifecycle; }
private:
    bool m_bVisualizeLayout;
    bool m_bTraceWidgetLifecycle;


    //////////////////////////////////////////////////////////////////////////
    // Refresh
public:
    void Refresh();
    void MainRefresh();

    AUISignal<void(), false > RefreshSignal;    // May not called in main-thread
    AUISignal<void()> RefreshMainSignal;        // Called in main-thread
    AUISignal<void()> HeavyUpdateSignal;        // Called in main-thread

    //////////////////////////////////////////////////////////////////////////
    // Lazy update
public:
    void RunLazyUpdate();
    void PostLazyUpdate();

    AUISignal<void()> LazyUpdateSignal;             // Called in main-thread
    AUISignal<void()> AfterLazyUpdateSignal;        // Called in main-thread
    AUISignal<void(), false> PostLazyUpdateSignal;  // May not called in main-thread

private:
    std::unique_ptr<AUILazyTaskManager> m_pLazyTaskManager;


    //////////////////////////////////////////////////////////////////////////
    // Async Task
public:
    void AsyncExecute(const std::shared_ptr<AUIAsyncTask>& pAsyncTask);
private:
    std::unordered_set<std::shared_ptr<AUIAsyncTask>> m_setAsyncExecute;


    //////////////////////////////////////////////////////////////////////////
    // Window
public:
    void RegisterWindow(const std::shared_ptr< AUIWindow >& pWindow);
    void RegisterWindow(const std::shared_ptr< AUIWindow >& pWindow, const std::shared_ptr< AUIWindow >& pParent);
    void UnregisterWindow(const std::shared_ptr< AUIWindow >& pWindow);
    bool IsRegisteredWindow(const std::shared_ptr< AUIWindow >& pWindow) const;
private:
    void UnregisterAllWindows();
    std::unordered_map<AUIWindow*, std::list<std::shared_ptr<AUIWindow>>> m_Windows;
    std::unordered_map<AUIWindow*, std::weak_ptr<AUIWindow>> m_RegisteredWindows;


    //////////////////////////////////////////////////////////////////////////
    // Application Information
public:
    AUIHandle* const GetApplicationHandle() const;
    void GetApplicationSize(int& width, int& height) const;
    void GetApplicationPosition(int& x, int& y) const;
    void GetApplicationPositionAndSize(int& x, int& y, int& width, int& height) const;
    std::wstring GetApplicationDirectory() const;


    //////////////////////////////////////////////////////////////////////////
    // Desktop Information
public:
    AUIHandle* const GetDesktopHandle() const;
    void GetDesktopSize(int& width, int& height) const;
    void GetVirtualScreenSize(int& width, int& height) const;
    void GetMonitorCount(int& count) const;
    void ConvertToDesktopPos(int& desktopX, int& desktopY, const int x, const int y, AUIHandle* const pHandle);
    void GetMonitorRectFromPoint(SkRect& monitorRect, const int& desktopX, const int& desktopY);

    //////////////////////////////////////////////////////////////////////////
    // Mouse Information
public:
    void GetMousePosition(int& x, int& y) const;
    void GetMouseDragOffset(int& x, int& y) const;
    bool IsMouseRightHanded() const;

    AUISignal<void(AUIWidgetManager*, int, int, float)> MouseWheelSignal;

    //////////////////////////////////////////////////////////////////////////
    // Tooltip
public:
    bool InitializeTooltip();
    std::shared_ptr<AUIForm> GetTooltipForm() const {
        return m_pTooltipForm;
    }
private:
    std::shared_ptr<AUIForm> m_pTooltipForm;


    //////////////////////////////////////////////////////////////////////////
    // OS Implementation
private:
    AUIApplicationImpl* const GetImpl() const { return m_pImpl.get(); }
    std::unique_ptr<AUIApplicationImpl> m_pImpl;
};

class ALICEUI_API AUIApplicationAutoInit final
{
public:
    AUIApplicationAutoInit();
    AUIApplicationAutoInit(std::unique_ptr<AUIApplicationImpl>&& pAppImpl);
    ~AUIApplicationAutoInit();
};
