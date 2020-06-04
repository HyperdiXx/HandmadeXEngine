
#include "types.h"

// @for now...
#include <glm/glm.hpp>

#define PI 					(3.1415926535897932f)	
#define SMALL_NUMBER		(1.e-8f)
#define DELTA			    (0.00001f)

#include <random>

#define THRESH_QUAT_NORMALIZED 0.01f
#define TOLERANCE 0.00000001f

inline static int32 truncate_int(real32 val)
{ 
    return (int32)val;
}

inline static real32 truncate_float(real32 val)
{
    return (real32)val;
}

inline static int32 floor_int(real32 val)
{
    return truncate_int(floorf(val));
}

inline static int32 round_int(real32 val)
{
    return floor_int(val + 0.5f);
}

inline static real32 floor_float(real32 val)
{
    return floorf(val);
}

inline static real64 floor_double(real32 val)
{
    return floor(val);
}

inline static real32 round_float(real32 val)
{
    return floor_float(val + 0.5f);
}

inline static real32 ceil_float(real32 val)
{
    return ceilf(val);
}

inline static real64 ceil_double(real64 val)
{
    return ceil(val);
}

inline static real32 get_fractional_signed(real32 val)
{
    return val - truncate_float(val);
}

inline static real32 get_fractional(real32 val)
{
    return val - floor_float(val);
}

inline static real32 get_mod(const real32 in, real32 *out)
{
    return modff(in, out);
}

inline static real32 xe_exp(real32 val)
{
    return expf(val);
}

inline static real32 xe_log(real32 val)
{
    return logf(val);
}

inline static real32 xe_sin(real32 radians)
{
    return sinf(radians);
}

inline static real32 xe_cos(real32 radians)
{
    return cosf(radians);
}

/** Inverse square root */
inline static real32 inv_sqrt(real32 F)
{
    return 1.0f / sqrtf(F);
}

inline static real32 xe_asin(real32 val) { return asinf((val < -1.0f) ? -1.0f : ((val < 1.0f) ? val : 1.0f)); }
inline static real32 xe_sinh(real32 val) { return sinhf(val); }
inline static real32 xe_acos(real32 val) { return acosf((val < -1.0f) ? -1.0f : ((val < 1.0f) ? val : 1.0f)); }
inline static real32 xe_tan(real32 val) { return tanf(val); }
inline static real32 xe_atan(real32 val) { return atanf(val); }
inline static real32 xe_sqrt(real32 val) { return sqrtf(val); }
inline static real32 xe_pow(real32 a, real32 b) { return powf(a, b); }

inline static int32 xe_rand() { return rand(); }

inline static void xe_srand(int32 val) 
{
    return srand(val);
}

/*struct vec2f
{
    union
    {
        struct
        {
            real32 x, y;
        };
        real32 data[2];
    };

    vec2f() : x(0.0f), y(0.0f) {};
    vec2f(real32 x, real32 y) : x(x), y(y) {};
};

inline static real32 dot_product(const vec2f &a, const vec2f &b)
{
    return a.x * b.x + a.y * b.y;
}

inline static real32 cross_product(const vec2f &a, const vec2f &b)
{
    return a.x * b.y - a.y * b.x;
}

inline static real32 magnitude(vec2f &a)
{
    return sqrtf(a.x * a.x + a.y * a.y);
}

inline static void normalize(vec2f &a)
{
    real32 length = magnitude(a);
    if (length > SMALL_NUMBER)
    {
        real32 s = inv_sqrt(length);

        a.x *= s;
        a.y *= s;
    }
}

inline static real32 distance_sqr(const vec2f &a, const vec2f &b)
{
    return sqrtf(b.x - a.x) + sqrtf(b.y - a.y);
}

inline static real32 distance(const vec2f &a, const vec2f &b)
{
    sqrtf(distance_sqr(a, b));
}

inline static vec2f max_cmp(const vec2f &a, const vec2f &b)
{
    return vec2f();
}

inline static vec2f min_cmp(const vec2f &a, const vec2f &b)
{    
    return vec2f();
}

struct vec3f
{
    union
    {
        struct
        {
            real32 x, y, z;
        };
        real32 data[3];
    };

    vec3f() : x(0.0f), y(0.0f), z(0.0f) {};
    vec3f(real32 x, real32 y, real32 z) : x(x), y(y), z(z) {};
};

inline static real32 dot_product(const vec3f &a, const vec3f &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline static vec3f cross_product(const vec3f &a, const vec3f &b)
{
    return vec3f(a.y * b.z - b.z * a.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline static real32 distance(const vec3f &a, const vec3f &b)
{
    
}

inline static real32 distance_sqr(const vec3f &a, const vec3f &b)
{

}

inline static vec3f max_cmp(const vec3f &a, const vec3f &b)
{

}

inline static vec3f min_cmp(const vec3f &a, const vec3f &b)
{

}*/

struct aabb
{
    glm::vec3 min;
    glm::vec3 max;
};

struct ray
{
    glm::vec3 origin, direction;

    bool isIntersects(const aabb &bb, float &t)
    {
        glm::vec3 dirfrac;
        // r.dir is unit direction vector of ray
        dirfrac.x = 1.0f / direction.x;
        dirfrac.y = 1.0f / direction.y;
        dirfrac.z = 1.0f / direction.z;
        
        // lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
        // r.org is origin of ray
        
        const glm::vec3& lb = bb.min;
        const glm::vec3& rt = bb.max;
        
        float t1 = (lb.x - origin.x) * dirfrac.x;
        float t2 = (rt.x - origin.x) * dirfrac.x;
        float t3 = (lb.y - origin.y) * dirfrac.y;
        float t4 = (rt.y - origin.y) * dirfrac.y;
        float t5 = (lb.z - origin.z) * dirfrac.z;
        float t6 = (rt.z - origin.z) * dirfrac.z;

        float tmin = glm::max(glm::max(glm::min(t1, t2), glm::min(t3, t4)), glm::min(t5, t6));
        float tmax = glm::min(glm::min(glm::max(t1, t2), glm::max(t3, t4)), glm::max(t5, t6));

        // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
        if (tmax < 0)
        {
            t = tmax;
            return false;
        }

        // if tmin > tmax, ray doesn't intersect AABB
        if (tmin > tmax)
        {
            t = tmax;
            return false;
        }

        t = tmin;

        return true;
    }

    bool isIntersectsTriangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3& C, float& t)
    {

    }
};