#pragma once

namespace XEngine
{
    template<typename T>
    struct Stack
    {
        T data;
        Stack *next;
    };
}
