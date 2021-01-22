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