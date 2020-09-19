
internal void parseToken()
{

}

internal token get_parsed_token(char *text_to_parse)
{
    token result = {};

    result.text = text_to_parse;
    result.length = 90;

    while (isWhitespace(*text_to_parse))
    {
        ++text_to_parse;
    }

    switch (*text_to_parse)
    {
        case '"':
        {
            char *token_text = text_to_parse;
            printf("This is open quote!\n");
            ++text_to_parse;

            while (*text_to_parse != '"' && *text_to_parse)
            {
                if (*text_to_parse == '\\' && text_to_parse[1])
                {
                    ++text_to_parse;
                }

                ++text_to_parse;
            }

            size_t text_len = text_to_parse - token_text;

            //OutputDebugStringA((LPCSTR)token_text);


        } break;

        default:
        {
            ++text_to_parse;
        } break;
    }

    return result;
}