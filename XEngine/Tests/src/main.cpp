
#include <xemath.h>

#define AssertEquals(x, y) \
    if((x) != (y)) { __debugbreak();}

void maxTest()
{
    using namespace Math;

    float a = 5.0f;
    float b = 2.0f;

    float res = Utils::max(a, b);

    AssertEquals(a, res);
}

void minTest()
{
    using namespace Math;

    float a = 5.0f;
    float b = 2.0f;

    float res = Utils::min(a, b);

    AssertEquals(b, res);
}

void absTest()
{
    using namespace Math;

    float a = -5.0f;

    Utils::abs(a);

    AssertEquals(5.0f, a);
}

void quaternionTest()
{
    using namespace Math;

    Quaternion q1(0.0f, 0.0f, 0.0f, 1.0f);
    Quaternion q2;

    AssertEquals(q1, q2);

}

void mat3Test()
{
    using namespace Math;
   
    mat3 a(1.0f);
    mat3 check;
    vec3f test = a.getRow(0);
    
    a.setRow(1, new vec3f(5.0f, 12.0f, 1.0f));

    test = a.getRow(1);

    mat3 b(1.0f);


    mat4 newtest(1.0f, 0.0f, 3.0f, 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f, 
                 4.0f, 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f);

    newtest.printElements();

    newtest.transpose();

    newtest.printElements();

    mat3 mat3pr(1.0f);

    mat3pr.printElements();

    mat3 matpr2(1.0f, 2.0f, 3.0f,
                0.0f, 1.0f, 0.0f,
                4.0f, 0.0f, 1.0f);

    matpr2.printElements();
}

int main()
{
    using namespace Math;

    maxTest();
    minTest();
    absTest();
    quaternionTest();


    mat3Test();
   
    int a = 5;
    int b = 10;

    int c = b & 1;

    vec3f test(1.0f, 2.0f, 0.0f);
    mat4 test1(1.0f);
    mat4 test2(1.0f);
    mat4 test3(1.0f);

    test1 = mat4::rotateX(30.0f);

    test.x = 3.0f;

    test.y += 3.0f;

    test.z *= 2.0f;

    if (test2 == test3)
        std::cout << "True!!!\n";
    else
        std::cout << "False!!!\n";

    test2.set(0, 15.0f);
    test2.set(5, 24.0f);

    test2.set(1, 1, 130.0f);

    float res = test2.get(15);
   
    if (test2 == test3)
        std::cout << "True!!!\n";
    else
        std::cout << "False!!!\n";

    printf("Before transpos test\n");
    for (int i = 0; i < 16; ++i)
    {
        printf("%g", test2[i]);
    }

    test2.transpose();

    for (int i = 0; i < 16; ++i)
    {
        printf("%g", test2[i]);
    }

    test2.transpose();

    printf("\nAfter transpos test\n");

    for (int i = 0; i < 16; ++i)
    {
        printf("%g", test2[i]);
    }

    
    return 0;
}

