#include "pch.h"
#include "AUIWin32Handle.h"
#include "AUIApplication.h"

static_assert(std::is_same<LPCTSTR, const wchar_t*>::value, "Works on Unicode Project");

static wchar_t kAliceUIWin32WndClassName[] = L"AliceUIWin32Wnd";

constexpr int NextPopupOffset = 25;
static bool isPrevPopupPosValid = false;
static int prevPopupPosX = 0;
static int prevPopupPosY = 0;

void WINAPI ModifyStyle(HWND hwnd, DWORD dwRemove, DWORD dwAdd)
{
    auto style = static_cast<DWORD>(::GetWindowLongPtrW(hwnd, GWL_STYLE));
    style = style & ~dwRemove;
    style = style | dwAdd;
    ::SetWindowLongPtrW(hwnd, GWL_STYLE, style);
    ::SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);
}

DWORD WINAPI GetStyle(HWND hwnd)
{
    return static_cast<DWORD>(::GetWindowLongPtrW(hwnd, GWL_STYLE));
}

AUIWin32Handle::AUIWin32Handle(HWND hWnd) noexcept
    : m_hWnd(hWnd)
{
    AUIAssert(GetHWND());
}

void AUIWin32Handle::SetTitle(const std::wstring & title)
{
    ::SetWindowTextW(GetHWND(), title.c_str());
}

void AUIWin32Handle::Activate(AUIHandle * const pParent)
{
    this->ActivateHWND(pParent);
    AUIHandle::Activate(pParent);
}

void AUIWin32Handle::ActivateModal(AUIHandle * const pParent)
{
}

void AUIWin32Handle::Deactivate()
{
}

bool AUIWin32Handle::IsActivated() const
{
    return false;
}

void AUIWin32Handle::DoShowMinimized()
{
}

void AUIWin32Handle::DoShowMaximized()
{
}

void AUIWin32Handle::DoShowDefault()
{
}

void AUIWin32Handle::ActivateHWND(AUIHandle * const pParent)
{
    if (IsActivated())
    {
        AUIAssert(!"Already activated");
        return;
    }

    DWORD BasicStyle = WS_CLIPCHILDREN;
    DWORD BasicExStyle = WS_EX_LAYERED;

    if (m_bVisible)
    {
        BasicStyle |= WS_VISIBLE;
    }

    if (AUIHandleMode::kPopup == m_Mode)
    {
        BasicStyle |= WS_POPUP;
    }
    else if (AUIHandleMode::kChild == m_Mode)
    {
        BasicStyle |= WS_CHILD;
    }

    if (IsTopMost())
    {
        BasicExStyle |= WS_EX_TOPMOST;
    }

    if (IsNonActivate())
    {
        BasicExStyle |= WS_EX_TOOLWINDOW;
        BasicExStyle |= WS_EX_NOACTIVATE;
    }

    if (IsResizeable())
    {
        BasicStyle |= WS_THICKFRAME;
    }

    if (m_bUseDefaultPos)
    {
        int appx;
        int appy;
        int appwidth;
        int appheight;

        AUIApplication::Instance().GetApplicationPositionAndSize(appx, appy, appwidth, appheight);

        if (m_Mode == AUIHandleMode::kChild)
            appx = appy = 0;

        if (isPrevPopupPosValid == false)
        {
            prevPopupPosX = int(appx + (appwidth - m_iWidth) * 0.5);
            prevPopupPosY = int(appy + (appheight - m_iHeight) * 0.5);
            isPrevPopupPosValid = true;
        }

        auto popupPosX = prevPopupPosX + NextPopupOffset;
        auto popupPosY = prevPopupPosY + NextPopupOffset;
        if (popupPosX + m_iWidth >= appx + appwidth - NextPopupOffset || popupPosY + m_iHeight >= appy + appheight - NextPopupOffset)
        {
            popupPosX = appx + NextPopupOffset;
            popupPosY = appy + NextPopupOffset;
        }

        m_iX = prevPopupPosX = popupPosX;
        m_iY = prevPopupPosY = popupPosY;

        m_bUseDefaultPos = false;
    }

    HWND hParentWnd = nullptr;
    if (pParent == nullptr)
    {
        hParentWnd = AUIApplication::Instance().GetApplicationHandle()->Cast<AUIWin32Handle>()->GetHWND();
    }
    else
    {
        hParentWnd = pParent->Cast<AUIWin32Handle>()->GetHWND();
    }

    const auto hInst = static_cast<HINSTANCE>(::GetModuleHandleW(nullptr));
    auto targetClassName = m_strWndClassName;
    if (targetClassName.empty())
    {
        WNDCLASSEX windowclass = { 0, };
        if (!(::GetClassInfoExW(hInst, kAliceUIWin32WndClassName, &windowclass)))
        {
            WNDCLASSEX nwndclass = { 0, };
            nwndclass.cbSize = sizeof(WNDCLASSEX);
            nwndclass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
            nwndclass.lpfnWndProc = ::DefWindowProc;
            nwndclass.cbClsExtra = nwndclass.cbWndExtra = 0;
            nwndclass.hInstance = hInst;
            nwndclass.hIcon = NULL;
            nwndclass.hCursor = ::AfxGetApp()->LoadStandardCursor(IDC_ARROW);
            nwndclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
            nwndclass.lpszMenuName = NULL;
            nwndclass.lpszClassName = kAliceUIWin32WndClassName;

            if (!::RegisterClassExW(&nwndclass))
            {
                throw std::runtime_error("Failed to register window class");
            }
        }
        targetClassName = kAliceUIWin32WndClassName;
    }
    m_hWnd = ::CreateWindowExW(BasicExStyle, targetClassName.c_str(), m_strTitle.c_str(), BasicStyle, m_iX, m_iY, m_iWidth, m_iHeight, hParentWnd, nullptr, hInst, nullptr);
    if (!GetHWND())
    {
        AUIAssert(!"Activation failed");
        return;
    }

    if (m_Opacity != kAUIAlpha100)
    {
        MakeTransparent();
    }

    if (false == IsNonActivate())
    {
        ::SetFocus(GetHWND());
    }
}

void AUIWin32Handle::Invalidate()
{
    AUIHandle::Invalidate();

    if (IsActivated())
    {
        ::InvalidateRect(GetHWND(), nullptr, TRUE);
    }
}

void AUIWin32Handle::UpdateWindow()
{
    ::UpdateWindow(GetHWND());
}

void AUIWin32Handle::SetVisible(bool state)
{
    AUIHandle::SetVisible(state);
    if (IsActivated())
    {
        int flag = 0;
        if (IsNonActivate())
        {
            flag = state ? SW_SHOWNA : SW_HIDE;
        }
        else
        {
            flag = state ? SW_SHOW : SW_HIDE;
        }
        ::ShowWindow(GetHWND(), flag);
    }
}

void AUIWin32Handle::SetFocus()
{
    AUIHandle::SetFocus();

    if (IsActivated() && false == IsNonActivate())
    {
        ::SetFocus(GetHWND());
    }
}

void AUIWin32Handle::CaptureMouseEvent()
{
    if (IsActivated())
    {
        ::SetCapture(GetHWND());
        m_bMouseCaptured = true;
    }
    else
    {
        m_bMouseCaptured = false;
    }
}

void AUIWin32Handle::ReleaseMouseEvent()
{
    if (IsActivated())
    {
        ::ReleaseCapture();
    }
    m_bMouseCaptured = false;
}

void AUIWin32Handle::SetOpacity(const SkAlpha alpha)
{
    m_Opacity = alpha;

    if (IsActivated())
    {
        MakeTransparent();
    }
}

bool AUIWin32Handle::MakeTransparent()
{
    if (IsActivated() == false)
        return false;

    AUIAssert(GetHWND());

    typedef DWORD(WINAPI* funcSLWA)(HWND, DWORD, BYTE, DWORD);
    static funcSLWA pFuncSetLayeredWindowAttributes = nullptr;
    static std::once_flag initload;
    std::call_once(initload, []() {
        if (const auto hUser32 = LoadLibrary(_T("user32")))
            pFuncSetLayeredWindowAttributes = reinterpret_cast<funcSLWA>(GetProcAddress(hUser32, "SetLayeredWindowAttributes"));
    });

    if (pFuncSetLayeredWindowAttributes == nullptr)
        return false;

    // Layered window
    ::SetLastError(0);
    ::SetWindowLongPtrW(GetHWND(), GWL_EXSTYLE, GetWindowLongPtr(GetHWND(), GWL_EXSTYLE) | WS_EX_LAYERED);
    if (GetLastError())
        return false;

    return (pFuncSetLayeredWindowAttributes(GetHWND(), RGB(0, 0, 1), GetOpacity(), LWA_COLORKEY | LWA_ALPHA) > 0) ? true : false;
}

bool AUIWin32Handle::IsZoomed() const
{
    return static_cast<bool>(::IsZoomed(GetHWND()));
}

bool AUIWin32Handle::IsIconic() const
{
    return static_cast<bool>(::IsIconic(GetHWND()));
}

void AUIWin32Handle::SetResizeable(bool val)
{
    SuperClass::SetResizeable(val);
    if (IsActivated())
    {
        if (val)
            ::ModifyStyle(GetHWND(), NULL, WS_THICKFRAME);
        else
            ::ModifyStyle(GetHWND(), WS_THICKFRAME, NULL);
    }
}

bool AUIWin32Handle::IsResizeable() const
{
    if (IsActivated())
    {
        if (::GetStyle(GetHWND()) & WS_THICKFRAME)
            return true;
        else
            return false;
    }
    return SuperClass::IsResizeable();
}

void AUIWin32Handle::SetSize(int width, int height)
{
    if (IsActivated())
    {
        int x;
        int y;
        GetPosition(x, y);

        UINT flag = SWP_NOZORDER | SWP_NOSIZE;
        if (IsNonActivate())
        {
            flag |= SWP_NOACTIVATE;
        }
        ::SetWindowPos(GetHWND(), nullptr, x, y, width, height, flag);
    }
    AUIHandle::SetSize(width, height);
}

void AUIWin32Handle::SetPosition(int x, int y)
{
    if (IsActivated())
    {
        int width;
        int height;
        this->GetSize(width, height);

        UINT flag = SWP_NOZORDER | SWP_NOREPOSITION;
        if (IsNonActivate())
        {
            flag |= SWP_NOACTIVATE;
        }
        ::SetWindowPos(GetHWND(), nullptr, x, y, width, height, flag);
    }
    AUIHandle::SetPosition(x, y);
    m_bUseDefaultPos = false;
}

void AUIWin32Handle::SetPositionAndSize(int x, int y, int sx, int sy)
{
    if (IsActivated())
    {
        UINT flag = SWP_NOZORDER;
        if (IsNonActivate())
        {
            flag |= SWP_NOACTIVATE;
        }
        ::SetWindowPos(GetHWND(), nullptr, x, y, sx, sy, flag);
    }

    AUIHandle::SetPositionAndSize(x, y, sx, sy);
    m_bUseDefaultPos = false;
}

void AUIWin32Handle::GetSize(int & width, int & height)
{
    if (IsActivated())
    {
        CRect rect;
        ::GetWindowRect(GetHWND(), rect);
        m_iWidth = rect.Width();
        m_iHeight = rect.Height();
    }
    AUIHandle::GetSize(width, height);
}

void AUIWin32Handle::GetPosition(int & x, int & y)
{
    if (IsActivated())
    {
        CRect rect;
        ::GetWindowRect(GetHWND(), rect);
        m_iX = rect.left;
        m_iY = rect.top;
    }
    AUIHandle::GetPosition(x, y);
}

void AUIWin32Handle::GetPositionAndSize(int & x, int & y, int & sx, int & sy)
{
    if (IsActivated())
    {
        CRect rect;
        ::GetWindowRect(GetHWND(), rect);
        m_iX = rect.left;
        m_iY = rect.top;
        m_iWidth = rect.Width();
        m_iHeight = rect.Height();
    }
    AUIHandle::GetPositionAndSize(x, y, sx, sy);
}

void AUIWin32Handle::BeginModal()
{
    AUIAssert(GetHWND());
    const auto hParentWnd = ::GetParent(GetHWND());
    if (!hParentWnd)
    {
        AUIAssert(!"Must have parent");
        return;
    }
    ::EnableWindow(hParentWnd, FALSE);

    ::EnableWindow(GetHWND(), TRUE);
    ::InvalidateRect(GetHWND(), nullptr, TRUE);

    m_ModalLooper.RunModalLoop(GetHWND(), hParentWnd);

    //Deactivate();
    if (IsActivated())
        Deactivate();
}

void AUIWin32Handle::EndModal(int result)
{
    AUIAssert(GetHWND());
    const auto hParentWnd = ::GetParent(GetHWND());
    AUIAssert(!hParentWnd);

    ::EnableWindow(hParentWnd, TRUE);

    //GetWnd()->DestroyWindow();
    //// Deactivate
    //Deactivate();


    m_ModalLooper.EndModalLoop(GetHWND(), result);

    //GetWnd()->DestroyWindow();
}

int AUIWin32Handle::ModalLooper::RunModalLoop(HWND hWnd, HWND hParentWnd)
{
    AUIAssert(::IsWindow(hWnd));

    //if (!hParentWnd)
    //    ::EnableWindow(hwndParent, FALSE);
    MSG msg{ 0, };
    for (fDone = false; fDone; ::WaitMessage())
    {
        while (::PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
            {
                fDone = true;
                ::PostMessageW(NULL, WM_QUIT, 0, 0);
                break;
            }

            if (!::IsDialogMessageW(hWnd, &msg))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessageW(&msg);
            }
        }
    }

    //if (hParentWnd != NULL)
    //    ::EnableWindow(hParentWnd, TRUE);

    ::DestroyWindow(hWnd);

    return fResult;
}

void AUIWin32Handle::ModalLooper::EndModalLoop(HWND hWnd, int nResult)
{
    AUIAssert(::IsWindow(hWnd));
    this->fResult = nResult;
    this->fDone = true;
    ::PostMessageW(hWnd, WM_NULL, NULL, NULL);
}
