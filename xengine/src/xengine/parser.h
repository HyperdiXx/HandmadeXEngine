#ifndef PARSER_H
#define PARSER_H

enum XE_TOKEN_TYPE
{
    Token_Unknown,
    Token_ID,
    Token_Str,
    Token_Colon,
    Token_Semicolon,
    Token_Ptr,
    Token_Openbraces,
    Token_Openbracket,
    Token_Closebraces,
    Token_Closebracket,
    Token_String,
    Token_End
};

enum XE_TOKEN_VALUE_TYPE
{
    Token_Struct,
    Token_Float,
    Token_Int32,
    Token_UInt32
};

struct Token
{
    XE_TOKEN_TYPE type;
    XE_TOKEN_VALUE_TYPE value_type;

    size_t length;
    char *text;
};

struct Tokenizer
{
    char *pos;
};

#endif // !PARSER_H