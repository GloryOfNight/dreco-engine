#include "transform.hxx"

using namespace dreco;

transform::transform()
{
}

transform::transform(vec2 _t, float _r, vec2 _s)
	: translation(_t), rotation(_r), scale(_s)
{
}

mat2x3 transform::GetTranslationMatrix()
{
	return mat2x3::translate(translation);
}
mat2x3 transform::GetRotationMatrix()
{
	return mat2x3::rotate(rotation);
}
mat2x3 transform::GetScaleMatrix()
{
	return mat2x3::scale(scale.x, scale.y);
}