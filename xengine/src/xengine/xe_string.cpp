
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
