#include "clipboard.h"

void Clipboard::add(char* text) {
    //TODO: Check for duplicates.
    Note note;
    note.text = text;
    note.creation = std::time(0);
    this->notes.push_back(note);
}

void Clipboard::show() {
    printf("\n");
    for (int i=0; i<this->notes.size(); i++) {
        Note note = this->notes.at(i);
        printf("Note | Text: %s , Creation: %i\n", note.text, note.creation);
    }
}

void Clipboard::configure(HWND winHandle) {
    this->winHandle = winHandle;
}

void Clipboard::command(UINT uMsg) {
    switch (uMsg) {
        case WM_CREATE: {
            // Watch the clipbaord content.
            AddClipboardFormatListener(this->winHandle);
            break;
        }

        case WM_DESTROY: {
            // Stop watching the clipboard content.
            RemoveClipboardFormatListener(this->winHandle);
            break;
        }

        case WM_CLIPBOARDUPDATE: {
            // Clipboard Changes Happened.
            OpenClipboard(this->winHandle);
            this->add((char*) GetClipboardData(CF_TEXT));
            CloseClipboard();
            break;
        }

        case WM_CLOSE: {
            DestroyWindow(this->winHandle);
            break;
        }
    }
}