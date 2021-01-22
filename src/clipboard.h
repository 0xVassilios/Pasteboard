#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <vector>
#include <string>
#include <ctime>
#include <iostream>

struct Note {
    char* text;
    int creation;
};

class Clipboard {
    public:
        void add(char* text);
        void show();

    private:
        std::vector<Note> notes;
};

#endif