#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <windows.h>
#include <shellapi.h>
#include <WinUser.h>
#include <iostream>

#define MENU_BUTTON_CLOSE 100
#define MENU_BUTTON_OPEN 110

class SystemTrayIcon {
    public:
        void configure(HWND winHandle, HINSTANCE hInstance);
        void command(LPARAM param);
        void command(WPARAM param);

    private:
        NOTIFYICONDATA notifyIconData;
        HWND winHandle;
};

#endif