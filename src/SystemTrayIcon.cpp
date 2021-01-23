#include "SystemTrayIcon.h"

void SystemTrayIcon::configure(HWND winHandle, HINSTANCE hInstance) {
    this->winHandle = winHandle;

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
    //TODO: Make exit button work. InsertMenu
    switch(param) {
        case WM_RBUTTONDOWN:
            POINT point;
            GetCursorPos(&point);
            HMENU hMenu = CreatePopupMenu();
            InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING, 100, (LPCSTR) "Exit");
            TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_BOTTOMALIGN, point.x, point.y, 0, this->winHandle, NULL);
            break;
    }
}