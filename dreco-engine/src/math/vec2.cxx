#include "vec2.hxx"

using namespace dreco;

vec2::vec2(const float _x, const float _y)
{
	x = _x;
	y = _y;
}
 
const void vec2::operator*=(const vec2& _v)
{
	this->x *= _v.x;
	this->y *= _v.y;
}

const vec2 vec2::operator*(const vec2& _v)
{
    return vec2(this->x * _v.x, this->y * _v.y);
}