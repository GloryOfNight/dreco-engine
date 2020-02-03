#pragma once

namespace dreco 
{
    struct mat2x3;

    struct vec3 
    {
        vec3();

        vec3(const float& _x, const float& _y, const float& _z);

        vec3 operator*(const mat2x3& _m);

        float x;

        float y;

        float z;
    };
}
