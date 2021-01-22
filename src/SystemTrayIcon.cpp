#include "SystemTrayIcon.h"

void SystemTrayIcon::configure(HWND winHandle, HINSTANCE hInstance) {
    this->notifyIconData.cbSize           = sizeof(NOTIFYICONDATA);                            // The size of the structure.
    this->notifyIconData.hIcon            = (HICON) LoadImage(NULL, "clipboard.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE|LR_DEFAULTSIZE); 
    this->notifyIconData.hWnd             = winHandle;                                         // The handle of the window that processes information.
    this->notifyIconData.uCallbackMessage = (WM_USER + 1);                                     // The message to be sent to the procedure when called.
    this->notifyIconData.uFlags           = NIF_MESSAGE | NIF_ICON | NIF_TIP;                  // Extra variables for the icon.
    this->notifyIconData.uID              = 100;                                               // The unique ID for our icon.
    this->notifyIconData.uVersion         = NOTIFYICON_VERSION;                                // Defines the behaviour of the icon based on the Win version.
    strncpy(this->notifyIconData.szTip, "Pasteboard", sizeof(this->notifyIconData.szTip));     // Setting the tooltip text to the application's name.

    Shell_NotifyIcon(NIM_ADD, &this->notifyIconData);
}

void SystemTrayIcon::command(LPARAM param) {
    switch(param) {
        case WM_RBUTTONDOWN:
            MessageBox(NULL, (LPCSTR) "Message", (LPCSTR) "Title", MB_OK);
            break;
    }
}