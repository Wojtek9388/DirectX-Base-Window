#include "Window.h"

// Windows core
#include <windows.h>
#include <wrl/client.h>
#include <stdexcept>      // For exceptions
#include <cstdio>         // For swprintf, printf
#include <cstdint>        // For fixed-size types (uint32_t, int32_t, etc.)

// Direct3D 11
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h> // For shaders
#include <DirectXMath.h> // For matrices, vectors, etc.

// Direct2D
#include <d2d1.h>
#include <dwrite.h>      // For text rendering
#include <d2d1helper.h>  // Optional helpers, like D2D1::RectF

// Optional utilities
#include <vector> // For Dynamic Vectors
#include <memory> // For smart pointers (unique_ptr, shared_ptr)

#include <cwchar>
#include <stdexcept>

#include "Number.h"
#include "StaticVector.h"

// --------------- //
//     Public      //
// --------------- //

// Misc
int Window::Init(charw* Title, HINSTANCE hInstance, int nCmdShow)
{
    this->HandleInstance = hInstance;
    this->Title = Title;
    this->ShowCommand = nCmdShow;

    WNDCLASSW wc = {};
    wc.lpfnWndProc = Window::WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = Title;

    if (!RegisterClassW(&wc))
    {
        DWORD err = GetLastError();
        wchar_t buffer[256];
        wsprintfW(buffer, L"Failed to register window class! Error code: %lu", err);
        MessageBoxW(nullptr, buffer, L"Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    this->Handle = CreateWindowExW(
        0,
        wc.lpszClassName,
        Title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr,
        hInstance,
        this                // pass 'this' for WM_NCCREATE
    );

    if (!this->Handle)
    {
        DWORD err = GetLastError();
        wchar_t buffer[256];
        wsprintfW(buffer, L"Failed to create window! Error code: %lu", err);
        MessageBoxW(nullptr, buffer, L"Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    return 0;
}

int Window::Show()
{
    ShowWindow(this->Handle, this->ShowCommand);

    return 0;
};

bool Window::MessageLoop()
{
    while (PeekMessage(&this->Message, nullptr, 0, 0, PM_REMOVE))
    {
        if (this->Message.message == WM_QUIT) return false;
        TranslateMessage(&this->Message);
        DispatchMessage(&this->Message);
    }

    return true;
};
