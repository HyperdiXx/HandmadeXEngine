#include "xe_parser.h"

namespace xe_parser
{
    // Pimpl Idiom
    class Parser::ParserObj
    {
    public:
        enum class Type
        {
            Null,
            Unknown,
            Boolean,
            Int,
            Float,
            String
        };

        ParserObj() {};
        ~ParserObj() {};

        ParserObj(const ParserObj &) = default;
        ParserObj& operator=(const ParserObj &other) = default;

        ParserObj(ParserObj&&) = default;
        ParserObj& operator=(ParserObj && pars) = default;

        Type objType = Type::Null;

        union
        {
            bool32 bool_value;
            uint32 uint_value;
            std::string str_value;
        };

    };

    Parser::Parser(const Parser & p) = default;

    Parser::Parser(Parser && pars) = default;
    Parser& Parser::operator=(Parser && pars) = default;
    
    Parser::Parser(bool32 val) : parser_obj_data(std::make_unique<ParserObj>())
    {
        parser_obj_data->bool_value = val;
        parser_obj_data->objType = ParserObj::Type::Boolean;
    }

    Parser::Parser(const std::string & val) : parser_obj_data(std::make_unique<ParserObj>())
    {
        parser_obj_data->str_value = val;
        parser_obj_data->objType = ParserObj::Type::String;
    }

    Parser::Parser(const char *val) : parser_obj_data(std::make_unique<ParserObj>())
    {
        parser_obj_data->str_value = std::string(val);
        parser_obj_data->objType = ParserObj::Type::String;
    }

    Parser::Parser(uint32 val) : parser_obj_data(std::make_unique<ParserObj>())
    {
        parser_obj_data->uint_value = val;
        parser_obj_data->objType = ParserObj::Type::Int;
    }
    
    std::string Parser::toString() const
    {
        switch (parser_obj_data->objType)
        {
        case ParserObj::Type::Null:
        {
            return "null";
        } break;
        case ParserObj::Type::Boolean:
        {
            return parser_obj_data->bool_value ? "true" : "false";
        } break;
        case ParserObj::Type::String:
        {
            return parser_obj_data->str_value;
        } break;
        case ParserObj::Type::Int:
        {
            //return std::string(parser_obj_data.uint_value);
        } break;
        default:
            break;
        }

        return "null";
    }

    bool32 Parser::operator==(const Parser & other) const
    {
        if (parser_obj_data->objType != other.parser_obj_data->objType)
        {
            return false;
        }
        else switch (parser_obj_data->objType)
        {
            case ParserObj::Type::Null: 
            {
                return true;
            }
            case ParserObj::Type::Boolean:
            {
                return parser_obj_data->bool_value == other.parser_obj_data->bool_value;
            }
            default:
            {
                return true;
            }            
        }       
    }

    Parser Parser::fromString(const std::string & val)
    {
        if (val == "true")
        {
            return true;
        }
        else if (val == "false")
        {
            return false;
        }
        else if (val == "null")
        {
            return nullptr;
        }
        else
        {
            return Parser();
        }
    }
}
