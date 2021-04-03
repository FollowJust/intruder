#include "SaveFile.h"

SaveFile::SaveFile(const char* filename) {
    this->filename = filename;
}

void SaveFile::open() {
    fopen_s(&filePointer, filename.c_str(), "r+");

    if (!filePointer)
        throw FileException("Can't open the file\n");
}

std::stringstream SaveFile::read() {
    open();
    std::stringstream inpStream;
    char str[100];
    while (std::fgets(str, 100, filePointer) != NULL) {
        inpStream << str;
    }
    close();
    return inpStream;
}

void SaveFile::write(const char* str) {
    open();
    if (std::fputs(str, filePointer) == EOF) {
        throw FileException("Can't write in file\n");
    }
    close();
}

void SaveFile::close() {
    if (std::fclose(filePointer) != 0)
    {
        throw FileException("Can't close the file\n");
    }
}

SaveFile::~SaveFile() {
    if (filePointer)
        delete filePointer;
}