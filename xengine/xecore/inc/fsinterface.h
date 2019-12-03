#pragma once

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "xestring.h"

enum status
{
    OK, 
    ERROR
};

class file_system
{
    void read_dir(const xestring& path);
    void write_dir(const xestring& path);

    void read_file(const xestring& path, xestring &res);
    void write_file(const xestring& path);
};


#endif // !FILESYSTEM_H

