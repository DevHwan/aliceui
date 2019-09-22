#pragma once

#include "AUIApplication.h"

class AUIHandle;

class ALICEUI_API AUIWin32AppImpl : public AUIApplicationImpl
{
public:
    AUIWin32AppImpl();
    ~AUIWin32AppImpl() override = default;


    //////////////////////////////////////////////////////////////////////////
    // Application Information
public:
    AUIHandle* GetApplicationHandle() const override;
    void GetApplicationSize(int& width, int& height) const override;
    void GetApplicationPosition(int& x, int& y) const override;
    void GetApplicationPositionAndSize(int& x, int& y, int& width, int& height) const override;
    std::wstring GetApplicationDirectory() const override;
private:
    std::wstring m_strExeDir;


    //////////////////////////////////////////////////////////////////////////
    // Desktop Information
public:
    AUIHandle* const GetDesktopHandle() const override;
    void GetDesktopSize(int& width, int& height) const override;
    void GetVirtualScreenSize(int& width, int& height) const override;
    void GetMonitorCount(int& count) const override;
    void ConvertToDesktopPos(int& desktopX, int& desktopY, const int x, const int y, AUIHandle* const pHandle) override;
    void GetMonitorRectFromPoint(SkRect& monitorRect, const int& desktopX, const int& desktopY) override;


    //////////////////////////////////////////////////////////////////////////
    // Mouse Information
public:
    void GetMousePosition(int& x, int& y) const override;
    void GetMouseDragOffset(int& x, int& y) const override;
    bool IsMouseRightHanded() const override;

public:
    static void InitRootWindow(HWND hRootWindow);
private:
    static HWND hRootWindow;
};
