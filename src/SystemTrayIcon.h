#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <windows.h>
#include <shellapi.h>
#include <WinUser.h>
#include <iostream>

class SystemTrayIcon {
    public:
        void configure(HWND winHandle, HINSTANCE hInstance);
        void command(LPARAM param);

    private:
        NOTIFYICONDATA notifyIconData;
        HWND winHandle;
};

#endif