
#include "common.h"
#include "macro.h"

#include "core.h"
#include "parser.h"

#include "core.cpp"

#include "string.cpp"
#include "parser.cpp"

internal 
void parseReflectedParams(Tokenizer *tokenizer)
{
    while (true)
    {
        Token tok = getToken(tokenizer);
        if ((tok.type == Token_Closebracket) ||
            tok.type == Token_End)
        {
            break;
        }
    }
}

internal 
bool32 isToken(Tokenizer *tokenizer, XE_TOKEN_TYPE setup)
{
    Token tok = getToken(tokenizer);
    return tok.type == setup;
}

internal 
void parseMember(Tokenizer *tokenizer, Token member)
{
    bool32 active = true;
    bool32 isPtr = false;

    while (active)
    {
        Token current = getToken(tokenizer);

        switch (current.type)
        {
            case Token_ID:
            {
                printf("ID VALUE: %. *s \n", current.length, current.text);
            } break;
            case Token_Ptr:
            {
                isPtr = true;
            } break;
            case Token_Semicolon:
            case Token_End:
            {
                // Skip!!!
                active = false;
            } break;
        }      
    }
}

internal 
void parseStruct(Tokenizer *tokenizer)
{
    Token struct_name = getToken(tokenizer);

    if (isToken(tokenizer, Token_Openbraces))
    {
        while (true)
        {
            Token member = getToken(tokenizer);
            if (member.type != Token_Closebraces)
            {
                parseMember(tokenizer, member);
            }
            else
            {
                break;
            }
        }
    }
}

internal 
void parseReflected(Tokenizer *tokenizer)
{
    if (isToken(tokenizer, Token_Openbracket))
    {
        parseReflectedParams(tokenizer);
        Token token_type = getToken(tokenizer);

        if (isTokenMatch(token_type, "struct"))
        {
            parseStruct(tokenizer);
        }
        else
        {
            //
        }
    }
    else
    {
        //
    }
}

int main(int arg_count, char **args)
{
    char* file_source = xe_core::readFileToChar("xengine/ecs.h");
    
    bool32 active = true;

    Tokenizer tokenizer = {};
    tokenizer.pos = file_source;

    while (active)
    {
        Token tok = getToken(&tokenizer);

        switch (tok.type)
        {
            case Token_End:
            {
                active = false;
            } break;
            case Token_Unknown:
            {

            } break;
            case Token_ID:
            {
                if (isTokenMatch(tok, "REFLECT"))
                {
                    parseReflected(&tokenizer);
                }

            } break;
            default:
            {
            } break;
        }
    }

    return 0;
}