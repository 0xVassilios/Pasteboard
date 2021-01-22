#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#define _WIN32_WINNT 0x0600 // Minimum Compatible Version: Windows Vista

#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <windows.h>

struct Note {
    char* text;
    int creation;
};

class Clipboard {
    public:
        void add(char* text);
        void command(UINT uMsg);
        void configure(HWND winHandle);
        void show();

    private:
        std::vector<Note> notes;
        HWND winHandle;
};

#endif