#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include <fstream>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

#include "../../Exceptions/SaveException.h"
#include "../../Exceptions/LoadException.h"
#include "../../Exceptions/FileException.h"

class SaveFile {

private:
    std::FILE* filePointer;
    std::string filename;
    SaveFile(const SaveFile&);
    SaveFile& operator=(const SaveFile&) = delete;

    void clear();
public:
    SaveFile(const char* filename);
    ~SaveFile();

    void open();
    void close();
    std::stringstream read();
    void write(const char* str);


};

#endif
