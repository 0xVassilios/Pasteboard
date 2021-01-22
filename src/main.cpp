#include "Clipboard.h"
#include "SystemTrayIcon.h"
#include <iostream>
#include <windows.h>

SystemTrayIcon systemTrayIcon = SystemTrayIcon();
Clipboard clipboard = Clipboard();

LRESULT CALLBACK ClipboardProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_CREATE || uMsg == WM_DESTROY || uMsg == WM_CLIPBOARDUPDATE || uMsg == WM_CLOSE) {
        clipboard.configure(hwnd);
        clipboard.command(uMsg);
    } else if (uMsg == (WM_USER + 1)) {
        systemTrayIcon.command(lParam);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS winClass;
    
    winClass.cbClsExtra    = 0;
    winClass.cbWndExtra    = 0;
    winClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    winClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    winClass.hInstance     = hInstance;
    winClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    winClass.lpfnWndProc   = (WNDPROC) ClipboardProcedure;
    winClass.lpszClassName = (LPCSTR) "PasteboardWindowClass";
    winClass.lpszMenuName  = (LPCSTR) "Pasteboard";
    winClass.style         = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&winClass);
    
    // Creating the window.
    HWND winHandle = CreateWindowEx(
        0,                                 // Window Styles
        (LPCSTR) "PasteboardWindowClass",  // Window Class.
        (LPCSTR) "Pasteboard",             // Window Text.
        WS_OVERLAPPED,                     // Window Style.
        CW_USEDEFAULT,                     // X.
        CW_USEDEFAULT,                     // Y.
        CW_USEDEFAULT,                     // nWidth.
        CW_USEDEFAULT,                     // nHeight.
        NULL,                              // Parent Window.
        NULL,                              // Menu.
        hInstance,                         // Instance Handle.
        NULL                               // Additional Data.
    );

    // System Tray Icon.
    systemTrayIcon.configure(winHandle, hInstance);

    // Event Loop.
    MSG message;
    while (TRUE) {
        while (PeekMessage(&message, winHandle, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    return 0;
}