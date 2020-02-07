#pragma once 
#include "math/mat2x3.hxx"
#include "math/vec2.hxx"

namespace dreco 
{
    class math_utils 
    {
        public:

        // UnProject screen coordinates to world
        static vec2 UnProject(const vec2& _screen_coord, const vec2& _viewport_size, 
			const mat2x3& _v, const mat2x3& _p);

	    static mat2x3 CreateProjectionMatrix2D(
		    const float right, const float left, const float top, const float bottom);
    };
}