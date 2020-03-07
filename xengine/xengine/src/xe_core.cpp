#include "xe_core.h"

#include "xe_platform.h"

#include <stdio.h>
#include <fstream>

namespace xe_core
{
    file read_whole_file(const char *filename)
    {
        file res = {};

        FILE *op = fopen(filename, "rb");

        if (op)
        {
            fseek(op, 0, SEEK_END);
            res.size = ftell(op);
            fseek(op, 0, SEEK_SET);

            res.data = malloc(res.size);
            fread(res.data, res.size, 1, op);
            fclose(op);
        }
        else
        {
            printf("ERROR: Cant open file %s!\n", filename);
        }

        return res;
    }

    std::string read_file_string(const char *file_path)
    {
        std::ifstream file(file_path);
        if (file.fail() || !file.is_open())
        {
            printf("Failed to open file: %s\n!!!", file_path);
            return "";
        }

        std::string source;
        std::string line;

        while (getline(file, line))
        {
            source.append(line + '\n');
        }

        return source;
    }
}
