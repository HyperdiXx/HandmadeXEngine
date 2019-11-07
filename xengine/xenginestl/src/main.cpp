
#include <XEngineSTL\sort.h>

#include <iostream>

int main()
{
    using namespace xenginestl;

    int arrayTest[10] = { 120, 4564, 1, 59, 10001, 498, 134, 8, 9, 15 };

    int n = 10;
    
    bublesort(arrayTest, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d\n", arrayTest[i]);
    }

    return 0;
}
