#pragma once

#ifndef XE_PARSER_H
#define XE_PARSER_H

#include "xe_types.h"
#include "xenpch.h"

namespace xe_parser
{
    class Parser
    {
    public:

        Parser() = default;
        Parser(const Parser& p);
        
        Parser(Parser &&);
        Parser& operator=(Parser&&);

        Parser(bool32 val);
        Parser(const std::string &val);
        Parser(const char *val);
        Parser(uint32 val);
    
        std::string toString() const;

        bool32 operator==(const Parser &other) const;

        static Parser fromString(const std::string &val);

    private:


    private:
        struct ParserObj;

        std::unique_ptr<ParserObj> parser_obj_data;
    };
}
#endif
