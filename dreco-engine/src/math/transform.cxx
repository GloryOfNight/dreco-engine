#include "transform.hxx"

using namespace dreco;

transform::transform() : translation(vec2()), rotation(0.0f), scale(vec2(1.0f, 1.0f))
{
}

transform::transform(const vec2& _t, const float& _r, const vec2& _s)
	: translation(_t), rotation(_r), scale(_s)
{
}
