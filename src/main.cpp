#define _WIN32_WINNT 0x0600 // Minimum Compatible Version: Windows Vista

#include "clipboard.h"
#include <iostream>
#include <windows.h>

Clipboard clipboard = Clipboard();

LRESULT CALLBACK WinProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_CREATE: {
            // Watch the clipbaord content.
            AddClipboardFormatListener(hwnd);
            return FALSE;
        }

        case WM_DESTROY: {
            // Stop watching the clipboard content.
            RemoveClipboardFormatListener(hwnd);
            return FALSE;
        }

        case WM_CLIPBOARDUPDATE: {
            // Clipboard Changes Happened.
            OpenClipboard(hwnd);
            HANDLE text = GetClipboardData(CF_TEXT);
            clipboard.add((char*) text);
            CloseClipboard();
            return FALSE;
        }

        case WM_CLOSE: {
            DestroyWindow(hwnd);
            return FALSE;
        }

        default: {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS winClass;
    
    winClass.cbClsExtra    = 0;
    winClass.cbWndExtra    = 0;
    winClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    winClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    winClass.hInstance     = hInstance;
    winClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    winClass.lpfnWndProc   = (WNDPROC) WinProcedure;
    winClass.lpszClassName = (LPCSTR) "PasteboardWindowClass";
    winClass.lpszMenuName  = (LPCSTR) "Pasteboard";
    winClass.style         = CS_HREDRAW | CS_VREDRAW;

    //TODO: Add error checking.
    RegisterClass(&winClass);
    
    // Creating the window.
    HWND winHandle = CreateWindowEx(
        0,                         // Window Styles
        (LPCSTR) "PasteboardWindowClass",  // Window Class.
        (LPCSTR) "Pasteboard",             // Window Text.
        WS_OVERLAPPED,             // Window Style.
        CW_USEDEFAULT,             // X.
        CW_USEDEFAULT,             // Y.
        CW_USEDEFAULT,             // nWidth.
        CW_USEDEFAULT,             // nHeight.
        NULL,                      // Parent Window.
        NULL,                      // Menu.
        hInstance,                 // Instance Handle.
        NULL                       // Additional Data.
    );

    // Event Loop.
    //TODO: Make loop conditional.
    MSG message;
    while (TRUE) {
        while (PeekMessage(&message, winHandle, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }   

    return 0;
}