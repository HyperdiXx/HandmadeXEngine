#pragma once

#ifndef RESOURCEOBJ_H
#define RESOURCEOBJ_H

namespace XEngine
{
    class ResourceObject
    {
    protected:

        void check()
        {
           
        }

        void create()
        {
            ref++;

            if (ref > 0)
                shouldCreate = true;
        }

        void destroy()
        {
            if (ref < 1)
                return;

            ref--;

            if (ref == 0)
                shouldCreate = false;
        }

    protected:
        int ref = 0;
        bool shouldCreate = false;
    };
}

#endif // !RESOURCEOBJ_H

