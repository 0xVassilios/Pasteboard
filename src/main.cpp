#define _WIN32_WINNT 0x0600 // Minimum Compatible Version: Windows Vista

#include "clipboard.h"
#include <iostream>
#include <windows.h>
#include <shellapi.h>

Clipboard clipboard = Clipboard();

LRESULT CALLBACK ClipboardProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_CREATE: {
            // Watch the clipbaord content.
            AddClipboardFormatListener(hwnd);
            break;
        }

        case WM_DESTROY: {
            // Stop watching the clipboard content.
            RemoveClipboardFormatListener(hwnd);
            break;
        }

        case WM_CLIPBOARDUPDATE: {
            // Clipboard Changes Happened.
            OpenClipboard(hwnd);
            clipboard.add((char*) GetClipboardData(CF_TEXT));
            CloseClipboard();
            break;
        }

        case WM_CLOSE: {
            DestroyWindow(hwnd);
            break;
        }

        // This is for the system tray notification.
        case (WM_USER + 1): {
            switch(lParam) {
                case WM_LBUTTONDBLCLK:
                    MessageBox(NULL, (LPCSTR) "Message", (LPCSTR) "Title", MB_OK);
                    break;
                default:
                    return DefWindowProc(hwnd, uMsg, wParam, lParam);
            }
            break;
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
    winClass.lpfnWndProc   = (WNDPROC) ClipboardProcedure;
    winClass.lpszClassName = (LPCSTR) "PasteboardWindowClass";
    winClass.lpszMenuName  = (LPCSTR) "Pasteboard";
    winClass.style         = CS_HREDRAW | CS_VREDRAW;

    //TODO: Add error checking.
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

    // Notification.
    NOTIFYICONDATA nid;

    nid.cbSize           = sizeof(NOTIFYICONDATA);           // The size of the structure.
    nid.hIcon            = LoadIcon(NULL, IDI_APPLICATION);  // The handle for the icon used.
    nid.hWnd             = winHandle;                        // The handle of the window that processes information.
    nid.uCallbackMessage = (WM_USER + 1);                    // The message to be sent to the procedure when called.
    nid.uFlags           = NIF_MESSAGE | NIF_ICON | NIF_TIP; // Extra variables for the icon.
    nid.uID              = 100;                              // The unique ID for our icon.
    nid.uVersion         = NOTIFYICON_VERSION;               // Defines the behaviour of the icon based on the Win version.

    Shell_NotifyIcon(NIM_ADD, &nid);

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