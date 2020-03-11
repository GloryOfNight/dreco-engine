#pragma once

namespace dreco
{
template <typename T>
struct point
{
	point() : x(0), y(0)
	{
	}

	point(const T& _v) : x(_v), y(_v)
	{
	}

	point(const T& _x, const T& _y) : x(_x), y(_y)
	{
	}

	point<T>& operator++()
	{
		++x;
		++y;
        return *this;
	}

	point<T>& operator--()
	{
		--x;
		--y;
        return *this;
	}

	point<T> operator+(const point<T>& _o)
	{
		return point<T>(this->x + _o.x, this->y + _o.y);
	}

	point<T> operator-(const point<T>& _o)
	{
		return point<T>(this->x - _o.x, this->y - _o.y);
	}

	T x;
	T y;
};
}	 // namespace dreco
