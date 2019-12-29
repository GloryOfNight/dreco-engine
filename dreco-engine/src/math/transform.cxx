#include "transform.hxx"

using namespace dreco;

transform::transform()
{
}

transform::transform(vec2 _t, float _r, vec2 _s)
	: translation(_t), rotation(_r), scale(_s)
{
}
