#include "pch.h"
#include "AUIWin32AppImpl.h"
#include "AUIWin32Handle.h"

static wchar_t kAliceUIWin32ApplicationWndClassName[] = L"AliceUIWin32Application";

HWND AUIWin32AppImpl::hRootWindow = nullptr;

AUIWin32AppImpl::AUIWin32AppImpl()
{
    AUIAssert(AUIWin32AppImpl::hRootWindow);

    std::vector<wchar_t> modulePathBuffer(MAX_PATH, L'\0');
    const auto lastBufferSize = ::GetModuleFileNameW(nullptr, modulePathBuffer.data(), static_cast<DWORD>(modulePathBuffer.size()));
    if (modulePathBuffer.size() < lastBufferSize)
    {
        modulePathBuffer.resize(lastBufferSize + 1, L'\0');
        const auto fallbackBufferSize = ::GetModuleFileNameW(nullptr, modulePathBuffer.data(), static_cast<DWORD>(modulePathBuffer.size()));
        AUIAssert(modulePathBuffer.size() > fallbackBufferSize);
    }
    const std::wstring strPath(modulePathBuffer.data());
    m_strExeDir = strPath.substr(0, strPath.find_last_of(L"\\/"));
    AUIAssert(m_strExeDir.empty() == false);
}

AUIHandle * AUIWin32AppImpl::GetApplicationHandle() const
{
    static auto sApplicationHandle = std::make_shared<AUIWin32Handle>(AUIWin32AppImpl::hRootWindow);
    return sApplicationHandle.get();
}

void AUIWin32AppImpl::GetApplicationSize(int & width, int & height) const
{
    AUIAssert(AUIWin32AppImpl::hRootWindow);
    RECT rect{ 0, };
    ::GetWindowRect(AUIWin32AppImpl::hRootWindow, &rect);

    width = rect.right - rect.left;
    height = rect.bottom - rect.top;
}

void AUIWin32AppImpl::GetApplicationPosition(int & x, int & y) const
{
    AUIAssert(AUIWin32AppImpl::hRootWindow);
    RECT rect{ 0, };
    ::GetWindowRect(AUIWin32AppImpl::hRootWindow, &rect);

    x = rect.left;
    y = rect.top;
}

void AUIWin32AppImpl::GetApplicationPositionAndSize(int & x, int & y, int & width, int & height) const
{
    AUIAssert(AUIWin32AppImpl::hRootWindow);
    RECT rect{ 0, };
    ::GetWindowRect(AUIWin32AppImpl::hRootWindow, &rect);

    x = rect.left;
    y = rect.top;
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;
}

std::wstring AUIWin32AppImpl::GetApplicationDirectory() const
{
    return m_strExeDir;
}

AUIHandle * const AUIWin32AppImpl::GetDesktopHandle() const
{
    static auto sDesktopHandle = std::make_shared<AUIWin32Handle>(::GetDesktopWindow());
    return sDesktopHandle.get();
}

void AUIWin32AppImpl::GetDesktopSize(int & width, int & height) const
{
    width = ::GetSystemMetrics(SM_CXSCREEN);
    height = ::GetSystemMetrics(SM_CYSCREEN);
}

void AUIWin32AppImpl::GetVirtualScreenSize(int & width, int & height) const
{
    width = ::GetSystemMetrics(SM_CXVIRTUALSCREEN);
    height = ::GetSystemMetrics(SM_CYVIRTUALSCREEN);
}

void AUIWin32AppImpl::GetMonitorCount(int & count) const
{
    count = ::GetSystemMetrics(SM_CMONITORS);
}

void AUIWin32AppImpl::ConvertToDesktopPos(int & desktopX, int & desktopY, const int x, const int y, AUIHandle * const pHandle)
{
    if (nullptr == pHandle)
    {
        desktopX = x;
        desktopY = y;
        AUIAssertFailReason("Invalid handle");
        return;
    }
    AUIAssert(dynamic_cast<AUIWin32Handle*>(pHandle));
    auto pWin32Handle = static_cast<AUIWin32Handle*>(pHandle);
    auto hWnd = pWin32Handle->GetHWND();
    if (!hWnd)
    {
        desktopX = x;
        desktopY = y;
        AUIAssertFailReason("Can't find CWnd class");
        return;
    }

    POINT pt{ x, y };
    ::ClientToScreen(hWnd, &pt);
    desktopX = pt.x;
    desktopY = pt.y;
}

void AUIWin32AppImpl::GetMonitorRectFromPoint(SkRect & monitorRect, const int & desktopX, const int & desktopY)
{
    const auto hMonitor = ::MonitorFromPoint(POINT{ desktopX, desktopY }, MONITOR_DEFAULTTONEAREST);
    MONITORINFOEX miex = { 0, };
    miex.cbSize = sizeof(miex);
    ::GetMonitorInfoW(hMonitor, &miex);

    const auto l = static_cast<SkScalar>(miex.rcMonitor.left);
    const auto t = static_cast<SkScalar>(miex.rcMonitor.top);
    const auto r = static_cast<SkScalar>(miex.rcMonitor.right);
    const auto b = static_cast<SkScalar>(miex.rcMonitor.bottom);

    monitorRect = SkRect::MakeLTRB(l, t, r, b);
}

void AUIWin32AppImpl::GetMousePosition(int & x, int & y) const
{
    POINT point{ 0, };
    ::GetCursorPos(&point);
    x = int(point.x);
    y = int(point.y);
}

void AUIWin32AppImpl::GetMouseDragOffset(int & x, int & y) const
{
    x = ::GetSystemMetrics(SM_CXDRAG);
    y = ::GetSystemMetrics(SM_CYDRAG);
}

bool AUIWin32AppImpl::IsMouseRightHanded() const
{
    return (!::GetSystemMetrics(SM_SWAPBUTTON));
}

void AUIWin32AppImpl::InitRootWindow(HWND hRootWindow)
{
    AUIAssert(!AUIWin32AppImpl::hRootWindow);
    AUIWin32AppImpl::hRootWindow = hRootWindow;
}
