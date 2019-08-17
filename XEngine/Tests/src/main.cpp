
#include <mathdll.h>


int main()
{
    int a = 5;
    int b = 10;

    int c = b & 1;

    Math::vec3 test(1.0f, 2.0f, 0.0f);
    Math::mat4 test1(1.0f);

    test1 = Math::mat4::rotateX(30.0f);

    test.x = 3.0f;

    test.y += 3.0f;

    test.z *= 2.0f;

    return 0;
}