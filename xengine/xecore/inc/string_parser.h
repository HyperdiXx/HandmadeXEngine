#pragma once

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

class xestring;

class string_parser
{
public:
    static void skip_whitespaces(xestring *str);
    static bool is_whitespace(char sym);
};
#endif // !STRING_UTILS_H

