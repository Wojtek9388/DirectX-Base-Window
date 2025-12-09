#ifndef Window_H
#define Window_H

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

#include "Number.h"
#include "StaticVector.h"

class Window
{
    public:
        // Setters
        void SetTitle(charw* Title) { this->Title = Title; };
        
        // Getters
        HWND GetHandle()       const { return this->Handle; }
        WNDCLASSW GetClass()    const { return this->Class; }
        MSG GetLatestMessage() const { return this->Message; }
        
        // Misc
        int Init(charw* Title, HINSTANCE hInstance, int nCmdShow);
        int Show();
        bool MessageLoop();

    private:
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        MSG Message = {};
        charw* Title;
        HWND Handle;
        WNDCLASSW Class; // Unused
        HINSTANCE HandleInstance;
        // uses alt-255 for extra space
        int ShowCommand = SW_SHOWNORMAL; // Default Value:  SW_SHOWNORMAL
};

#endif // Window_H