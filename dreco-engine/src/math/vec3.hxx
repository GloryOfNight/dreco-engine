#pragma once

namespace dreco 
{
    struct mat2x3;

    struct vec3 
    {
        vec3();

        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        vec3 operator*(const mat2x3& _m);
    };
}
