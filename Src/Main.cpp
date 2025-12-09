// Windows core
#include <windows.h>
#include <wrl/client.h>

// Direct3D 11
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h> // For Shaders

// Direct2D
#include <d2d1.h>
#include <dwrite.h>      // For text rendering

#include <cstdio>

#include "Number.h"
#include "StaticVector.h"
#include "Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    bool Running = true;
    Window MainWindow;
    MainWindow.Init(L"Hello, windows!", hInstance, nCmdShow);
    MainWindow.Show();

    while (Running)
    {
        Running = MainWindow.MessageLoop();
        
    }
    return 0;
}
