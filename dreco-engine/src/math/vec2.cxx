#include "vec2.hxx"

using namespace dreco;

vec2::vec2() : x(0.0f), y(0.0f)
{
}

vec2::vec2(const float& _x, const float& _y) : x(_x), y(_y)
{
}

void vec2::operator*=(const vec2& _v)
{
	this->x *= _v.x;
	this->y *= _v.y;
}

vec2 vec2::operator*(const vec2& _v)
{
	return vec2(this->x * _v.x, this->y * _v.y);
}

vec2 vec2::operator-(const vec2& _v)
{
	return vec2(this->x - _v.x, this->y - _v.y);
}

void vec2::operator+=(const vec2& _v)
{
	this->x += _v.x;
	this->y += _v.y;
}

void vec2::operator-=(const float& _f)
{
	this->x -= _f;
	this->y -= _f;
}

void vec2::operator+=(const float& _f)
{
	this->x += _f;
	this->y += _f;
}

bool vec2::operator==(const vec2& _v)
{
	return this->x == _v.x && this->y == _v.y;
}