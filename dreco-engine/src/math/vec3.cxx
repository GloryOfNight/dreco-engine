#include "vec3.hxx"
#include "mat2x3.hxx"

using namespace dreco;

vec3::vec3() {}

vec3 vec3::operator*(const mat2x3& _m) 
{
    vec3 res;
    res.x = x *_m.mat[0][0] + x *_m.mat[1][0];
    res.y = y * _m.mat[0][1] + y * _m.mat[1][1];
    res.z = z *_m.mat[0][2] + z *_m.mat[1][2] + res.z;
    return res;
}