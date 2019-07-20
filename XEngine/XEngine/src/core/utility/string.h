#pragma once

#include <string>
#include <sstream>
#include <vector>


namespace XEngine
{
    class String
    {
    public:
        String() { }
        String(std::string s) : str(s) { }

        std::vector<String> splitInto(char symbol)
        {
            std::stringstream ss;
            std::vector<String> res;

            ss.str(str);
            std::string value;

            while (getline(ss, value, symbol)) {
                res.push_back(String(value));
            }

            return res;
        }

        bool operator==(const char* s) const
        {
            return str == s;
        }

        bool operator==(const String& s) const
        {
            return str == s.toStr();
        }

        std::string toStr() const 
        {
            return str;
        }

        const char* toStrChar() const 
        {
            return str.c_str();
        }

        String operator+(const String& s) const
        {
            return String(str + s.toStr());
        }


    private:
        std::string str;

    };
}