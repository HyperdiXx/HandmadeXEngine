#include "xe_core.h"

#include "xe_platform.h"

#include <stdio.h>

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
}
