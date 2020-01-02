#include "int_vec2.hxx"

using namespace dreco;

int_vec2::int_vec2() : x(0), y(0)
{
}

int_vec2::int_vec2(const int32_t _x, const int32_t _y) : x(_x), y(_y)
{
}

int_vec2 int_vec2::operator-(const int_vec2& _v) 
{
    return int_vec2(this->x - _v.x, this->y - _v.y);
}