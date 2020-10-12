
#ifndef STRING_CPP
#define STRING_CPP

inline uint32 strLength(const char* str)
{
    const char* first = str;

    while (*str != '\0')
    {
        ++str;
    }

    return (uint32)(str - first);
}

inline bool strEquals(const char *a, const char* b)
{
    if (!a || !b)
    {
        return false;
    }

    uint32 length = strLength(a);

    if (length != strLength(b))
    {
        return false;
    }

    bool result = true;

    for (uint32 i = 0; i < length; ++i)
    {
        if (a[i] != b[i])
        {
            result = false;
            break;
        }
    }

    return result;
}

inline bool isAlpha(char character)
{
    return (character >= 'a' && character <= 'z') ||
        (character >= 'A' && character <= 'Z');
}

inline bool isNumeric(char number)
{
    return (number >= '0' && number <= '9');
}

inline bool isWhitespace(char character)
{
    return ((character == ' ') ||
        (character == '\t') ||
        (character == '\r') ||
        (character == '\n'));
}

#endif

