#include "pch.h"
#include "AUIDarwinAppImpl.h"
#include "AUIDarwinHandle.h"
#include "AUIStringConvert.h"

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

static std::shared_ptr<AUIDarwinHandle> sDesktopHandle;

void* AUIDarwinAppImpl::sRootWindow = nullptr;

bool AUIDarwinAppImpl::InitRootWindow(void* root)
{
    AUIDarwinAppImpl::sRootWindow = root;
    sDesktopHandle = std::make_shared<AUIDarwinHandle>(root);
    return true;
}

AUIDarwinAppImpl::AUIDarwinAppImpl()
{
    
}

AUIDarwinAppImpl::~AUIDarwinAppImpl()
{
    
}

AUIHandle* AUIDarwinAppImpl::GetApplicationHandle() const
{
    static auto sApplicationHandle = std::make_shared<AUIDarwinHandle>(AUIDarwinAppImpl::sRootWindow);
    return sApplicationHandle.get();
}

void AUIDarwinAppImpl::GetApplicationSize(int& width, int& height) const
{
    const auto winsize = [[(NSWindow*)AUIDarwinAppImpl::sRootWindow contentView] frame].size;
    width = (int)winsize.width;
    height = (int)winsize.height;
}

void AUIDarwinAppImpl::GetApplicationPosition(int& x, int& y) const
{
    const auto pos = [[(NSWindow*)AUIDarwinAppImpl::sRootWindow contentView] frame].origin;
    x = (int)pos.x;
    y = (int)pos.y;
}

void AUIDarwinAppImpl::GetApplicationPositionAndSize(int& x, int& y, int& width, int& height) const
{
    const auto windowFrame = [[(NSWindow*)AUIDarwinAppImpl::sRootWindow contentView] frame];
    width = (int)windowFrame.size.width;
    height = (int)windowFrame.size.height;
    x = (int)windowFrame.origin.x;
    y = (int)windowFrame.origin.y;
}

std::wstring AUIDarwinAppImpl::GetApplicationDirectory() const
{
    const auto appFileManager = [NSFileManager defaultManager];
    const auto currentDirectoryPath = [appFileManager currentDirectoryPath];
    const auto utf8Path = [currentDirectoryPath cStringUsingEncoding:NSUTF8StringEncoding];
    return AUIStringConvert::UTF8ToWCS(utf8Path);
}

AUIHandle* const AUIDarwinAppImpl::GetDesktopHandle() const
{
    return sDesktopHandle.get();
}

void AUIDarwinAppImpl::GetDesktopSize(int& width, int& height) const
{
    // TODO
}

void AUIDarwinAppImpl::GetVirtualScreenSize(int& width, int& height) const
{
    // TODO
}

void AUIDarwinAppImpl::GetMonitorCount(int& count) const
{
    // TODO
}

void AUIDarwinAppImpl::ConvertToDesktopPos(int& desktopX, int& desktopY, const int x, const int y, AUIHandle* const pHandle)
{
    // TODO
}

void AUIDarwinAppImpl::GetMonitorRectFromPoint(SkRect& monitorRect, const int& desktopX, const int& desktopY)
{
    NSScreen* screen = ((NSWindow*)AUIDarwinAppImpl::sRootWindow).screen;
    if (nil == screen) {
        return;
    }
    monitorRect = SkRect::MakeXYWH(screen.frame.origin.x,
                                   screen.frame.origin.y,
                                   screen.frame.size.width,
                                   screen.frame.size.height);
}

void AUIDarwinAppImpl::GetMousePosition(int& x, int& y) const
{
    // TODO
    
}

void AUIDarwinAppImpl::GetMouseDragOffset(int& x, int& y) const
{
    
    // TODO
}

bool AUIDarwinAppImpl::IsMouseRightHanded() const
{
    // TODO
    return true;
}
