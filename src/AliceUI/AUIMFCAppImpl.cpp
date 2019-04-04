#include "pch.h"
#include "AUIMFCAppImpl.h"
#include "AUIMFCHandle.h"

namespace {
    auto funcGetMainWnd() {
        return ::AfxGetApp()->GetMainWnd();
    }
}

AUIMFCAppImpl::AUIMFCAppImpl()
{
    const auto hModule = GetModuleHandle(nullptr);
    wchar_t path[_MAX_PATH] = { L'\0', };
    AUIAssert( hModule );
    ::GetModuleFileNameW(hModule, path, _MAX_PATH);
    AUIAssert(wcslen(path) > 0);
    const auto exepath = std::wstring(path);
    const auto dirpos = exepath.rfind( L'\\' );
    m_strExeDir = exepath.substr( 0, dirpos );
    AUIAssert( m_strExeDir.empty() == false );
}

AUIHandle* AUIMFCAppImpl::GetApplicationHandle() const
{
    static auto sApplicationHandle = std::make_shared<AUIMFCHandle>(funcGetMainWnd());
    return sApplicationHandle.get();
}

void AUIMFCAppImpl::GetApplicationSize( int& width, int& height ) const
{
    CRect rect;
    AUIAssert(funcGetMainWnd());
    funcGetMainWnd()->GetWindowRect( rect );

    width = rect.Width();
    height = rect.Height();
}

void AUIMFCAppImpl::GetApplicationPosition( int& x, int& y ) const
{
    CRect rect;
    AUIAssert(funcGetMainWnd());
    funcGetMainWnd()->GetWindowRect( rect );

    x = rect.left;
    y = rect.top;
}

std::wstring AUIMFCAppImpl::GetApplicationDirectory() const
{
    return m_strExeDir;
}

void AUIMFCAppImpl::GetApplicationPositionAndSize( int& x, int& y, int& width, int& height ) const
{
    CRect rect;
    AUIAssert(funcGetMainWnd());
    funcGetMainWnd()->GetWindowRect( rect );

    x = rect.left;
    y = rect.top;
    width = rect.Width();
    height = rect.Height();
}

AUIHandle* const AUIMFCAppImpl::GetDesktopHandle() const
{
    static auto sDesktopHandle = std::make_shared<AUIMFCHandle>(CWnd::GetDesktopWindow());
    return sDesktopHandle.get();
}

void AUIMFCAppImpl::GetDesktopSize( int& width, int& height ) const
{
    width = ::GetSystemMetrics( SM_CXSCREEN );
    height = ::GetSystemMetrics( SM_CYSCREEN );
}

void AUIMFCAppImpl::GetMonitorCount( int& count ) const
{
    count = ::GetSystemMetrics( SM_CMONITORS );
}

void AUIMFCAppImpl::GetVirtualScreenSize( int& width, int& height ) const
{
    width = ::GetSystemMetrics( SM_CXVIRTUALSCREEN );
    height = ::GetSystemMetrics( SM_CYVIRTUALSCREEN );
}

void AUIMFCAppImpl::GetMousePosition( int& x, int& y ) const
{
    CPoint point;
    ::GetCursorPos( &point );
    x = int( point.x );
    y = int( point.y );
}

void AUIMFCAppImpl::GetMouseDragOffset( int& x, int& y ) const
{
    x = ::GetSystemMetrics( SM_CXDRAG );
    y = ::GetSystemMetrics( SM_CYDRAG );
}

bool AUIMFCAppImpl::IsMouseRightHanded() const
{
    return ( !::GetSystemMetrics( SM_SWAPBUTTON ) );
}

void AUIMFCAppImpl::ConvertToDesktopPos( int& desktopX, int& desktopY, const int x, const int y, AUIHandle* const pHandle )
{
    if ( nullptr == pHandle )
    {
        desktopX = x;
        desktopY = y;
        AUIAssertFailReason("Invalid handle");
        return;
    }
    AUIAssert( dynamic_cast< AUIMFCHandle* >( pHandle ) );
    auto pMFCHandle = static_cast< AUIMFCHandle* >( pHandle );
    auto pWnd = pMFCHandle->GetWnd();
    if ( nullptr == pWnd )
    {
        desktopX = x;
        desktopY = y;
        AUIAssertFailReason("Can't find CWnd class");
        return;
    }

    CPoint pt( x, y );
    ::ClientToScreen( pWnd->GetSafeHwnd(), &pt );
    desktopX = pt.x;
    desktopY = pt.y;
}

void AUIMFCAppImpl::GetMonitorRectFromPoint( SkRect& monitorRect, const int& desktopX, const int& desktopY )
{
    const auto hMonitor = ::MonitorFromPoint( CPoint( desktopX, desktopY ), MONITOR_DEFAULTTONEAREST );
    MONITORINFOEX miex = { 0, };
    miex.cbSize = sizeof( miex );
    ::GetMonitorInfo( hMonitor, &miex );

    const auto l = static_cast<SkScalar>( miex.rcMonitor.left );
    const auto t = static_cast<SkScalar>( miex.rcMonitor.top );
    const auto r = static_cast<SkScalar>( miex.rcMonitor.right );
    const auto b = static_cast<SkScalar>( miex.rcMonitor.bottom );

    monitorRect = SkRect::MakeLTRB( l, t, r, b );
}
