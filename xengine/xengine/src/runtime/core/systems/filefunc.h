#pragma once

#include <string>

namespace XEngine
{
    
    class FileUtils
    {
    public:
        static std::string readFileEngine(const char* filepath)
        {
            FILE *file = fopen(filepath, "rt");
            if (file != nullptr)
            {
                fseek(file, 0, SEEK_END);
                unsigned long length = ftell(file);
                char* shadercode = new char[length + 1];
                memset(shadercode, 0, length + 1);
                fseek(file, 0, SEEK_SET);
                fread(shadercode, 1, length, file);
                fclose(file);

                std::string res(shadercode);
                delete[] shadercode;
                return res;
            }
            else
            {
                printf("Error in shader reading function");
            }
           
        }
    };
    
}