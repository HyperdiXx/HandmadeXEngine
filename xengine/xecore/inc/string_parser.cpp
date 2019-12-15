#include "string_parser.h"

#include "assert.h"
#include "xestring.h"

// TODO : find better way to delete 
void string_parser::skip_whitespaces(xestring *str)
{
    assert(str != nullptr);

    uint16 count = 0;

    for (uint32 i = 0; i < str->get_length(); i++)
    {
        if (is_whitespace(str->m_data[i]))        
            str->erase(i);        
    }
}

bool string_parser::is_whitespace(char sym)
{
    return sym == ' ' || sym == '\r' || sym == '\n' || sym == '\t' || sym == '\f';
}
