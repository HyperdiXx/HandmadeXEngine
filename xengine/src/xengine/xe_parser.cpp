#include "xe_parser.h"

namespace xe_parser
{
    // Pimpl Idiom
    struct Parser::Impl
    {
        enum class Type
        {
            Null,
            Unknown,
            Boolean,
            Int,
            Float,
            String
        };

        Impl()
        {

        };

        ~Impl()
        {
        };

        Impl(const Impl &) = delete;
        Impl& operator=(const Impl &other) = delete;

        Impl(Impl&&) = delete;
        Impl& operator=(Impl && pars) = delete;

        Type objType = Type::Null;

        union
        {
            bool32 bool_value;
            uint32 uint_value;
            std::string str_value;
        };

    };

    Parser::~Parser() = default;

    //Parser::Parser(const Parser & p) = default;
   // Parser& Parser::operator=(const Parser& p) = default;

    Parser::Parser(Parser && pars) = default;
    Parser& Parser::operator=(Parser && pars) = default;
    
    Parser::Parser(bool32 val) : parser_obj_data(std::make_unique<Impl>())
    {
        parser_obj_data->bool_value = val;
        parser_obj_data->objType = Impl::Type::Boolean;
    }

    Parser::Parser(const std::string & val) : parser_obj_data(std::make_unique<Impl>())
    {
        parser_obj_data->str_value = val;
        parser_obj_data->objType = Impl::Type::String;
    }

    Parser::Parser(const char *val) : parser_obj_data(std::make_unique<Impl>())
    {
        parser_obj_data->str_value = std::string(val);
        parser_obj_data->objType = Impl::Type::String;
    }

    Parser::Parser(uint32 val) : parser_obj_data(std::make_unique<Impl>())
    {
        parser_obj_data->uint_value = val;
        parser_obj_data->objType = Impl::Type::Int;
    }
    
    std::string Parser::toString() const
    {
        switch (parser_obj_data->objType)
        {
        case Impl::Type::Null:
        {
            return "null";
        } break;
        case Impl::Type::Boolean:
        {
            return parser_obj_data->bool_value ? "true" : "false";
        } break;
        case Impl::Type::String:
        {
            return parser_obj_data->str_value;
        } break;
        case Impl::Type::Int:
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
            case Impl::Type::Null: 
            {
                return true;
            }
            case Impl::Type::Boolean:
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
