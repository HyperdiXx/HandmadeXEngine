
internal 
void parseChar()
{

}

internal 
void parseNumber()
{

}

internal Token getToken(Tokenizer *tokenizer)
{
    Token result = {};

    result.text = tokenizer->pos;
    result.length = 1;

    char current = tokenizer->pos[0];
    ++tokenizer->pos;

    while (true)
    {
        if (isWhitespace(tokenizer->pos[0]))
        {
            ++tokenizer->pos;
        }
        else if (tokenizer->pos[0] == '/' && tokenizer->pos[1] == '/')
        {
            tokenizer->pos += 2;

            while (tokenizer->pos[0] && !isEndOfLine(tokenizer->pos[0]))
            {
                ++tokenizer->pos;
            }           
        }
        else if (tokenizer->pos[0] == '/' && tokenizer->pos[1] == '*')
        {
            tokenizer->pos += 2;
            
            while (tokenizer->pos[0] && !((tokenizer->pos[0] == '*') && (tokenizer->pos[1] == '/')))
            {
                ++tokenizer->pos;
            }

            if (tokenizer->pos[0] == '*')
            {
                tokenizer->pos += 2;
            }
        }
        else
        {
            break;
        }
    }

    switch (current)
    {
        case '\0':
        {
            result.type = XE_TOKEN_TYPE::Token_End;
        } break;
        case ';':
        {
            result.type = XE_TOKEN_TYPE::Token_Semicolon;
        } break;
        case ':':
        {
            result.type = XE_TOKEN_TYPE::Token_Colon;
        } break;
        case '*':
        {
            result.type = XE_TOKEN_TYPE::Token_Ptr;
        } break;
        case '(':
        {
            result.type = XE_TOKEN_TYPE::Token_Openbracket;
        } break;
        case ')':
        {
            result.type = XE_TOKEN_TYPE::Token_Closebracket;
        } break;
        case '{':
        {
            result.type = XE_TOKEN_TYPE::Token_Openbraces;
        } break;
        case '}':
        {
            result.type = XE_TOKEN_TYPE::Token_Closebraces;
        } break;
        case '"':
        {
            // Skip first "
            ++tokenizer->pos;
            result.type = XE_TOKEN_TYPE::Token_String;            
            result.text = tokenizer->pos;
            
            while (tokenizer->pos[0] && tokenizer->pos[0] != '"')
            {
                if ((tokenizer->pos[0] == '\\') && tokenizer->pos[1])
                {
                    ++tokenizer->pos;
                }

                ++tokenizer->pos;
            }

            result.length = tokenizer->pos - result.text;

            if (tokenizer->pos[0] == '"')
            {
                ++tokenizer->pos;
            }

        } break;
        default:
        {
            if (isAlpha(current))
            {
                result.type = XE_TOKEN_TYPE::Token_ID;
                while (isAlpha(tokenizer->pos[0]) ||
                       isNumeric(tokenizer->pos[0]) ||
                       tokenizer->pos[0] == '_')
                {
                    ++tokenizer->pos;
                }
                      
                result.length = tokenizer->pos - result.text;
            }
/*          else if (isNumeric(current))
            {

            }*/
            else
            {
                result.type = XE_TOKEN_TYPE::Token_Unknown;
            }

        } break;
    }

    return result;
}

internal 
bool32 isTokenMatch(Token tok, char *pattern)
{
    char *pos = pattern;

    for (int i = 0;
        i < tok.length;
        ++i, ++pos)
    {
        if ((*pos == 0) ||
            (tok.text[i] != *pos))
        {
            return false;
        }
    }
   
    return (*pos == 0);
}
